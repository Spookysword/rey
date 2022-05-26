// https://www.youtube.com/watch?v=1WLYOV7oM_g
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#ifdef _WIN32
#include <Windows.h>
#endif

/*
NOTES:
Multiple windows won't work currently because I don't know how to clear screen to a certain window.
Create a grey_vector struct in order to manage triangle float sizes.
COLOR STRUCT!!!!!!!!!!!
*/

/* The unknown key */
#define KEY_UNKNOWN            -1

/* Printable keys */
#define KEY_SPACE              32
#define KEY_APOSTROPHE         39  /* ' */
#define KEY_COMMA              44  /* , */
#define KEY_MINUS              45  /* - */
#define KEY_PERIOD             46  /* . */
#define KEY_SLASH              47  /* / */
#define KEY_0                  48
#define KEY_1                  49
#define KEY_2                  50
#define KEY_3                  51
#define KEY_4                  52
#define KEY_5                  53
#define KEY_6                  54
#define KEY_7                  55
#define KEY_8                  56
#define KEY_9                  57
#define KEY_SEMICOLON          59  /* ; */
#define KEY_EQUAL              61  /* = */
#define KEY_A                  65
#define KEY_B                  66
#define KEY_C                  67
#define KEY_D                  68
#define KEY_E                  69
#define KEY_F                  70
#define KEY_G                  71
#define KEY_H                  72
#define KEY_I                  73
#define KEY_J                  74
#define KEY_K                  75
#define KEY_L                  76
#define KEY_M                  77
#define KEY_N                  78
#define KEY_O                  79
#define KEY_P                  80
#define KEY_Q                  81
#define KEY_R                  82
#define KEY_S                  83
#define KEY_T                  84
#define KEY_U                  85
#define KEY_V                  86
#define KEY_W                  87
#define KEY_X                  88
#define KEY_Y                  89
#define KEY_Z                  90
#define KEY_LEFT_BRACKET       91  /* [ */
#define KEY_BACKSLASH          92  /* \ */
#define KEY_RIGHT_BRACKET      93  /* ] */
#define KEY_GRAVE_ACCENT       96  /* ` */
#define KEY_WORLD_1            161 /* non-US #1 */
#define KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define KEY_ESCAPE             256
#define KEY_ENTER              257
#define KEY_TAB                258
#define KEY_BACKSPACE          259
#define KEY_INSERT             260
#define KEY_DELETE             261
#define KEY_RIGHT              262
#define KEY_LEFT               263
#define KEY_DOWN               264
#define KEY_UP                 265
#define KEY_PAGE_UP            266
#define KEY_PAGE_DOWN          267
#define KEY_HOME               268
#define KEY_END                269
#define KEY_CAPS_LOCK          280
#define KEY_SCROLL_LOCK        281
#define KEY_NUM_LOCK           282
#define KEY_PRINT_SCREEN       283
#define KEY_PAUSE              284
#define KEY_F1                 290
#define KEY_F2                 291
#define KEY_F3                 292
#define KEY_F4                 293
#define KEY_F5                 294
#define KEY_F6                 295
#define KEY_F7                 296
#define KEY_F8                 297
#define KEY_F9                 298
#define KEY_F10                299
#define KEY_F11                300
#define KEY_F12                301
#define KEY_F13                302
#define KEY_F14                303
#define KEY_F15                304
#define KEY_F16                305
#define KEY_F17                306
#define KEY_F18                307
#define KEY_F19                308
#define KEY_F20                309
#define KEY_F21                310
#define KEY_F22                311
#define KEY_F23                312
#define KEY_F24                313
#define KEY_F25                314
#define KEY_KP_0               320
#define KEY_KP_1               321
#define KEY_KP_2               322
#define KEY_KP_3               323
#define KEY_KP_4               324
#define KEY_KP_5               325
#define KEY_KP_6               326
#define KEY_KP_7               327
#define KEY_KP_8               328
#define KEY_KP_9               329
#define KEY_KP_DECIMAL         330
#define KEY_KP_DIVIDE          331
#define KEY_KP_MULTIPLY        332
#define KEY_KP_SUBTRACT        333
#define KEY_KP_ADD             334
#define KEY_KP_ENTER           335
#define KEY_KP_EQUAL           336
#define KEY_LEFT_SHIFT         340
#define KEY_LEFT_CONTROL       341
#define KEY_LEFT_ALT           342
#define KEY_LEFT_SUPER         343
#define KEY_RIGHT_SHIFT        344
#define KEY_RIGHT_CONTROL      345
#define KEY_RIGHT_ALT          346
#define KEY_RIGHT_SUPER        347
#define KEY_MENU               348
// Window flags
#define WINDOW_RESIZABLE GLFW_RESIZABLE
#define WINDOW_VISIBLE GLFW_VISIBLE
#define WINDOW_DECORATED GLFW_DECORATED
#define WINDOW_FOCUSED GLFW_FOCUSED
#define WINDOW_AUTO_ICONIFY GLFW_AUTO_ICONIFY
#define WINDOW_FLOATING GLFW_FLOATING
#define WINDOW_MAXIMIZED GLFW_MAXIMIZED
#define WINDOW_CENTER_CURSOR GLFW_CENTER_CURSOR
#define WINDOW_TRANSPARENT_FRAMEBUFFER GLFW_TRANSPARENT_FRAMEBUFFER
#define WINDOW_FOCUS_ON_SHOW GLFW_FOCUS_ON_SHOW
#define WINDOW_SCALE_TO_MONITOR GLFW_SCALE_TO_MONITOR

// Shaders
const char* colorVertexShader = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 aColor;\n"
"out vec4 aColor;\n"
"void main() {\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* colorFragmentShader = "#version 330 core\n"
"out vec4 FragColor;"
"in vec4 aColor;\n"
"void main() {\n"
"	FragColor = aColor;\n"
"}\0";

float vertices[] = {
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
};
#ifndef IMPLEMENT_REY_H
struct Window {
#else
struct C_Window {
#endif
	GLFWwindow* windowHandle;
	boolean keys[349];
	const char* title;
	unsigned int colorShader, VBO, VAO;
};
#ifndef IMPLEMENT_REY_H
typedef struct Window Window;
#else
typedef struct C_Window C_Window;
#endif

// Init/deinit funcs
#ifndef IMPLEMENT_REY_H
void initGrey(unsigned int sampleRate) {
#else
void C_initGrey(unsigned int sampleRate) {
#endif
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
#ifndef IMPLEMENT_REY_H
void closeGrey() {
#else
void C_closeGrey() {
#endif
	glfwTerminate();
}

// Window funcs
void framebufferCallback(GLFWwindow* win, int width, int height) {
	glViewport(0, 0, width, height);
}
#ifndef IMPLEMENT_REY_H
Window createWindow(int width, int height, const char* title) {
#else
C_Window C_createWindow(int width, int height, const char* title) {
#endif
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
#ifndef IMPLEMENT_REY_H
	Window win;
#else
	C_Window win;
#endif
	win.windowHandle = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwSetWindowPos(win.windowHandle, (mode->width / 2) - (width / 2), (mode->height / 2) - (height / 2));
	glfwMakeContextCurrent(win.windowHandle);
	glfwSetFramebufferSizeCallback(win.windowHandle, framebufferCallback);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	win.title = title;
	
	glGenBuffers(1, &win.VBO);
	glGenVertexArrays(1, &win.VAO);
	glBindVertexArray(win.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, win.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
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
	unsigned int w_colorFragmentShader = glCreateShader(GL_VERTEX_SHADER);
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
#ifndef IMPLEMENT_REY_H
boolean shouldWindowClose(Window win) {
#else
boolean C_shouldWindowClose(C_Window win) {
#endif
	return glfwWindowShouldClose(win.windowHandle);
}
#ifndef IMPLEMENT_REY_H
void updateWindow(Window* win) {
#else
void C_updateWindow(C_Window* win) {
#endif
	glfwSetWindowTitle(win->windowHandle, win->title);
	glfwPollEvents();
	for (int i = 0; i < sizeof(win->keys)/sizeof(win->keys[0]); i++) {
		win->keys[i] = glfwGetKey(win->windowHandle, i);
	}
}
#ifndef IMPLEMENT_REY_H
void renderWindow(Window win) {
#else
void C_renderWindow(C_Window win) {
#endif
	glBindBuffer(GL_ARRAY_BUFFER, win.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(win.VAO);
	glUseProgram(win.colorShader);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glfwSwapBuffers(win.windowHandle);
}
#ifndef IMPLEMENT_REY_H
void closeWindow(Window win) {
#else
void C_closeWindow(C_Window win) {
#endif
	glfwSetWindowShouldClose(win.windowHandle, GLFW_TRUE);
}
#ifndef IMPLEMENT_REY_H
void setWindowFlag(Window win, uint32_t flag, boolean state) {
#else
void C_setWindowFlag(C_Window win, uint32_t flag, boolean state) {
#endif
	glfwSetWindowAttrib(win.windowHandle, flag, state);
}

// Key input
#ifndef IMPLEMENT_REY_H
boolean isKeyDown(Window win, int key) {
#else
boolean C_isKeyDown(C_Window win, int key) {
#endif
	if (key<sizeof(win.keys)/sizeof(win.keys[0])) {
		return win.keys[key];
	}
	return 0;
}

// Draw funcs
#ifndef IMPLEMENT_REY_H
void clearWindowBackground(Window win, float R, float G, float B, float A) {
#else
void C_clearWindowBackground(C_Window win, float R, float G, float B, float A) {
#endif
	glfwMakeContextCurrent(win.windowHandle);
	glClearColor(R/255, G/255, B/255, A/255);
	glClear(GL_COLOR_BUFFER_BIT);
}