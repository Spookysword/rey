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

void df(struct Button* button) {
	return;
}

Button createButton(double x, double y, double width, double height) {
	Style s = { STYLE_SHAPE_RECT, 0, { 200, 200, 200, 255 }, { 255, 255, 255, 255 } , { 150, 150, 150, 255 } };
	Button b = { x, y, width, height, s, BUTTON_HOVER_STATE_OFF, BUTTON_MOUSE_STATE_OFF, df, df, df, df, df, df };
	return b;
}

void renderButton(Window win, Button* button) {
	button->onUpdate(button);
	unsigned int drawColor[4];

	if (win.mouse.x < button->x + button->width && win.mouse.x + 1 > button->x && win.mouse.y < button->y + button->height && win.mouse.y + 1 > button->y) {
		if (button->hoverState == BUTTON_HOVER_STATE_OFF) {
			button->onHoverOn(button);
		}
		button->hoverState = BUTTON_HOVER_STATE_ON;
		if (win.mouse.isPrimaryDown) {
			if (button->clickState == BUTTON_MOUSE_STATE_OFF) {
				button->onMouseDown(button);
			}
			button->clickState = BUTTON_MOUSE_STATE_ON;
			setColor(&drawColor, button->style.clickedColor);
		}
		else {
			if (button->clickState == BUTTON_MOUSE_STATE_ON) {
				button->onMouseUp(button);
			}
			button->clickState = BUTTON_MOUSE_STATE_OFF;
			setColor(&drawColor, button->style.hoverColor);
		}
	}
	else {
		if (button->hoverState == BUTTON_HOVER_STATE_ON) {
			button->onHoverOff(button);
		}
		button->hoverState = BUTTON_HOVER_STATE_OFF;
		setColor(&drawColor, button->style.normalColor);
	}
	
	switch (button->style.drawShape) {
	default:
		break;
	case STYLE_SHAPE_RECT:
		drawRectangle(&win, button->x, button->y, button->width, button->height, 0, drawColor);
		break;
	case STYLE_SHAPE_ROUNDED_RECT:
		drawRoundedRect(&win, button->x, button->y, button->width, button->height, button->style.roundedness, 0, drawColor);
		break;
	}

	button->onRender(button);
}