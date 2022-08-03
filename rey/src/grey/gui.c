#include "grey/gui.h"

void df(struct Button* button) {
	return;
}

void df2(struct Slider* slider) {
	return;
}

void df3(struct IconButton* iconButton) {
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
	Slider s = { ls, ss, BUTTON_HOVER_STATE_OFF, BUTTON_MOUSE_STATE_OFF, value, df2, df2, df2, df2, df2, df2 };
	return s;
}

IconButton createIconButton(double x, double y, double width, double height, Texture iconTexture, unsigned int texturePaddingX, unsigned int texturePaddingY, unsigned int textPadding, FontID font, unsigned int fontSize, const char* text) {
	Style bS = { x, y, width, height, STYLE_SHAPE_RECT, 0, 0, { 0, 0, 0, 255 }, { 200, 200, 200, 255 }, { 255, 255, 255, 255 } , { 150, 150, 150, 255 } };
	IconButton iB = { bS, iconTexture, texturePaddingX, texturePaddingY, textPadding, font, fontSize, (char*)text, 0, 0, { 255, 255, 255, 255 }, { 0, 0, 0, 255 }, df3, df3, df3, df3, df3, df3 };
	return iB;
}

void renderIconButton(Window win, IconButton* iconButton) {
	iconButton->onUpdate(iconButton);
	unsigned int drawColor[4];

	if (win.mouse.x < iconButton->buttonStyle.x + iconButton->buttonStyle.width && win.mouse.x + 1 > iconButton->buttonStyle.x && win.mouse.y < iconButton->buttonStyle.y + iconButton->buttonStyle.height && win.mouse.y + 1 > iconButton->buttonStyle.y) {
		if (iconButton->hoverState == BUTTON_HOVER_STATE_OFF) {
			iconButton->onHoverOn(iconButton);
		}
		iconButton->hoverState = BUTTON_HOVER_STATE_ON;
		if (win.mouse.isPrimaryDown) {
			if (iconButton->clickState == BUTTON_MOUSE_STATE_OFF) {
				iconButton->onMouseDown(iconButton);
			}
			iconButton->clickState = BUTTON_MOUSE_STATE_ON;
			setColor(&drawColor, iconButton->buttonStyle.clickedColor);
		}
		else {
			if (iconButton->clickState == BUTTON_MOUSE_STATE_ON) {
				iconButton->onMouseUp(iconButton);
			}
			iconButton->clickState = BUTTON_MOUSE_STATE_OFF;
			setColor(&drawColor, iconButton->buttonStyle.hoverColor);
		}
	}
	else {
		if (iconButton->hoverState == BUTTON_HOVER_STATE_ON) {
			iconButton->onHoverOff(iconButton);
		}
		iconButton->hoverState = BUTTON_HOVER_STATE_OFF;
		setColor(&drawColor, iconButton->buttonStyle.normalColor);
	}

	switch (iconButton->buttonStyle.drawShape) {
	default:
		break;
	case STYLE_SHAPE_RECT:
		drawRectangle(&win, iconButton->buttonStyle.x, iconButton->buttonStyle.y, iconButton->buttonStyle.width, iconButton->buttonStyle.height, 0, drawColor);
		if (iconButton->buttonStyle.borderSize > 0) {
			drawRectangle(&win, iconButton->buttonStyle.x, iconButton->buttonStyle.y, iconButton->buttonStyle.width, iconButton->buttonStyle.borderSize, 0, iconButton->buttonStyle.borderColor);
			drawRectangle(&win,iconButton->buttonStyle.x, (iconButton->buttonStyle.y + iconButton->buttonStyle.height) - iconButton->buttonStyle.borderSize, iconButton->buttonStyle.width, iconButton->buttonStyle.borderSize, 0, iconButton->buttonStyle.borderColor);
			drawRectangle(&win, iconButton->buttonStyle.x, iconButton->buttonStyle.y + iconButton->buttonStyle.borderSize, iconButton->buttonStyle.borderSize, iconButton->buttonStyle.height - (iconButton->buttonStyle.borderSize * 2.0), 0, iconButton->buttonStyle.borderColor);
			drawRectangle(&win, (iconButton->buttonStyle.x + iconButton->buttonStyle.width) - iconButton->buttonStyle.borderSize, iconButton->buttonStyle.y + iconButton->buttonStyle.borderSize, iconButton->buttonStyle.borderSize, iconButton->buttonStyle.height - (iconButton->buttonStyle.borderSize * 2.0), 0, iconButton->buttonStyle.borderColor);
		}
		break;
	case STYLE_SHAPE_ROUNDED_RECT:
		if (iconButton->buttonStyle.borderSize > 0) {
			drawRoundedRect(&win, iconButton->buttonStyle.x, iconButton->buttonStyle.y, iconButton->buttonStyle.width, iconButton->buttonStyle.height, iconButton->buttonStyle.roundedness, 0, iconButton->buttonStyle.borderColor);
			drawRoundedRect(&win, iconButton->buttonStyle.x + iconButton->buttonStyle.borderSize, iconButton->buttonStyle.y + iconButton->buttonStyle.borderSize, iconButton->buttonStyle.width - (iconButton->buttonStyle.borderSize * 2.0), iconButton->buttonStyle.height - (iconButton->buttonStyle.borderSize * 2.0), iconButton->buttonStyle.roundedness / 1.5f, 0, drawColor);
		}
		else {
			drawRoundedRect(&win, iconButton->buttonStyle.x, iconButton->buttonStyle.y, iconButton->buttonStyle.width, iconButton->buttonStyle.height, iconButton->buttonStyle.roundedness, 0, drawColor);
		}
		break;
	}

	drawTexture(&win, iconButton->iconTexture, iconButton->buttonStyle.x + iconButton->texturePaddingX / 2, iconButton->buttonStyle.y + iconButton->texturePaddingY / 2, iconButton->buttonStyle.height - iconButton->texturePaddingX, iconButton->buttonStyle.height - iconButton->texturePaddingY, 0, iconButton->textureColor);

	double height = getHeightOfText(&win, iconButton->text, iconButton->font, iconButton->fontSize);
	drawText(&win, iconButton->text, iconButton->font, iconButton->buttonStyle.height, (iconButton->buttonStyle.y + iconButton->buttonStyle.height / 2) - height, iconButton->fontSize, iconButton->textColor);

	iconButton->onRender(iconButton);
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