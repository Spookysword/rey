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
#include "grey/grey/shaders.h"
#include "grey/grey/vertices.h"

#ifndef CIRCLE_ACCURACY
#define CIRCLE_ACCURACY 360
#endif
#ifdef __cplusplus
namespace grey {
#endif
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. A mouse struct.
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

    // SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. The current shader that the window is using to render.
    int currentShader;
    // SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. The shader vector the window uses.
    CustomShaderVec shaders;
    // The time the window was created.
    float startTime;
    // How long the window has existed.
    float time;
    // The background color of the window.
    Color backgroundColor;
    // The mouse relative to the window.
    Mouse mouse;
    // The offset everything in the window renders at.
    Vec3 offset;
    // The camera struct the window uses.
    Camera camera;
    // The transform struct the window uses.
    Transform transform;
    // Whether the mouse is locked or not.
    boolean mouseLocked;
};
typedef struct Window Window;

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

// Draws a 3D shape with the vertices and texture passed in.
void draw3DShape(Window* win, Texture texture, Vertices vertices);

#ifdef __cplusplus
}
#endif