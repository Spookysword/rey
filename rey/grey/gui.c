#include <grey/gui.h>

void df(struct Button* button) {
	return;
}

Button createButton(double x, double y, double width, double height) {
	Style s = { x, y, width, height, STYLE_SHAPE_RECT, 0, 0, { 0, 0, 0, 255 }, { 200, 200, 200, 255 }, { 255, 255, 255, 255 } , { 150, 150, 150, 255 } };
	Button b = { s, BUTTON_HOVER_STATE_OFF, BUTTON_MOUSE_STATE_OFF, df, df, df, df, df, df };
	return b;
}

Slider createSlider(double x1, double x2, double y, double width, double height, double value) {
	double position = (x2 - x1) * value;
	Style ls = { x1, y + (height / 3), (x2 - x1), height / 3, STYLE_SHAPE_RECT, 0, 0, { 0, 0, 0, 255 }, { 200, 200, 200, 255 }, { 255, 255, 255, 255 }, { 150, 150, 150, 255 } };
	Style ss = { (x1 - (width / 2)) + position, y, width, height, STYLE_SHAPE_RECT, 0, 0, { 0, 0, 0, 255 }, { 200, 200, 200, 255 }, { 255, 255, 255, 255 }, { 150, 150, 150, 255 } };
	Slider s = { ls, ss, BUTTON_HOVER_STATE_OFF, BUTTON_MOUSE_STATE_OFF, value, df, df, df, df, df, df };
	return s;
}

void renderButton(Window win, Button* button) {
	button->onUpdate(button);
	unsigned int drawColor[4];

	if (win.mouse.x < button->style.x + button->style.width && win.mouse.x + 1 > button->style.x && win.mouse.y < button->style.y + button->style.height && win.mouse.y + 1 > button->style.y) {
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
		drawRectangle(&win, button->style.x, button->style.y, button->style.width, button->style.height, 0, drawColor);
		if (button->style.borderSize > 0) {
			drawRectangle(&win, button->style.x, button->style.y, button->style.width, button->style.borderSize, 0, button->style.borderColor);
			drawRectangle(&win, button->style.x, (button->style.y + button->style.height) - button->style.borderSize, button->style.width, button->style.borderSize, 0, button->style.borderColor);
			drawRectangle(&win, button->style.x, button->style.y + button->style.borderSize, button->style.borderSize, button->style.height - (button->style.borderSize * 2.0), 0, button->style.borderColor);
			drawRectangle(&win, (button->style.x + button->style.width) - button->style.borderSize, button->style.y + button->style.borderSize, button->style.borderSize, button->style.height - (button->style.borderSize * 2.0), 0, button->style.borderColor);
		}
		break;
	case STYLE_SHAPE_ROUNDED_RECT:
		if (button->style.borderSize > 0) {
			drawRoundedRect(&win, button->style.x, button->style.y, button->style.width, button->style.height, button->style.roundedness, 0, button->style.borderColor);
			drawRoundedRect(&win, button->style.x + button->style.borderSize, button->style.y + button->style.borderSize, button->style.width - (button->style.borderSize * 2.0), button->style.height - (button->style.borderSize * 2.0), button->style.roundedness / 2, 0, drawColor);
		}
		else {
			drawRoundedRect(&win, button->style.x, button->style.y, button->style.width, button->style.height, button->style.roundedness, 0, drawColor);
		}
		break;
	}

	button->onRender(button);
}

void renderSlider(Window win, Slider* slider) {
	slider->onUpdate(slider);
	unsigned int drawColor[4];

	if (win.mouse.x < slider->sliderStyle.x + slider->sliderStyle.width && win.mouse.x + 1 > slider->sliderStyle.x && win.mouse.y < slider->sliderStyle.y + slider->sliderStyle.height && win.mouse.y + 1 > slider->sliderStyle.y) {
		if (slider->hoverState == BUTTON_HOVER_STATE_OFF) {
			slider->onHoverOn(slider);
		}
		slider->hoverState = BUTTON_HOVER_STATE_ON;
		if (win.mouse.isPrimaryDown) {
			slider->sliderStyle.x = win.mouse.x - (slider->sliderStyle.width / 2);
			if (slider->clickState == BUTTON_MOUSE_STATE_OFF) {
				slider->onMouseDown(slider);
			}
			slider->clickState = BUTTON_MOUSE_STATE_ON;
			setColor(&drawColor, slider->sliderStyle.clickedColor);
		}
		else {
			if (slider->clickState == BUTTON_MOUSE_STATE_ON) {
				slider->onMouseUp(slider);
			}
			slider->clickState = BUTTON_MOUSE_STATE_OFF;
			setColor(&drawColor, slider->sliderStyle.hoverColor);
		}
	}
	else {
		if (slider->hoverState == BUTTON_HOVER_STATE_ON) {
			slider->onHoverOff(slider);
		}
		slider->hoverState = BUTTON_HOVER_STATE_OFF;
		setColor(&drawColor, slider->sliderStyle.normalColor);
	}

	if (slider->sliderStyle.x < slider->lineStyle.x - (slider->sliderStyle.width / 2)) { slider->sliderStyle.x = slider->lineStyle.x - (slider->sliderStyle.width / 2); }
	else if (slider->sliderStyle.x > (slider->lineStyle.x + slider->lineStyle.width) - (slider->sliderStyle.width / 2)) { slider->sliderStyle.x = (slider->lineStyle.x + slider->lineStyle.width) - (slider->sliderStyle.width / 2); }

	slider->value = (slider->sliderStyle.x - (slider->lineStyle.x - (slider->sliderStyle.width / 2))) / slider->lineStyle.width;
	printf("%lf\n", slider->value);

	switch (slider->lineStyle.drawShape) {
	default:
		break;
	case STYLE_SHAPE_RECT:
		drawRectangle(&win, slider->lineStyle.x, slider->lineStyle.y, slider->lineStyle.width, slider->lineStyle.height, 0, slider->lineStyle.normalColor);
		break;
	case STYLE_SHAPE_ROUNDED_RECT:
		drawRoundedRect(&win, slider->lineStyle.x, slider->lineStyle.y, slider->lineStyle.width, slider->lineStyle.height, slider->lineStyle.roundedness, 0, slider->lineStyle.normalColor);
		break;
	}

	switch (slider->sliderStyle.drawShape) {
	default:
		break;
	case STYLE_SHAPE_RECT:
		drawRectangle(&win, slider->sliderStyle.x, slider->sliderStyle.y, slider->sliderStyle.width, slider->sliderStyle.height, 0, drawColor);
		break;
	case STYLE_SHAPE_ROUNDED_RECT:
		drawRoundedRect(&win, slider->sliderStyle.x, slider->sliderStyle.y, slider->sliderStyle.width, slider->sliderStyle.height, slider->sliderStyle.roundedness, 0, drawColor);
		break;
	}

	slider->onRender(slider);
}