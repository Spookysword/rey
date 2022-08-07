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

	// Loads a font and returns the ID of it. The size indicates the resolution the font is intended to be rendered at in pixels.
	FontID loadFont(Window* win, const char* filePath, float size);
	// Deletes the specified font from memory.
	void deleteFont(Window* win, FontID font);

	// Starts up all graphics. "sampleRate" controls the amount of anti-aliasing planned to be used.
	void initGrey(unsigned int sampleRate);
	// Frees up any possibly used memory.
	void closeGrey();
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