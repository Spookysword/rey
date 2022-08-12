#pragma once

#ifdef __cplusplus
namespace grey {
    // A color, AKA an array of 4 unsigned ints (R, G, B, A), all 0 -> 255.
    class Color {
    public:
        unsigned int r, g, b, a;
        Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
        Color(unsigned int r, unsigned int g, unsigned int b) {
        Color(r, g, b, 255);
    }
        Color() {
        Color(255, 255, 255, 255);
    }
        Color(Color* pColor) {
        r = pColor->r;
        g = pColor->g;
        b = pColor->b;
        a = pColor->a;
    }
        unsigned int operator[](int i) const {
        switch (i) {
            case 0:
                return r;
                break;
            case 1:
                return g;
                break;
            case 2:
                return b;
                break;
            case 3:
                return a;
                break;
            default:
                return 0.0f;
                break;
        }
    }
    };
}
#else
    // A color, AKA an array of 4 unsigned ints (R, G, B, A), all 0 -> 255.
	typedef unsigned int Color[4];
#endif
    // Takes the memory address of a color and replaces it with another color. Essentially, oldColor = newColor for nerds using C.
    #ifdef __cplusplus
namespace grey {
#endif
	void setColor(Color* oldColor, Color newColor);
    #ifdef __cplusplus
}
#endif

#ifdef __cplusplus
	// Chromakey
#define COLOR_BLACK new Color{ 0, 0, 0, 255 }
#define COLOR_WHITE new Color{ 255, 255, 255, 255 }
#define COLOR_LIGHT_GREY new Color{ 128, 128, 128, 255 }
#define COLOR_DARK_GREY new Color{ 63, 63, 63, 255 }
#define COLOR_GREY new Color{ 15, 15, 15, 255 }
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


#else

	// Chromakey
#define COLOR_BLACK (unsigned int [4]){ 0, 0, 0, 255 }
#define COLOR_WHITE (unsigned int [4]){ 255, 255, 255, 255 }
#define COLOR_LIGHT_GREY (unsigned int [4]){ 128, 128, 128, 255 }
#define COLOR_DARK_GREY (unsigned int [4]){ 63, 63, 63, 255 }
#define COLOR_GREY (unsigned int [4]){ 15, 15, 15, 255 }
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