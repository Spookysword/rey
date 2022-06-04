#include "grey.h"
#include <stdlib.h>
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
const char* textureVertexShader = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec4 color;\n"
"out vec2 TexCoord;\n"
"uniform vec2 viewport;\n"
"uniform vec3 offset;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4((aPos.x - viewport.x) / viewport.x - (offset.x / viewport.x), (aPos.y + viewport.y) / viewport.y + (offset.y / viewport.y), aPos.z, 1.0);\n"
"	color = aColor;\n"
"	TexCoord = aTexCoord;\n"
"}\0";
const char* textureFragmentShader = "#version 330 core\n"
"in vec4 color;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D currentTexture;\n"
"void main()\n"
"{\n"
"	gl_FragColor = texture(currentTexture, TexCoord) * color;\n"
"}\0";

C_Batch C_createBatch() {
	C_Batch batch;
	glGenVertexArrays(1, &batch.VAO);
	glGenBuffers(1, &batch.VBO);
	glBindVertexArray(batch.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, batch.VBO);
	batch.stack = 0;
	batch.verticeCount = 0;
	batch.triangles = C_floatVecCreate();
	batch.shapeVertices = C_intVecCreate();
	//glBufferData(GL_ARRAY_BUFFER, batch.triangles.size * sizeof(float), batch.triangles.data, GL_DYNAMIC_DRAW);
	
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return batch;
}
void C_addVertice(C_Batch* batch, float verts[7]) {
	C_floatVecPushBack7(&batch->triangles, verts);
	batch->verticeCount++;
	batch->stack++;
}
void C_addTriangle(C_Batch* batch, float verts[21]) {
	C_floatVecPushBack21(&batch->triangles, verts);
	batch->verticeCount += 3;
	batch->stack += 3;
}
void C_endShape(C_Batch* batch) {
	C_intVecPushBack(&batch->shapeVertices, batch->stack);
	batch->stack = 0;
}
void C_draw(C_Batch batch, GLenum type) {
	// This could be optimized by not using a vector here
	glBindVertexArray(batch.VAO);
	C_intVec first = C_intVecCreate();
	int tempInt = 0;
	for (int i = 0; i < batch.shapeVertices.size; i++) {
		C_intVecPushBack(&first, tempInt);
		tempInt += batch.shapeVertices.data[i];
	}
	glMultiDrawArrays(type, first.data, batch.shapeVertices.data, batch.shapeVertices.size);
	C_intVecDelete(&first);
}
void C_bindBatch(C_Batch batch) {
	glBindBuffer(GL_ARRAY_BUFFER, batch.VBO);
	glBufferData(GL_ARRAY_BUFFER, batch.triangles.size * sizeof(float), batch.triangles.data, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void C_flushBatch(C_Batch* batch) {
	C_floatVecClear(&batch->triangles);
	batch->verticeCount = 0;
	batch->stack = 0;
	C_intVecClear(&batch->shapeVertices);
}
void C_deleteBatch(C_Batch* batch) {
	C_floatVecDelete(&batch->triangles);
	C_intVecDelete(&batch->shapeVertices);
}

void C_addTextureVertice(C_TextureBatch* batch, float verts[9]) {
	C_floatVecPushBack9(&batch->triangles, verts);
	batch->verticeCount++;
	batch->stack++;
}
void C_addTextureTriangle(C_TextureBatch* batch, float verts[27]) {
	C_floatVecPushBack27(&batch->triangles, verts);
	batch->verticeCount+= 3;
	batch->stack+= 3;
}
void C_endTextureShape(C_TextureBatch* batch) {
	C_intVecPushBack(&batch->shapeVertices, batch->stack);
	batch->stack = 0;
}
void C_drawTextureBatch(C_TextureBatch batch, GLenum type) {
	glBindVertexArray(batch.VAO);
	C_intVec first = C_intVecCreate();
	int tempInt = 0;
	for (int i = 0; i < batch.shapeVertices.size; i++) {
		C_intVecPushBack(&first, tempInt);
		tempInt += batch.shapeVertices.data[i];
	}
	glMultiDrawArrays(type, first.data, batch.shapeVertices.data, batch.shapeVertices.size);
	C_intVecDelete(&first);
}
C_TextureBatch C_createTextureBatch(const char* filePath, int filter) {
	C_TextureBatch batch;
	glGenVertexArrays(1, &batch.VAO);
	glGenBuffers(1, &batch.VBO);
	glBindVertexArray(batch.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, batch.VBO);
	batch.stack = 0;
	batch.verticeCount = 0;
	batch.triangles = C_floatVecCreate();
	batch.shapeVertices = C_intVecCreate();

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Texture coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenTextures(1, &batch.textureID);
	glBindTexture(GL_TEXTURE_2D, batch.textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

	int width, height, nrChannels;
	// No clue what "desired_channels" does here
	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 4);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		printf("Error generating texture\n");
	}
	stbi_image_free(data);

	return batch;
}
void C_bindTextureBatch(C_TextureBatch batch) {
	glBindBuffer(GL_ARRAY_BUFFER, batch.VBO);
	glBufferData(GL_ARRAY_BUFFER, batch.triangles.size * sizeof(float), batch.triangles.data, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void C_flushTextureBatch(C_TextureBatch* batch) {
	C_floatVecClear(&batch->triangles);
	batch->verticeCount = 0;
	batch->stack = 0;
	C_intVecClear(&batch->shapeVertices);
}
void C_deleteTextureBatch(C_TextureBatch* batch) {
	C_floatVecDelete(&batch->triangles);
	C_intVecDelete(&batch->shapeVertices);
}

C_textureVec C_textureVecCreate() {
	C_textureVec vec;
	vec.data = (C_TextureBatch*)calloc(0, sizeof(C_TextureBatch));
	vec.size = 0;
	vec.limit = 0;
	return vec;
}
void C_textureVecCheckSize(C_textureVec* vec) {
	if (vec->size + 1 > vec->limit) {
		C_TextureBatch* temp;
		vec->limit = vec->size * 2;
		temp = (C_TextureBatch*)realloc(vec->data, vec->limit * sizeof(C_TextureBatch));
		if (temp) { vec->data = temp; }
	}
}
void C_textureVecPushBack(C_textureVec* vec, C_TextureBatch num) {
	vec->size += 1;
	C_textureVecCheckSize(vec);
	vec->data[vec->size-1] = num;
}
void C_textureVecClear(C_textureVec* vec) {
	free(vec->data);
	vec->limit /= 2;
	vec->data = (C_TextureBatch*)calloc(vec->limit, sizeof(C_TextureBatch));
	vec->size = 0;
}
void C_textureVecDelete(C_textureVec* vec) {
	for (int i = 0; i < vec->size; i++) {
		C_deleteTextureBatch(&vec->data[i-1]);
	}
	free(vec->data);
	vec->size = 0;
	vec->limit = 0;
}

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
	GLFWmonitor* returnMon = monitors[widths.size-1];
	for (int i = 0; i < widths.size; i++) {
		if (widths.size && x > widths.data[i] && x < widths.data[i+1]) {
			returnMon = monitors[i];
		}
	}
	C_floatVecDelete(&widths);
	return returnMon;
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
	win.shapeBatch = C_createBatch();
	win.deltaTime = 0.001f;
	win.width = width;
	win.height = height;
	win.fullscreen = FALSE;
	win.priorFullscreen = FALSE;
	win.prevWidth = width;
	win.prevHeight = height;
	win.textures = C_textureVecCreate();
	win.zmod = 0.0f;
	win.camera.x = 0.0f, win.camera.y = 0.0f, win.camera.z = 0.0f;
	win.framesPerSecond = 0.0f;

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

	// Prob should make this a function
	unsigned int w_textureVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(w_textureVertexShader, 1, &textureVertexShader, NULL);
	glCompileShader(w_textureVertexShader);
	unsigned int w_textureFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(w_textureFragmentShader, 1, &textureFragmentShader, NULL);
	glCompileShader(w_textureFragmentShader);
	win.textureShader = glCreateProgram();
	glAttachShader(win.textureShader, w_textureVertexShader);
	glAttachShader(win.textureShader, w_textureFragmentShader);
	glLinkProgram(win.textureShader);
	glDeleteShader(w_textureVertexShader);
	glDeleteShader(w_textureFragmentShader);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return win;
}
void C_deleteWindow(C_Window* win) {
	C_deleteBatch(&win->shapeBatch);
	C_textureVecClear(&win->textures);
	C_textureVecDelete(&win->textures);
}
boolean C_shouldWindowClose(C_Window win) {
	return glfwWindowShouldClose(win.windowHandle);
}
Texture c_newTexture(C_Window* win, const char* path, int filter) {
	C_TextureBatch text = C_createTextureBatch(path, filter);
	C_textureVecPushBack(&win->textures, text);
	return win->textures.size-1;
}
void c_deleteTexture(C_Window* win, Texture texture) {
	C_deleteTextureBatch(&win->textures.data[texture]);
}
void C_updateWindow(C_Window* win) {
	C_flushBatch(&win->shapeBatch);
	for (int i = 0; i < win->textures.size; i++) {
		C_flushTextureBatch(&win->textures.data[i]);
	}
	win->framesPerSecond = 1.0f / (glfwGetTime() - win->currentFrame);
	win->currentFrame = (float)glfwGetTime();
	win->deltaTime = win->currentFrame - win->lastFrame;
	win->lastFrame = win->currentFrame;
	win->zmod = 0.0f;
	if (win->deltaTime > 0.05f) { win->deltaTime = 0.05f; }
	glfwSetWindowTitle(win->windowHandle, win->title);
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
	
	C_bindBatch(win.shapeBatch);
	glUseProgram(win.colorShader);
	glUniform2f(glGetUniformLocation(win.colorShader, "viewport"), (GLfloat)win.width/2, (GLfloat)win.height/2);
	glUniform3f(glGetUniformLocation(win.colorShader, "offset"), win.camera.x, win.camera.y, win.camera.z);
	
	C_draw(win.shapeBatch, GL_TRIANGLE_FAN);
	
	glUseProgram(win.textureShader);
	glUniform2f(glGetUniformLocation(win.textureShader, "viewport"), (GLfloat)win.width / 2, (GLfloat)win.height / 2);
	glUniform3f(glGetUniformLocation(win.textureShader, "offset"), win.camera.x, win.camera.y, win.camera.z);
	for (int i = 0; i < win.textures.size; i++) {
		C_bindTextureBatch(win.textures.data[i]);
		glBindTexture(GL_TEXTURE_2D, win.textures.data[i].textureID);
		glBindVertexArray(win.textures.data[i].VAO);
		C_drawTextureBatch(win.textures.data[i], GL_TRIANGLE_FAN);
	}

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
	float passIn1[21] = {
		x1, -y1, win->zmod, (float)color[0]/255, (float)color[1]/255, (float)color[2]/255, (float)color[3]/255,
		x2, -y2, win->zmod, (float)color[0]/255, (float)color[1]/255, (float)color[2]/255, (float)color[3]/255,
		x3, -y3, win->zmod, (float)color[0]/255, (float)color[1]/255, (float)color[2]/255, (float)color[3]/255
	};
	C_addTriangle(&win->shapeBatch, passIn1);
	C_endShape(&win->shapeBatch);
	win->zmod -= 0.000001f;
}
void C_drawRectangle(C_Window* win, float x, float y, float width, float height, float rotation, Color color) {
	float r = (float)color[0] / 255, g = (float)color[1] / 255, b = (float)color[2] / 255, a = (float)color[3] / 255;
	y = -y;
	if (rotation == 0.0f || (int)rotation % 360 == 0) {
		float passIn1[21] = {
			x, y, win->zmod, r, g, b, a,
			x, y - height, win->zmod, r, g, b, a,
			x + width, y - height, win->zmod, r, g, b, a
		};
		float passIn2[7] = {
			x + width, y, win->zmod, r, g, b, a
		};
		C_addTriangle(&win->shapeBatch, passIn1);
		C_addVertice(&win->shapeBatch, passIn2);
		C_endShape(&win->shapeBatch);
	}
	else {
		float pi = 3.1415926535897932384626433;
		rotation = -rotation * (pi / 180);
		float a1 = sqrt(pow((width / 2), 2) + pow((height / 2), 2));
		float r0 = asin(((height / 2) * (sin(pi / 2))) / a1), r1 = r0 + rotation, r2 = -r0 + rotation, r3 = r1 - pi, r4 = r2 - pi;
		float c1 = x + width / 2, c2 = y - height / 2;
		float passIn1[21] = {
			a1 * cos(r1) + c1, a1 * sin(r1) + c2, win->zmod, r, g, b, a,
			a1 * cos(r2) + c1, a1 * sin(r2) + c2, win->zmod, r, g, b, a,
			a1 * cos(r3) + c1, a1 * sin(r3) + c2, win->zmod, r, g, b, a
		};
		float passIn2[7] = {
			a1 * cos(r4) + c1, a1 * sin(r4) + c2, win->zmod, r, g, b, a
		};
		C_addTriangle(&win->shapeBatch, passIn1);
		C_addVertice(&win->shapeBatch, passIn2);
		C_endShape(&win->shapeBatch);
	}
	win->zmod -= 0.000001f;
}
void C_drawTexture(C_Window* win, Texture texture, float x, float y, float width, float height, float rotation, Color color) {
	float r = (float)color[0] / 255, g = (float)color[1] / 255, b = (float)color[2] / 255, a = (float)color[3] / 255;
	y = -y;
	if (rotation == 0.0f || (int)rotation % 360 == 0) {
		float passIn1[27] = {
			x, y, win->zmod, r, g, b, a, 0.0f, 1.0f,
			x, y - height, win->zmod, r, g, b, a, 0.0f, 0.0f,
			x + width, y - height, win->zmod, r, g, b, a, 1.0f, 0.0f
		};
		float passIn2[9] = {
			x + width, y, win->zmod, r, g, b, a, 1.0f, 1.0f
		};
		C_addTextureTriangle(&win->textures.data[texture], passIn1);
		C_addTextureVertice(&win->textures.data[texture], passIn2);
		C_endTextureShape(&win->textures.data[texture]);
	}
	else {
		float pi = 3.1415926535897932384626433;
		rotation = -rotation * (pi / 180);
		float a1 = sqrt(pow((width / 2), 2) + pow((height / 2), 2));
		float r0 = asin(((height / 2) * (sin(pi / 2))) / a1), r1 = r0 + rotation, r2 = -r0 + rotation, r3 = r1 - pi, r4 = r2 - pi;
		float c1 = x + width / 2, c2 = y - height / 2;
		float passIn1[27] = {
			a1 * cos(r1) + c1, a1 * sin(r1) + c2, win->zmod, r, g, b, a, 0.0f, 1.0f,
			a1 * cos(r2) + c1, a1 * sin(r2) + c2, win->zmod, r, g, b, a, 0.0f, 0.0f,
			a1 * cos(r3) + c1, a1 * sin(r3) + c2, win->zmod, r, g, b, a, 1.0f, 0.0f
		};
		float passIn2[9] = {
			a1 * cos(r4) + c1, a1 * sin(r4) + c2, win->zmod, r, g, b, a, 1.0f, 1.0f
		};
		C_addTextureTriangle(&win->textures.data[texture], passIn1);
		C_addTextureVertice(&win->textures.data[texture], passIn2);
		C_endTextureShape(&win->textures.data[texture]);
	}
	win->zmod -= 0.000001f;
}