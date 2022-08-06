// https://www.youtube.com/watch?v=1WLYOV7oM_g
#ifndef GREY_H
#define GREY_H
#ifdef __cplusplus
extern "C" {
#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <mrey/mrey.h>
#ifdef _WIN32
#include <Windows.h>
#else
#define boolean unsigned int
#define TRUE 1
#define FALSE 0
#endif
#ifndef CIRCLE_ACCURACY
#define CIRCLE_ACCURACY 360
#endif
#include "grey/grey/shaders.h"
#include "grey/grey/batch.h"
#include "grey/grey/texture_batch.h"
#include "grey/grey/batch_3d.h"
#include "grey/grey/keys.h"
#include "grey/grey/window_flags.h"
#include "grey/grey/color.h"
#include "grey/grey/texture.h"
#include "grey/grey/font.h"
#include "grey/grey/shader.h"
#include "grey/grey/window.h"
#include "grey/grey/font.h"

	// Starts up all graphics. "sampleRate" controls the amount of anti-aliasing planned to be used.
	void initGrey(unsigned int sampleRate);
	// Frees up any possibly used memory.
	void closeGrey();
	void framebufferCallback(GLFWwindow* win, int width, int height);
	// Returns a valid Window struct.
	Window createWindow(int width, int height, const char* title);
	// Deletes the Window from memory. Different from closeWindow, which closes the window.
	void deleteWindow(Window* win);
	// Checks if a Window should be closed.
	boolean shouldWindowClose(Window win);
	// Handles updating the window, including polling events & general variables within the struct.
	void updateWindow(Window* win);
	// Collects every draw call you've made and sends it in a few collective batches.
	void renderWindow(Window win);
	// Closes the Window. Different from deleteWindow, which deletes the Window from memory.
	void closeWindow(Window win);
	// Sets a window flag's state. All the window flags can be found in the grey file near line 149.
	void setWindowFlag(Window win, uint32_t flag, boolean state);
	/*
	Loads a texture. Beware that the file path you link is relative to the .exe, so you need to have the resources within your build file.
	Also, don't forget to call deleteTexture when you aren't going to use it anymore, otherwise it could cause memory leaks!
	Also also, if you don't know what to put for filter, you can put either FILTER_NEAREST or FILTER_LINEAR.
	(For reference, when upscaling/downscaling, FILTER_NEAREST can make it look blurry (better for realistic images), and FILTER_LINEAR can make it look pixelated (better for low-pixel images AKA pixel art).
	*/
	Texture newTexture(Window* win, const char* path, int filter);

	Texture new3DTexture(Window* win, const char* path, int filter);

	Texture blank3DTexture(Window* win);
	/*
	Deloads a texture, freeing up the memory it's using.
	*/
	void deleteTexture(Window* win, Texture texture);

	void delete3DTexture(Window* win, Texture texture);
	/*
	Checks if a certain key is down. All keys can be found in the grey file near line 26.
	Note that this shouldn't be confused with isKeyPressed, which is only valid once on the frame the user clicks.
	*/
	boolean isKeyDown(Window win, int key);
	/*
	Checks if a certain key has been pressed. All keys can be found in the grey file near line 26.
	Note that this shouldn't be confused with isKeyDown, which is valid each frame that the user has the key down.
	*/
	boolean isKeyPressed(Window win, int key);
	// Clears the background with a color. Generally should be called each frame before drawing anything else.
	void clearWindowBackground(Window* win, Color color);
	// Enables or disables wireframe mode, which draws everything as lines.
	void setWireframeMode(Window win, boolean state);
	// Draws a triangle with three given points and a color.
	void drawTriangle(Window* win, float x1, float y1, float x2, float y2, float x3, float y3, Color color);
	// Draws a rectangle. Note that rotation is measured in degrees,
	void drawRectangle(Window* win, float x, float y, float width, float height, float rotation, Color color);
	// Draws a texture. Note that rotation is measured in degrees.
	void drawTexture(Window* win, Texture texture, float x, float y, float width, float height, float rotation, Color color);
	// Draws a circle.
	void drawCircle(Window* win, float x, float y, float radius, Color color);
	// Draws a rounded rectangle.
	void drawRoundedRect(Window* win, float x, float y, float width, float height, float radius, float rotation, Color color);
	// Draws the specified text with the font passed in. Scale controls how many pixels large it is.
	void drawText(Window* win, const char* text, FontID font, float x, float y, float scale, Color color);
	// Draws text but with a border around it. Kinda broken honestly.
	void drawBorderedText(Window* win, const char* text, FontID font, float x, float y, float scale, float borderSize, Color color, Color borderColor);
	// Gets the total width, in pixels, of the specified text.
	float getWidthOfText(Window* win, const char* text, FontID font, float scale);
	// Gets the width, in pixels, of the specified character of a font.
	float getWidthOfChar(Window* win, char text, FontID font, float scale);
	// Get the height, in pixels, of the specified text.
	float getHeightOfText(Window* win, const char* text, FontID font, float scale);
	// Draws a polygon with the given coordinates.
	void drawPolygon(Window* win, float* xs, float* ys, int points, Color color);
	// Draws a rectangle with all of the four points' colors specified.
	void drawAdvancedRect(Window* win, float x, float y, float width, float height, float rotation, Color topLeft, Color topRight, Color bottomLeft, Color bottomRight);
	// Draws a triangle with all of the trhee points' colors specified.
	void drawAdvancedTriangle(Window* win, float x1, float y1, float x2, float y2, float x3, float y3, Color bottomLeft, Color topMiddle, Color bottomRight);
	// Draws a line between the two points given.
	void drawLine(Window* win, float x1, float y1, float x2, float y2, float thickness, Color color);
	// Draws a line with all of the two points' colors specified.
	void drawAdvancedLine(Window* win, float x1, float y1, float x2, float y2, float thickness, Color color1, Color color2);

	// A vertice struct.
	typedef struct Vertice {
		float x, y, z;
		float r, g, b, a;
		float u, v;
		float nx, ny, nz;
	} Vertice;

	// A struct of verticies.
	typedef struct Vertices {
		Vertice* vertices;
		int size;
	} Vertices;

	// Returns a valid vertice struct with the data passed in.
	Vertice Vertice_new(float x, float y, float z, Color color, float u, float v);
	// Returns a valid vertice struct with the data passed in part 2: Electric Boogaloo.
	Vertice Vertice_create(Vec3 pos, Color color, Vec2 uv, Vec3 normal);
	// Draws a 3D shape with the vertices and texture passed in.
	void draw3DShape(Window* win, Texture texture, Vertices vertices);
	// Sets the status of the mouse being locked to true or false.
	void setMouseLocked(Window* win, boolean locked);
	// Sets the mouse position relative to the window.
	void setMousePos(Window* win, float x, float y);
	// Gets the current clipboard text of the user.
	const char* getClipboardText(Window* win);

#ifdef __cplusplus
	// Chromakey
#define COLOR_BLACK new Color{ 0, 0, 0, 255 }
#define COLOR_WHITE new Color{ 255, 255, 255, 255 }
#define COLOR_LIGHT_GREY new Color{ 128, 128, 128, 255 }
#define COLOR_DARK_GREY new Color{ 63, 63, 63, 255 }
#define grey new Color{ 15, 15, 15, 255 }
// Primary
#define COLOR_RED  new Color{ 255, 0, 0, 255 }
#define COLOR_GREEN new Color{ 0, 255, 0, 255 }
#define COLOR_BLUE new Color{ 0, 0, 255, 255 }
// Secondary
#define COLOR_YELLOW new Color{ 255, 255, 0, 255 }
#define COLOR_CYAN new Color{ 0, 255, 255, 255 }
#define COLOR_MAGENTA new Color{ 255, 0, 255, 255 }
// Tertiary
#define COLOR_ORANGE new Color{ 255, 128, 0, 255 }
#define COLOR_CHARTREUSE new Color{ 128, 255, 0, 255 }
#define COLOR_SPRING_GREEN new Color{ 0, 255, 128, 255 }
#define COLOR_AZURE new Color{ 0, 128, 255, 255 }
#define COLOR_VIOLET new Color{ 128, 0, 255, 255 }
#define COLOR_ROSE new Color{ 255, 0, 128, 255 }

// Soft Primary
#define COLOR_SOFT_RED new Color{ 255, 50, 50, 255 }
#define COLOR_SOFT_GREEN new Color{ 50, 255, 50, 255 }
#define COLOR_SOFT_BLUE new Color{ 50, 50, 255, 255 }
// Soft Secondary
#define COLOR_SOFT_YELLOW new Color{ 255, 255, 50, 255 }
#define COLOR_SOFT_CYAN new Color{ 50, 255, 255, 255 }
#define COLOR_SOFT_MAGENTA new Color{ 255, 50, 255, 255 }
// Soft Tertiary
#define COLOR_SOFT_ORANGE new Color{ 255, 128, 50, 255 }
#define COLOR_SOFT_CHARTREUSE new Color{ 128, 255, 50, 255 }
#define COLOR_SOFT_SPRING_GREEN new Color{ 50, 255, 128, 255 }
#define COLOR_SOFT_AZURE new Color{ 50, 128, 255, 255 }
#define COLOR_SOFT_VIOLET new Color{ 128, 50, 255, 255 }
#define COLOR_SOFT_ROSE new Color{ 255, 50, 128, 255 }

// Miscellaneous
#define COLOR_DISCORD new Color{ 54, 57, 63, 255 }
#define COLOR_SIMPLE new Color{ 0, 159, 141, 255 }
#define COLOR_BROWN new Color{ 165, 42, 42, 255 }

}

#else

	// Chromakey
#define COLOR_BLACK (unsigned int [4]){ 0, 0, 0, 255 }
#define COLOR_WHITE (unsigned int [4]){ 255, 255, 255, 255 }
#define COLOR_LIGHT_GREY (unsigned int [4]){ 128, 128, 128, 255 }
#define COLOR_DARK_GREY (unsigned int [4]){ 63, 63, 63, 255 }
#define grey (unsigned int [4]){ 15, 15, 15, 255 }
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