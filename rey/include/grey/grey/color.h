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
    Color operator*(float f) {
        return Color(r * f, g * f, b * f, a * f);
    }
    Color operator-(float f) {
        return Color(r - f, g - f, b - f, a - f);
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
    Color rgb_(unsigned int a) {
        return Color(r, g, b, a);
    }
    Color _gba(unsigned int r) {
        return Color(r, g, b, a);
    }

};

bool operator==(const Color& lhs, const Color& rhs) {
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
}



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
extern const grey::Color COLOR_BLACK;
extern const grey::Color COLOR_WHITE;
extern const grey::Color COLOR_LIGHT_GREY;
extern const grey::Color COLOR_DARK_GREY;
extern const grey::Color COLOR_GREY;
// Primary
extern const grey::Color COLOR_RED;
extern const grey::Color COLOR_GREEN;
extern const grey::Color COLOR_BLUE;
// Secondary
extern const grey::Color COLOR_YELLOW;
extern const grey::Color COLOR_CYAN;
extern const grey::Color COLOR_MAGENTA;
// Tertiary
extern const grey::Color COLOR_ORANGE;
extern const grey::Color COLOR_CHARTREUSE;
extern const grey::Color COLOR_SPRING_GREEN;
extern const grey::Color COLOR_AZURE;
extern const grey::Color COLOR_VIOLET;
extern const grey::Color COLOR_ROSE;

// Soft Primary
extern const grey::Color COLOR_SOFT_RED;
extern const grey::Color COLOR_SOFT_GREEN;
extern const grey::Color COLOR_SOFT_BLUE;
// Soft Secondary
extern const grey::Color COLOR_SOFT_YELLOW;
extern const grey::Color COLOR_SOFT_CYAN;
extern const grey::Color COLOR_SOFT_MAGENTA;
// Soft Tertiary
extern const grey::Color COLOR_SOFT_ORANGE;
extern const grey::Color COLOR_SOFT_CHARTREUSE;
extern const grey::Color COLOR_SOFT_SPRING_GREEN;
extern const grey::Color COLOR_SOFT_AZURE;
extern const grey::Color COLOR_SOFT_VIOLET;
extern const grey::Color COLOR_SOFT_ROSE;

// Miscellaneous
extern const grey::Color COLOR_DISCORD;
extern const grey::Color COLOR_SIMPLE;
extern const grey::Color COLOR_BROWN;


#else

	// Chromakey
extern const Color COLOR_BLACK;
extern const Color COLOR_WHITE;
extern const Color COLOR_LIGHT_GREY;
extern const Color COLOR_DARK_GREY;
extern const Color COLOR_GREY;
// Primary
extern const Color COLOR_RED;
extern const Color COLOR_GREEN;
extern const Color COLOR_BLUE;
// Secondary
extern const Color COLOR_YELLOW;
extern const Color COLOR_CYAN;
extern const Color COLOR_MAGENTA;
// Tertiary
extern const Color COLOR_ORANGE;
extern const Color COLOR_CHARTREUSE;
extern const Color COLOR_SPRING_GREEN;
extern const Color COLOR_AZURE;
extern const Color COLOR_VIOLET;
extern const Color COLOR_ROSE;

// Soft Primary
extern const Color COLOR_SOFT_RED;
extern const Color COLOR_SOFT_GREEN;
extern const Color COLOR_SOFT_BLUE;
// Soft Secondary
extern const Color COLOR_SOFT_YELLOW;
extern const Color COLOR_SOFT_CYAN;
extern const Color COLOR_SOFT_MAGENTA;
// Soft Tertiary
extern const Color COLOR_SOFT_ORANGE;
extern const Color COLOR_SOFT_CHARTREUSE;
extern const Color COLOR_SOFT_SPRING_GREEN;
extern const Color COLOR_SOFT_AZURE;
extern const Color COLOR_SOFT_VIOLET;
extern const Color COLOR_SOFT_ROSE;

// Miscellaneous
extern const Color COLOR_DISCORD;
extern const Color COLOR_SIMPLE;

#endif