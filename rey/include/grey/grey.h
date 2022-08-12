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

#ifdef __cplusplus
namespace grey {
#endif

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
	Checks if a certain key has been pressed. All keys can be found in the keys.h file.
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
}
}
#ifndef GREY_ENABLE_NAMESPACE
using namespace grey;
#endif
#endif

#endif
