#include <grey/grey.h>

#define STYLE_SHAPE_RECT 0
#define STYLE_SHAPE_ROUNDED_RECT 1

#define BUTTON_HOVER_STATE_OFF 0
#define BUTTON_HOVER_STATE_ON 1

#define BUTTON_MOUSE_STATE_OFF 0
#define BUTTON_MOUSE_STATE_ON 1

struct Style {
	unsigned int drawShape;
	unsigned int roundedness;
	unsigned int normalColor[4];
	unsigned int hoverColor[4];
	unsigned int clickedColor[4];
};
typedef struct Style Style;

struct Button {
	double x, y, width, height;
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