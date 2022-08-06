#pragma once

// Actual window flags

// Determines if the window should be resizable or not.
#define WINDOW_RESIZABLE GLFW_RESIZABLE
// Determines if the window should be visible or not.
#define WINDOW_VISIBLE GLFW_VISIBLE
// Determines if the window should have a title bar and border or not.
#define WINDOW_DECORATED GLFW_DECORATED
// Determines if the window should automatically hide itself once alt-tabbed on fullscreen or not.
#define WINDOW_AUTO_ICONIFY GLFW_AUTO_ICONIFY
// Determines if the window should stay above all other windows permanently or not.
#define WINDOW_FLOATING GLFW_FLOATING
// Determines if alpha-channels allow to actually see through the window itself or not.
#define WINDOW_TRANSPARENT_FRAMEBUFFER GLFW_TRANSPARENT_FRAMEBUFFER

// Not window flags but still in here -_-

// https://learnopengl.com/img/getting-started/texture_filtering.png
#define FILTER_NEAREST GL_NEAREST
// https://learnopengl.com/img/getting-started/texture_filtering.png
#define FILTER_LINEAR GL_LINEAR