#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#ifdef _WIN32
#include <Windows.h>
#else
#define boolean unsigned int
#define TRUE 1
#define FALSE 0
#endif
#include "grey/grey/shader.h"
#include "grey/grey/color.h"

struct Mouse {
    double x, y;
    boolean isPrimaryDown, isPrimaryPressed;
    boolean isSecondaryDown, isSecondaryPressed;
    boolean isMiddleDown, isMiddlePressed;
};
typedef struct Mouse Mouse;

// A window struct. You can use multiple if you're wondering, by the way.
struct Window {
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
    // The window's width. You can use this to change the window's width or get it with no functions needed (pretty cool amiright)
    unsigned int width;
    // The window's height. You can use this to change the window's height or get it with no functions needed (pretty cool amiright)
    unsigned int height;
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
    // The amount of times the frame has been drawn in the last second. May not be 100% accurate and change rapidly.
    float framesPerSecond;

    int currentShader;
    CustomShaderVec shaders;
    float startTime;
    float time;
    Color backgroundColor;
    Mouse mouse;
    Vec3 offset;

    Camera camera;
    Transform transform;

    boolean mouseLocked;
};
typedef struct Window Window;

	FontID loadFont(Window* win, const char* filePath, float size);
	void deleteFont(Window* win, FontID font);