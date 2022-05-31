#include "grey.h"
#include <stdlib.h>
#include <stdio.h>

const char* colorVertexShader = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 aColor;\n"
"out vec4 color;\n"
"uniform vec2 viewport;\n"
"uniform vec3 offset;\n"
"void main() {\n"
"   gl_Position = vec4((aPos.x - viewport.x) / viewport.x - (offset.x / viewport.x), (aPos.y + viewport.y) / viewport.y + (offset.y / viewport.y), aPos.z, 1.0);\n"
"	color = aColor;\n"
"}\0";

const char* colorFragmentShader = "#version 330 core\n"
//"out vec4 FragColor;\n"
"in vec4 color;\n"
"void main() {\n"
"	gl_FragColor = color;\n"
"}\0";

GLFWmonitor* getWindowMonitor(GLFWwindow* win) {
	int count;
	GLFWmonitor** monitors = glfwGetMonitors(&count);
	C_floatVec widths = C_floatVecCreate();
	for (int i = 0; i < count; i++) {
		if (i == 0) { C_floatVecPushBack(&widths, 0.0f); }
		else {
			const GLFWvidmode* modee = glfwGetVideoMode(monitors[i]);
			C_floatVecPushBack(&widths, modee->width + widths.data[widths.size - 1]);
		}
	}
	int x = 0, y = 0;
	glfwGetWindowPos(win, &x, &y);
	for (int i = 0; i < widths.size; i++) {
		if (i + 2 > widths.size || x > widths.data[i] && x < widths.data[i+1]) {
			return monitors[i];
		}
	}
}

// Init/deinit funcs
void C_initGrey(unsigned int sampleRate) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, sampleRate);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
#ifdef _WIN32
	typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC)(int interval);
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if (wglSwapIntervalEXT) { wglSwapIntervalEXT(1); }
#else
	glfwSwapInterval(1);
#endif
}
void C_closeGrey() {
	glfwTerminate();
}

// Window funcs
void framebufferCallback(GLFWwindow * win, int width, int height) {
	glfwMakeContextCurrent(win);
	glViewport(0, 0, width, height);
}
C_Window C_createWindow(int width, int height, const char* title) {
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	C_Window win;
	win.windowHandle = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwSetWindowPos(win.windowHandle, (mode->width / 2) - (width / 2), (mode->height / 2) - (height / 2));
	glfwMakeContextCurrent(win.windowHandle);
	glfwSetFramebufferSizeCallback(win.windowHandle, framebufferCallback);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	win.title = title;
	win.triangles = C_floatVecCreate();
	win.deltaTime = 0.0f;
	win.width = width;
	win.height = height;
	win.fullscreen = FALSE;
	win.priorFullscreen = FALSE;
	win.prevWidth = width;
	win.prevHeight = height;

	glGenBuffers(1, &win.VBO);
	glGenVertexArrays(1, &win.VAO);
	glBindVertexArray(win.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, win.VBO);
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	unsigned int w_colorVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(w_colorVertexShader, 1, &colorVertexShader, NULL);
	glCompileShader(w_colorVertexShader);
	unsigned int w_colorFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(w_colorFragmentShader, 1, &colorFragmentShader, NULL);
	glCompileShader(w_colorFragmentShader);
	win.colorShader = glCreateProgram();
	glAttachShader(win.colorShader, w_colorVertexShader);
	glAttachShader(win.colorShader, w_colorFragmentShader);
	glLinkProgram(win.colorShader);
	glDeleteShader(w_colorVertexShader);
	glDeleteShader(w_colorFragmentShader);

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return win;
}
void C_deleteWindow(C_Window* win) {
	C_floatVecDelete(&win->triangles);
}
boolean C_shouldWindowClose(C_Window win) {
	return glfwWindowShouldClose(win.windowHandle);
}
void C_updateWindow(C_Window* win) {
	win->currentFrame = (float)glfwGetTime();
	win->deltaTime = win->currentFrame - win->lastFrame;
	win->lastFrame = win->currentFrame;
	if (win->deltaTime > 0.05f) { win->deltaTime = 0.05f; }
	glfwSetWindowTitle(win->windowHandle, win->title);
	C_floatVecClear(&win->triangles);
	glfwPollEvents();

	if (win->fullscreen != win->priorFullscreen) {
		win->priorFullscreen = win->fullscreen;
		if (win->fullscreen == TRUE) {
			glfwGetWindowPos(win->windowHandle, &win->prevX, &win->prevY);
			glfwGetWindowSize(win->windowHandle, &win->prevWidth, &win->prevHeight);
			GLFWmonitor* currentMonitor = getWindowMonitor(win->windowHandle);
			const GLFWvidmode* mode = glfwGetVideoMode(currentMonitor);
			glfwSetWindowMonitor(win->windowHandle, currentMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		}
		else {
			const GLFWvidmode* mode = glfwGetVideoMode(getWindowMonitor(win->windowHandle));
			glfwSetWindowMonitor(win->windowHandle, NULL, win->prevX, win->prevY, win->prevWidth, win->prevHeight, mode->refreshRate);
		}
	}

	glfwGetWindowSize(win->windowHandle, &win->width, &win->height);
	for (int i = 0; i < sizeof(win->keys) / sizeof(win->keys[0]); i++) {
		win->keys[i] = glfwGetKey(win->windowHandle, i);
		if (win->keys[i] == GLFW_PRESS && win->tempKeys[i] == GLFW_PRESS) {
			win->tempKeys[i] = GLFW_RELEASE;
			win->tempKeysCheck[i] = 1;
		}
		else if (win->keys[i] == GLFW_RELEASE) {
			win->tempKeys[i] = GLFW_RELEASE;
			win->tempKeysCheck[i] = 0;
		}
		else if (win->tempKeysCheck[i] == 0) {
			win->tempKeys[i] = win->keys[i];
		}
	}
}
void C_renderWindow(C_Window win) {
	glfwMakeContextCurrent(win.windowHandle);
	glfwSetWindowSize(win.windowHandle, win.width, win.height);

	glBindBuffer(GL_ARRAY_BUFFER, win.VBO);
	glBufferData(GL_ARRAY_BUFFER, win.triangles.size * sizeof(float), win.triangles.data, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(win.VAO);
	glUseProgram(win.colorShader);
	glUniform2f(glGetUniformLocation(win.colorShader, "viewport"), (GLfloat)win.width/2, (GLfloat)win.height/2);
	glUniform3f(glGetUniformLocation(win.colorShader, "offset"), 0.0f, 0.0f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, ((win.triangles.size / 7) * 3));

	glfwSwapBuffers(win.windowHandle);
}
void C_closeWindow(C_Window win) {
	glfwSetWindowShouldClose(win.windowHandle, GLFW_TRUE);
}
void C_setWindowFlag(C_Window win, uint32_t flag, boolean state) {
	glfwSetWindowAttrib(win.windowHandle, flag, state);
}

// Key input
boolean C_isKeyDown(C_Window win, int key) {
	if (key < sizeof(win.keys) / sizeof(win.keys[0])) {
		return win.keys[key];
	}
	return 0;
}
boolean C_isKeyPressed(C_Window win, int key) {
	if (key < sizeof(win.tempKeys) / sizeof(win.tempKeys[0])) {
		return win.tempKeys[key];
	}
	return 0;
}

// Draw funcs
void C_clearWindowBackground(C_Window win, Color color) {
	glfwMakeContextCurrent(win.windowHandle);
	glClearColor((float)color[0] / 255, (float)color[1] / 255, (float)color[2] / 255, (float)color[3] / 255);
	glClear(GL_COLOR_BUFFER_BIT);
}
void C_setWireframeMode(C_Window win, boolean state) {
	glfwMakeContextCurrent(win.windowHandle);
	if (state) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
void C_drawTriangle(C_Window* win, float x1, float y1, float x2, float y2, float x3, float y3, Color color) {
	float xs[3] = {x1, x2, x3};
	float ys[3] = { -y1, -y2, -y3 };

	// This could be optimized. Too bad!
	for (int i = 1; i < 4; i++) {
		C_floatVecPushBack(&win->triangles, xs[i-1]);
		C_floatVecPushBack(&win->triangles, ys[i-1]);
		C_floatVecPushBack(&win->triangles, 0.0f);
		C_floatVecPushBack(&win->triangles, (float)color[0] / 255);
		C_floatVecPushBack(&win->triangles, (float)color[1] / 255);
		C_floatVecPushBack(&win->triangles, (float)color[2] / 255);
		C_floatVecPushBack(&win->triangles, (float)color[3] / 255);
	}
}
void C_drawRectangle(C_Window* win, float x, float y, float width, float height, Color color) {
	C_drawTriangle(win, x, y, x, y + height, x + width, y + height, color);
	C_drawTriangle(win, x, y, x + width, y, x + width, y + height, color);
}