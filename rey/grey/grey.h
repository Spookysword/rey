// https://www.youtube.com/watch?v=1WLYOV7oM_g
#ifndef GREY_H
#define GREY_H
#ifdef __cplusplus
extern "C" {
#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "mrey.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#ifndef CIRCLE_ACCURACY
#define CIRCLE_ACCURACY 360
#endif

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
#define FILTER_NEAREST GL_NEAREST
#define FILTER_LINEAR GL_LINEAR

// A color, AKA an array of 4 unsigned ints (R, G, B, A), all 0 -> 255.
typedef unsigned int Color[4];
// A texture, which is really just an ID of the texture.
typedef unsigned int Texture;

struct C_Batch {
	GLuint VAO, VBO;
	C_floatVec triangles;
	int verticeCount, stack;
	C_intVec shapeVertices;
};
typedef struct C_Batch C_Batch;

struct C_TextureBatch {
	GLuint VAO, VBO, textureID;
	C_floatVec triangles;
	int verticeCount, stack;
	C_intVec shapeVertices;
};
typedef struct C_TextureBatch C_TextureBatch;

void C_addVertice(C_Batch* batch, float verts[7]);
void C_addTriangle(C_Batch* batch, float verts[21]);
void C_endShape(C_Batch* batch);
void C_draw(C_Batch batch, GLenum type);
C_Batch C_createBatch();
void C_bindBatch(C_Batch batch);
void C_flushBatch(C_Batch* batch);
void C_deleteBatch(C_Batch* batch);

void C_addTextureVertice(C_TextureBatch* batch, float verts[9]);
void C_addTextureTriangle(C_TextureBatch* batch, float verts[27]);
void C_endTextureShape(C_TextureBatch* batch);
void C_drawTextureBatch(C_TextureBatch batch, GLenum type);
C_TextureBatch C_createTextureBatch(const char* filePath, int filter);
void C_bindTextureBatch(C_TextureBatch batch);
void C_flushTextureBatch(C_TextureBatch* batch);
void C_deleteTextureBatch(C_TextureBatch* batch);

struct C_textureVec {
	C_TextureBatch* data;
	int size;
	int limit;
};
typedef struct C_textureVec C_textureVec;

C_textureVec C_textureVecCreate();
void C_textureVecPushBack(C_textureVec* vec, C_TextureBatch num);
void C_textureVecClear(C_textureVec* vec);
void C_textureVecDelete(C_textureVec* vec);

struct C_Camera {
	float x, y, z;
};
typedef struct C_Camera C_Camera;

FT_Library FT;

struct C_Character {
	unsigned int ID;
	char character;
	float sizeX, sizeY;
	float bearingX, bearingY;
	unsigned int advance;
	C_TextureBatch batch;
};
typedef struct C_Character C_Character;
struct C_Font {
	FT_Face face;
	C_Character characters[128];
};
typedef struct C_Font C_Font;

// A window struct. You can use multiple if you're wondering, by the way.
struct C_Window {
	// The GLFW window obj for the window. Shouldn't be used unless directly using OpenGL functions.
	GLFWwindow* windowHandle;
	// A list of all of the keys and if they're pressed or not. Shouldn't be used, instead use isKeyDown()
	boolean keys[349];
	// A list of all of the keys and if they were clicked first on this frame. Shouldn't be used, instead use isKeyPressed()
	boolean tempKeys[349];
	// Used to check if a key has been clicked. Shouldn't be used.
	boolean tempKeysCheck[349];
	// The window's title. You can use this to change the window's title or get it with no functions needed (pretty cool amiright)
	const char* title;
	// The int passed to OpenGL that's used to draw basic color objects. Shouldn't be used unless directly using OpenGL functions.
	unsigned int colorShader;
	// The int passed to OpenGL that's used to draw textures. Shouldn't be used unless directly using OpenGL functions.
	unsigned int textureShader;
	// The window's width. You can use this to change the window's width or get it with no functions needed (pretty cool amiright)
	unsigned int width;
	// The window's height. You can use this to change the window's height or get it with no functions needed (pretty cool amiright)
	unsigned int height;
	// The batch that's used to draw all basic shapes. Shouldn't be used unless directly using openGL functions.
	C_Batch shapeBatch;
	// The time since the last frame happened. Multiplying values by this makes the value frame independent, meaning that it moves at the same rate of change regardless of the FPS.
	float deltaTime;
	// Value used to calculate deltaTime and shouldn't be used or modified.
	float lastFrame;
	// Value used to calculate deltaTime and shouldn't be used or modified.
	float currentFrame;
	// The Z-value used to draw items in order despite being sent in different batches.
	float zmod;
	// Used to store vars for fullscreen info and shouldn't be used or modified.
	int prevX, prevY, prevWidth, prevHeight;
	// Whether or not the window is fullscreen. You can use this to change the window's fullscreen status or get it with no functions needed (pretty cool amiright)
	boolean fullscreen;
	// Value used to manage the "fullscreen" var and shouldn't be used or modified.
	boolean priorFullscreen;
	// The vector used to hold all of the textures and their respective batch info. Shouldn't be used.
	C_textureVec textures;
	// The camera used to project everything. It has modifiable x, y, & z values.
	C_Camera camera;
	// The amount of times the frame has been drawn in the last second. May not be 100% accurate and change rapidly.
	float framesPerSecond;

	C_Font arial;
	unsigned int fontShader;
};
typedef struct C_Window C_Window;

// Starts up all graphics. "sampleRate" controls the amount of anti-aliasing planned to be used.
void C_initGrey(unsigned int sampleRate);
	// Frees up any possibly used memory.
void C_closeGrey();
void framebufferCallback(GLFWwindow* win, int width, int height);
// Returns a valid Window struct.
C_Window C_createWindow(int width, int height, const char* title);
// Deletes the Window from memory. Different from closeWindow, which closes the window.
void C_deleteWindow(C_Window* win);
// Checks if a Window should be closed.
boolean C_shouldWindowClose(C_Window win);
// Handles updating the window, including polling events & general variables within the struct.
void C_updateWindow(C_Window* win);
// Collects every draw call you've made and sends it in a few collective batches.
void C_renderWindow(C_Window win);
// Closes the Window. Different from deleteWindow, which deletes the Window from memory.
void C_closeWindow(C_Window win);
// Sets a window flag's state. All the window flags can be found in the grey file near line 149.
void C_setWindowFlag(C_Window win, uint32_t flag, boolean state);
/*
Loads a texture. Beware that the file path you link is relative to the .exe, so you need to have the resources within your build file.
Also, don't forget to call deleteTexture when you aren't going to use it anymore, otherwise it could cause memory leaks!
Also also, if you don't know what to put for filter, you can put either FILTER_NEAREST or FILTER_LINEAR.
(For reference, when upscaling/downscaling, FILTER_NEAREST can make it look blurry (better for realistic images), and FILTER_LINEAR can make it look pixelated (better for low-pixel images AKA pixel art).
*/
Texture c_newTexture(C_Window* win, const char* path, int filter);
/*
Deloads a texture, freeing up the memory it's using.
*/
void c_deleteTexture(C_Window* win, Texture texture);
/*
Checks if a certain key is down. All keys can be found in the grey file near line 26.
Note that this shouldn't be confused with isKeyPressed, which is only valid once on the frame the user clicks.
*/
boolean C_isKeyDown(C_Window win, int key);
/*
Checks if a certain key has been pressed. All keys can be found in the grey file near line 26.
Note that this shouldn't be confused with isKeyDown, which is valid each frame that the user has the key down.
*/
boolean C_isKeyPressed(C_Window win, int key);
// Clears the background with a color. Generally should be called each frame before drawing anything else.
void C_clearWindowBackground(C_Window win, Color color);
// Enables or disables wireframe mode, which draws everything as lines.
void C_setWireframeMode(C_Window win, boolean state);
// Draws a triangle with three given points and a color.
void C_drawTriangle(C_Window* win, float x1, float y1, float x2, float y2, float x3, float y3, Color color);
// Draws a rectangle. Note that rotation is measured in degrees,
void C_drawRectangle(C_Window* win, float x, float y, float width, float height, float rotation, Color color);
// Draws a texture. Note that rotation is measured in degrees.
void C_drawTexture(C_Window* win, Texture texture, float x, float y, float width, float height, float rotation, Color color);
// Draws a circle.
void C_drawCircle(C_Window* win, float x, float y, float radius, Color color);
// Draws a rounded rectangle.
void C_drawRoundedRect(C_Window* win, float x, float y, float width, float height, float radius, float rotation, Color color);

#ifndef IMPLEMENT_GREY_H

// Clears the background with a color. Generally should be called each frame before drawing anything else.
#define clearWindowBackground C_clearWindowBackground
// Enables or disables wireframe mode, which draws everything as lines.
#define setWireframeMode C_setWireframeMode
/*
Checks if a certain key is down. All keys can be found in the grey file near line 26.
Note that this shouldn't be confused with isKeyPressed, which is only valid once on the frame the user clicks.
*/
#define isKeyDown C_isKeyDown
/*
Checks if a certain key has been pressed. All keys can be found in the grey file near line 26.
Note that this shouldn't be confused with isKeyDown, which is valid each frame that the user has the key down.
*/
#define isKeyPressed C_isKeyPressed
// Sets a window flag's state. All the window flags can be found in the grey file near line 149.
#define setWindowFlag C_setWindowFlag
/*
Loads a texture. Beware that the file path you link is relative to the .exe, so you need to have the resources within your build file.
Also, don't forget to call deleteTexture when you aren't going to use it anymore, otherwise it could cause memory leaks!
*/
#define newTexture c_newTexture
/*
Deloads a texture, freeing up the memory it's using.
*/
#define deleteTexture c_deleteTexture
// Closes the Window. Different from deleteWindow, which deletes the Window from memory.
#define closeWindow C_closeWindow
// Deletes the Window from memory. Different from closeWindow, which closes the window.
#define deleteWindow C_deleteWindow
// Collects every draw call you've made and sends it in a few collective batches.
#define renderWindow C_renderWindow
// Handles updating the window, including polling events & general variables within the struct.
#define updateWindow C_updateWindow
// Checks if a Window should be closed.
#define shouldWindowClose C_shouldWindowClose
// Returns a valid Window struct.
#define createWindow C_createWindow
// Frees up any possibly used memory.
#define closeGrey C_closeGrey
// Starts up all graphics. "sampleRate" controls the amount of anti-aliasing planned to be used.
#define initGrey C_initGrey

#define Camera C_Camera
// A window struct. You can use multiple if you're wondering, by the way.
#define Window C_Window
// Draws a triangle with three given points and a color.
#define drawTriangle C_drawTriangle
// Draws a rectangle. Note that rotation is measured in degrees.
#define drawRectangle C_drawRectangle
// Draws a texture. Note that rotation is measured in degrees.
#define drawTexture C_drawTexture
// Draws a circle.
#define drawCircle C_drawCircle
// Draws a rounded rectangle.
#define drawRoundedRect C_drawRoundedRect

#endif

#ifdef __cplusplus
// Chromakey
#define COLOR_BLACK Color{ 0, 0, 0, 255 }
#define COLOR_WHITE Color{ 255, 255, 255, 255 }
#define COLOR_LIGHT_GREY Color{ 128, 128, 128, 255 }
#define COLOR_DARK_GREY Color{ 63, 63, 63, 255 }
#define grey Color{ 14, 14, 14, 255 }
// Primary
#define COLOR_RED Color{ 255, 0, 0, 255 }
#define COLOR_GREEN Color{ 0, 255, 0, 255 }
#define COLOR_BLUE Color{ 0, 0, 255, 255 }
// Secondary
#define COLOR_YELLOW Color{ 255, 255, 0, 255 }
#define COLOR_CYAN Color{ 0, 255, 255, 255 }
#define COLOR_MAGENTA Color{ 255, 0, 255, 255 }
// Tertiary
#define COLOR_ORANGE Color{ 255, 128, 0, 255 }
#define COLOR_CHARTREUSE Color{ 128, 255, 0, 255 }
#define COLOR_SPRING_GREEN Color{ 0, 255, 128, 255 }
#define COLOR_AZURE Color){ 0, 128, 255, 255 }
#define COLOR_VIOLET Color{ 128, 0, 255, 255 }
#define COLOR_ROSE Color{ 255, 0, 128, 255 }

// Soft Primary
#define COLOR_SOFT_RED Color{ 255, 50, 50, 255 }
#define COLOR_SOFT_GREEN Color{ 50, 255, 50, 255 }
#define COLOR_SOFT_BLUE Color{ 50, 50, 255, 255 }
// Soft Secondary
#define COLOR_SOFT_YELLOW Color{ 255, 255, 50, 255 }
#define COLOR_SOFT_CYAN Color{ 50, 255, 255, 255 }
#define COLOR_SOFT_MAGENTA Color{ 255, 50, 255, 255 }
// Soft Tertiary
#define COLOR_SOFT_ORANGE Color{ 255, 128, 50, 255 }
#define COLOR_SOFT_CHARTREUSE Color{ 128, 255, 50, 255 }
#define COLOR_SOFT_SPRING_GREEN Color{ 50, 255, 128, 255 }
#define COLOR_SOFT_AZURE Color{ 50, 128, 255, 255 }
#define COLOR_SOFT_VIOLET Color{ 128, 50, 255, 255 }
#define COLOR_SOFT_ROSE Color{ 255, 50, 128, 255 }

// Miscellaneous
#define COLOR_DISCORD Color{ 54, 57, 63, 255 }
#define COLOR_SIMPLE Color{ 0, 159, 141, 255 }

}

#else

// Chromakey
#define COLOR_BLACK (unsigned int [4]){ 0, 0, 0, 255 }
#define COLOR_WHITE (unsigned int [4]){ 255, 255, 255, 255 }
#define COLOR_LIGHT_GREY (unsigned int [4]){ 128, 128, 128, 255 }
#define COLOR_DARK_GREY (unsigned int [4]){ 63, 63, 63, 255 }
#define grey (unsigned int [4]){ 14, 14, 14, 255 }
// Primary
#define COLOR_RED (unsigned int [4]){ 255, 0, 0, 255 }
#define COLOR_GREEN (unsigned int [4]){ 0, 255, 0, 255 }
#define COLOR_BLUE (unsigned int [4]){ 0, 0, 255, 255 }
// Secondary
#define COLOR_YELLOW (unsigned int [4]){ 255, 255, 0, 255 }
#define COLOR_CYAN (unsigned int [4]){ 0, 255, 255, 255 }
#define COLOR_MAGENTA (unsigned int [4]){ 255, 0, 255, 255 }
// Tertiary
#define COLOR_ORANGE (unsigned int [4]){ 255, 128, 0, 255 }
#define COLOR_CHARTREUSE (unsigned int [4]){ 128, 255, 0, 255 }
#define COLOR_SPRING_GREEN (unsigned int [4]){ 0, 255, 128, 255 }
#define COLOR_AZURE (unsigned int [4]){ 0, 128, 255, 255 }
#define COLOR_VIOLET (unsigned int [4]){ 128, 0, 255, 255 }
#define COLOR_ROSE (unsigned int [4]){ 255, 0, 128, 255 }

// Soft Primary
#define COLOR_SOFT_RED (unsigned int [4]){ 255, 50, 50, 255 }
#define COLOR_SOFT_GREEN (unsigned int [4]){ 50, 255, 50, 255 }
#define COLOR_SOFT_BLUE (unsigned int [4]){ 50, 50, 255, 255 }
// Soft Secondary
#define COLOR_SOFT_YELLOW (unsigned int [4]){ 255, 255, 50, 255 }
#define COLOR_SOFT_CYAN (unsigned int [4]){ 50, 255, 255, 255 }
#define COLOR_SOFT_MAGENTA (unsigned int [4]){ 255, 50, 255, 255 }
// Soft Tertiary
#define COLOR_SOFT_ORANGE (unsigned int [4]){ 255, 128, 50, 255 }
#define COLOR_SOFT_CHARTREUSE (unsigned int [4]){ 128, 255, 50, 255 }
#define COLOR_SOFT_SPRING_GREEN (unsigned int [4]){ 50, 255, 128, 255 }
#define COLOR_SOFT_AZURE (unsigned int [4]){ 50, 128, 255, 255 }
#define COLOR_SOFT_VIOLET (unsigned int [4]){ 128, 50, 255, 255 }
#define COLOR_SOFT_ROSE (unsigned int [4]){ 255, 50, 128, 255 }

// Miscellaneous
#define COLOR_DISCORD (unsigned int [4]){ 54, 57, 63, 255 }
#define COLOR_SIMPLE (unsigned int [4]){ 0, 159, 141, 255 }

#endif
#endif