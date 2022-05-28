#include "grey"

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

float* resizeFloatList(float* list, int indexSize) {
	float* tempTri;
	tempTri = (float*)calloc(indexSize, sizeof(float));
	if (!tempTri) { return NULL; }
	memcpy(tempTri, list, indexSize);
	return tempTri;
}
grey_float_vector C_new_grey_float_vector() {
	grey_float_vector vec;
	vec.vec = (float*)calloc(0, sizeof(float));
	vec.vecSize = 0;
	return vec;
}
void C_float_vec_push_back(grey_float_vector* vec, float num) {
	int a = vec->vecSize; // a = 0;
	float* before = (float*)calloc(vec->vecSize, sizeof(float));
	if (!before) { return; }
	for (int i = 0; i < vec->vecSize; i++) {
		before[i] = vec->vec[i];
	}
	vec->vecSize += 1; // vecSize = 1;
	free(vec->vec); // vec = {  };
	vec->vec = (float*)calloc(vec->vecSize, sizeof(float)); // vec = { 0 };
	if (!vec->vec) { return; }
	for (int i = 0; i < a; i++) { // for (int i = 0; i < 0; i++)
		// Fuck you C
		vec->vec[i] = before[i]; // (never exec)
	}
	vec->vec[vec->vecSize - 1] = num; // vec[0] = num;
	free(before);
}
void C_float_vec_clear(grey_float_vector* vec) {
	free(vec->vec);
	vec->vec = (float*)calloc(0, sizeof(float));
	vec->vecSize = 0;
}
void C_float_vec_delete(grey_float_vector* vec) {
	free(vec->vec);
	vec->vecSize = 0;
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
	win.triangles = C_new_grey_float_vector();
	win.deltaTime = 0.0f;

	glGenBuffers(1, &win.VBO);
	glGenVertexArrays(1, &win.VAO);
	glBindVertexArray(win.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, win.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(win.triangles.vec), win.triangles.vec, GL_DYNAMIC_DRAW);
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

	return win;
}
void C_deleteWindow(C_Window* win) {
	C_float_vec_delete(&win->triangles);
}
boolean C_shouldWindowClose(C_Window win) {
	return glfwWindowShouldClose(win.windowHandle);
}
void C_updateWindow(C_Window* win) {
	win->currentFrame = glfwGetTime();
	win->deltaTime = win->currentFrame - win->lastFrame;
	win->lastFrame = win->currentFrame;
	if (win->deltaTime > 0.05f) { win->deltaTime = 0.05f; }
	glfwSetWindowTitle(win->windowHandle, win->title);
	C_float_vec_clear(&win->triangles);
	glfwPollEvents();
	for (int i = 0; i < sizeof(win->keys) / sizeof(win->keys[0]); i++) {
		win->keys[i] = glfwGetKey(win->windowHandle, i);
	}
}
void C_renderWindow(C_Window win) {
	glBindBuffer(GL_ARRAY_BUFFER, win.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(win.triangles.vec) * 7 * ((win.triangles.vecSize / 7) * 3), win.triangles.vec, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(win.VAO);
	glUseProgram(win.colorShader);
	int width = 0, height = 0;
	glfwGetWindowSize(win.windowHandle, &width, &height);
	glUniform2f(glGetUniformLocation(win.colorShader, "viewport"), width/2, height/2);
	glUniform3f(glGetUniformLocation(win.colorShader, "offset"), 0, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, ((win.triangles.vecSize / 7) * 3));

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

// Draw funcs
void C_clearWindowBackground(C_Window win, Color color) {
	glfwMakeContextCurrent(win.windowHandle);
	glClearColor((float)color[0] / 255, (float)color[1] / 255, (float)color[2] / 255, (float)color[3] / 255);
	glClear(GL_COLOR_BUFFER_BIT);
}
void C_drawTriangle(C_Window* win, float x1, float y1, float x2, float y2, float x3, float y3, Color color) {
	float xs[3] = {x1, x2, x3};
	float ys[3] = { -y1, -y2, -y3 };

	// This could be optimized. Too bad!
	for (int i = 1; i < 4; i++) {
		C_float_vec_push_back(&win->triangles, xs[i-1]);
		C_float_vec_push_back(&win->triangles, ys[i-1]);
		C_float_vec_push_back(&win->triangles, 0.0f);
		C_float_vec_push_back(&win->triangles, (float)color[0] / 255);
		C_float_vec_push_back(&win->triangles, (float)color[1] / 255);
		C_float_vec_push_back(&win->triangles, (float)color[2] / 255);
		C_float_vec_push_back(&win->triangles, (float)color[3] / 255);
	}
}
void C_drawRectangle(C_Window* win, float x, float y, float width, float height, Color color) {
	C_drawTriangle(win, x, y, x, y + height, x + width, y + height, color);
	C_drawTriangle(win, x, y, x + width, y, x + width, y + height, color);
}