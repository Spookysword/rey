#include "grey/grey/color.h"
#ifdef __cplusplus
// Chromakey
const grey::Color COLOR_BLACK = new Color{ 0, 0, 0, 255 };
const grey::Color COLOR_WHITE = new Color{ 255, 255, 255, 255 };
const grey::Color COLOR_LIGHT_GREY = new Color{ 128, 128, 128, 255 };
const grey::Color COLOR_DARK_GREY = new Color{ 63, 63, 63, 255 };
const grey::Color COLOR_GREY = new Color{ 15, 15, 15, 255 };
// Primary
const grey::Color COLOR_RED  = new Color{ 255, 0, 0, 255 };
const grey::Color COLOR_GREEN = new Color{ 0, 255, 0, 255 };
const grey::Color COLOR_BLUE = new Color{ 0, 0, 255, 255 };
// Secondary
const grey::Color COLOR_YELLOW = new Color{ 255, 255, 0, 255 };
const grey::Color COLOR_CYAN = new Color{ 0, 255, 255, 255 };
const grey::Color COLOR_MAGENTA = new Color{ 255, 0, 255, 255 };
// Tertiary
const grey::Color COLOR_ORANGE = new Color{ 255, 128, 0, 255 };
const grey::Color COLOR_CHARTREUSE = new Color{ 128, 255, 0, 255 };
const grey::Color COLOR_SPRING_GREEN = new Color{ 0, 255, 128, 255 };
const grey::Color COLOR_AZURE = new Color{ 0, 128, 255, 255 };
const grey::Color COLOR_VIOLET = new Color{ 128, 0, 255, 255 };
const grey::Color COLOR_ROSE = new Color{ 255, 0, 128, 255 };

// Soft Primary
const grey::Color COLOR_SOFT_RED = new Color{ 255, 50, 50, 255 };
const grey::Color COLOR_SOFT_GREEN = new Color{ 50, 255, 50, 255 };
const grey::Color COLOR_SOFT_BLUE = new Color{ 50, 50, 255, 255 };
// Soft Secondary
const grey::Color COLOR_SOFT_YELLOW = new Color{ 255, 255, 50, 255 };
const grey::Color COLOR_SOFT_CYAN = new Color{ 50, 255, 255, 255 };
const grey::Color COLOR_SOFT_MAGENTA = new Color{ 255, 50, 255, 255 };
// Soft Tertiary
const grey::Color COLOR_SOFT_ORANGE = new Color{ 255, 128, 50, 255 };
const grey::Color COLOR_SOFT_CHARTREUSE = new Color{ 128, 255, 50, 255 };
const grey::Color COLOR_SOFT_SPRING_GREEN = new Color{ 50, 255, 128, 255 };
const grey::Color COLOR_SOFT_AZURE = new Color{ 50, 128, 255, 255 };
const grey::Color COLOR_SOFT_VIOLET = new Color{ 128, 50, 255, 255 };
const grey::Color COLOR_SOFT_ROSE = new Color{ 255, 50, 128, 255 };

// Miscellaneous
const grey::Color COLOR_DISCORD = new Color{ 54, 57, 63, 255 };
const grey::Color COLOR_SIMPLE = new Color{ 0, 159, 141, 255 };
const grey::Color COLOR_BROWN = new Color{ 165, 42, 42, 255 };


#else

	// Chromakey
const Color COLOR_BLACK = { 0, 0, 0, 255 };
const Color COLOR_WHITE = { 255, 255, 255, 255 };
const Color COLOR_LIGHT_GREY = { 128, 128, 128, 255 };
const Color COLOR_DARK_GREY = { 63, 63, 63, 255 };
const Color COLOR_GREY = { 15, 15, 15, 255 };
// Primary
const Color COLOR_RED = { 255, 0, 0, 255 };
const Color COLOR_GREEN = { 0, 255, 0, 255 };
const Color COLOR_BLUE = { 0, 0, 255, 255 };
// Secondary
const Color COLOR_YELLOW = { 255, 255, 0, 255 };
const Color COLOR_CYAN = { 0, 255, 255, 255 };
const Color COLOR_MAGENTA = { 255, 0, 255, 255 };
// Tertiary
const Color COLOR_ORANGE = { 255, 128, 0, 255 };
const Color COLOR_CHARTREUSE = { 128, 255, 0, 255 };
const Color COLOR_SPRING_GREEN = { 0, 255, 128, 255 };
const Color COLOR_AZURE = { 0, 128, 255, 255 };
const Color COLOR_VIOLET = { 128, 0, 255, 255 };
const Color COLOR_ROSE = { 255, 0, 128, 255 };

// Soft Primary
const Color COLOR_SOFT_RED = { 255, 50, 50, 255 };
const Color COLOR_SOFT_GREEN = { 50, 255, 50, 255 };
const Color COLOR_SOFT_BLUE = { 50, 50, 255, 255 };
// Soft Secondary
const Color COLOR_SOFT_YELLOW = { 255, 255, 50, 255 };
const Color COLOR_SOFT_CYAN = { 50, 255, 255, 255 };
const Color COLOR_SOFT_MAGENTA = { 255, 50, 255, 255 };
// Soft Tertiary
const Color COLOR_SOFT_ORANGE = { 255, 128, 50, 255 };
const Color COLOR_SOFT_CHARTREUSE = { 128, 255, 50, 255 };
const Color COLOR_SOFT_SPRING_GREEN = { 50, 255, 128, 255 };
const Color COLOR_SOFT_AZURE = { 50, 128, 255, 255 };
const Color COLOR_SOFT_VIOLET = { 128, 50, 255, 255 };
const Color COLOR_SOFT_ROSE = { 255, 50, 128, 255 };

// Miscellaneous
const Color COLOR_DISCORD = { 54, 57, 63, 255 };
const Color COLOR_SIMPLE = { 0, 159, 141, 255 };

#endif

#ifdef __cplusplus
namespace grey {
#endif
	void setColor(Color* oldColor, Color newColor) {
    #ifdef __cplusplus
	    *oldColor = newColor;
    #else
        oldColor->r = newColor.r;
        oldColor->g = newColor.g;
        oldColor->b = newColor.b;
        oldColor->a = newColor.a;
    #endif
}
#ifdef __cplusplus
}
#endif
