#include <grey/grey.h>

#define STYLE_SHAPE_RECT 0
#define STYLE_SHAPE_ROUNDED_RECT 1

#define BUTTON_HOVER_STATE_OFF 0
#define BUTTON_HOVER_STATE_ON 1

#define BUTTON_MOUSE_STATE_OFF 0
#define BUTTON_MOUSE_STATE_ON 1

struct Theme {
	unsigned int buttonBorder[4];
	unsigned int buttonNormal[4];
	unsigned int buttonHover[4];
	unsigned int buttonClicked[4];
};
typedef struct Theme Theme;

struct Style {
	double x, y, width, height;
	unsigned int drawShape;
	unsigned int roundedness;
	unsigned int borderSize;
	unsigned int borderColor[4];
	unsigned int normalColor[4];
	unsigned int hoverColor[4];
	unsigned int clickedColor[4];
};
typedef struct Style Style;

struct Button {
	Style style;
	unsigned int hoverState, clickState;
	void (*onUpdate)(struct Button*);
	void (*onRender)(struct Button*);
	void (*onHoverOn)(struct Button*);
	void (*onHoverOff)(struct Button*);
	void (*onMouseDown)(struct Button*);
	void (*onMouseUp)(struct Button*);
};
typedef struct Button Button;

void df(struct Button* button);

Button createButton(double x, double y, double width, double height);

void renderButton(Window win, Button* button);

struct Slider {
	Style lineStyle;
	Style sliderStyle;
	unsigned int hoverState, clickState;
	double value;
	void (*onUpdate)(struct Slider*);
	void (*onRender)(struct Slider*);
	void (*onHoverOn)(struct Slider*);
	void (*onHoverOff)(struct Slider*);
	void (*onMouseDown)(struct Slider*);
	void (*onMouseUp)(struct Slider*);
};
typedef struct Slider Slider;

Slider createSlider(double x1, double x2, double y, double width, double height, double value);

void renderSlider(Window win, Slider* slider);