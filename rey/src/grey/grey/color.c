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
const Color COLOR_BLACK = (Color){ 0, 0, 0, 255 };
const Color COLOR_WHITE = (Color){ 255, 255, 255, 255 };
const Color COLOR_LIGHT_GREY = (Color){ 128, 128, 128, 255 };
const Color COLOR_DARK_GREY = (Color){ 63, 63, 63, 255 };
const Color COLOR_GREY = (Color){ 15, 15, 15, 255 };
// Primary
const Color COLOR_RED = (Color){ 255, 0, 0, 255 };
const Color COLOR_GREEN = (Color){ 0, 255, 0, 255 };
const Color COLOR_BLUE = (Color){ 0, 0, 255, 255 };
// Secondary
const Color COLOR_YELLOW = (Color){ 255, 255, 0, 255 };
const Color COLOR_CYAN = (Color){ 0, 255, 255, 255 };
const Color COLOR_MAGENTA = (Color){ 255, 0, 255, 255 };
// Tertiary
const Color COLOR_ORANGE = (Color){ 255, 128, 0, 255 };
const Color COLOR_CHARTREUSE = (Color){ 128, 255, 0, 255 };
const Color COLOR_SPRING_GREEN = (Color){ 0, 255, 128, 255 };
const Color COLOR_AZURE = (Color){ 0, 128, 255, 255 };
const Color COLOR_VIOLET = (Color){ 128, 0, 255, 255 };
const Color COLOR_ROSE = (Color){ 255, 0, 128, 255 };

// Soft Primary
const Color COLOR_SOFT_RED = (Color){ 255, 50, 50, 255 };
const Color COLOR_SOFT_GREEN = (Color){ 50, 255, 50, 255 };
const Color COLOR_SOFT_BLUE = (Color){ 50, 50, 255, 255 };
// Soft Secondary
const Color COLOR_SOFT_YELLOW = (Color){ 255, 255, 50, 255 };
const Color COLOR_SOFT_CYAN = (Color){ 50, 255, 255, 255 };
const Color COLOR_SOFT_MAGENTA = (Color){ 255, 50, 255, 255 };
// Soft Tertiary
const Color COLOR_SOFT_ORANGE = (Color){ 255, 128, 50, 255 };
const Color COLOR_SOFT_CHARTREUSE = (Color){ 128, 255, 50, 255 };
const Color COLOR_SOFT_SPRING_GREEN = (Color){ 50, 255, 128, 255 };
const Color COLOR_SOFT_AZURE = (Color){ 50, 128, 255, 255 };
const Color COLOR_SOFT_VIOLET = (Color){ 128, 50, 255, 255 };
const Color COLOR_SOFT_ROSE = (Color){ 255, 50, 128, 255 };

// Miscellaneous
const Color COLOR_DISCORD = (Color){ 54, 57, 63, 255 };
const Color COLOR_SIMPLE = (Color){ 0, 159, 141, 255 };

#endif

#ifdef __cplusplus
namespace grey {
#endif
	void setColor(Color* oldColor, Color newColor) {
    #ifdef __cplusplus
	    *oldColor = newColor;
    #else
        oldColor[0][0] = newColor[0];
        oldColor[0][1] = newColor[1];
        oldColor[0][2] = newColor[2];
        oldColor[0][3] = newColor[3];
    #endif
}
#ifdef __cplusplus
}
#endif