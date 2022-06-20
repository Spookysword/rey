/*

FAIR WARNING
This demo is NOT finished, so do not expect much from it.

*/
#include <grey.h>

struct Style {
	// "rectangle"* or "roundedRectangle"
	const char* drawType;
	// "normal"* or "bordered"
	const char* textType;
	float radius;
	int borderSize;
	Color color;
	Color hoverColor;
	Color clickColor;
	Color textColor;
	Color textBorderColor;
	FontID font;
	int textScale;
};
typedef struct Style Style;
struct Button {
	float x, y, width, height;
	Style style;
	const char* text;
};
typedef struct Button Button;
Button createButton(float x, float y, float width, float height, const char* text) {
	Button returnButton;
	returnButton.x = x; returnButton.y = y; returnButton.width = width; returnButton.height = height;
	returnButton.style.drawType = "rectangle";
	returnButton.style.textType = "normal";
	returnButton.style.color[3] = 255;
	returnButton.style.hoverColor[3] = 255;
	returnButton.style.clickColor[3] = 255;
	returnButton.style.textColor[3] = 255;
	returnButton.style.textBorderColor[3] = 255;
	returnButton.style.radius = 0.0f;
	returnButton.style.borderSize = 0;
	returnButton.style.textScale = 0;
	returnButton.text = text;
	returnButton.style.font = 0;
	return returnButton;
}
boolean isButtonHovering(Window win, Button button) {
	if (win.mouse.x > button.x && win.mouse.x < button.x + button.width && win.mouse.y > button.y && win.mouse.y < button.y + button.height) {
		return TRUE;
	}
	return FALSE;
}
void drawButton(Window win, Button button) {
	Color drawColor;
	if (isButtonHovering(win, button)) {
		if (win.mouse.isPrimaryDown) {
			setColor(&drawColor, button.style.clickColor);
		}
		else {
			setColor(&drawColor, button.style.hoverColor);
		}
	}
	else {
		setColor(&drawColor, button.style.color);
	}
	if (button.style.drawType == "roundedRectangle") {
		drawRoundedRect(&win, button.x, button.y, button.width, button.height, button.style.radius, 0, drawColor);
	}
	else {
		drawRectangle(&win, button.x, button.y, button.width, button.height, 0, drawColor);
	}
	float wid = getWidthOfText(&win, button.text, button.style.font, button.style.textScale);
	float hei = getHeightOfText(&win, button.text, button.style.font, button.style.textScale);
	float textX = (button.x + button.width / 2) - wid / 2;
	float textY = (button.y + button.height / 2) - hei / 2;

	if (button.style.textType == "bordered") {
		printf("A");
		drawBorderedText(&win, button.text, button.style.font, textX, textY, button.style.textScale, button.style.borderSize, button.style.textColor, button.style.textBorderColor);
	}
	else {
		drawText(&win, button.text, button.style.font, textX, textY, button.style.textScale, button.style.textColor);
	}
}
boolean isButtonDown(Window win, Button button) {
	if (!isButtonHovering(win, button)) {
		return FALSE;
	}
	if (win.mouse.isPrimaryDown) {
		return TRUE;
	}
}
boolean isButtonPressed(Window win, Button button) {
	if (!isButtonHovering(win, button)) {
		return FALSE;
	}
	if (win.mouse.isPrimaryPressed) {
		return TRUE;
	}
}

int main()
{
	initGrey(1);
	Window win = createWindow(1280, 720, "grey");

	FontID eightBitDragon = loadFont(&win, "resources/EightBitDragon.ttf", 50);

	Button testButton = createButton(100, 100, 100, 100, "B1");
	setColor(&testButton.style.color, COLOR_LIGHT_GREY);
	setColor(&testButton.style.clickColor, COLOR_DARK_GREY);
	testButton.style.font = eightBitDragon;
	testButton.style.textScale = 30;
	setColor(&testButton.style.textColor, COLOR_RED);

	Button testButton2 = createButton(300, 100, 100, 100, "B2");
	testButton2.style.drawType = "roundedRectangle";
	testButton2.style.radius = 25.0f;
	setColor(&testButton2.style.color, COLOR_LIGHT_GREY);
	setColor(&testButton2.style.clickColor, COLOR_DARK_GREY);
	testButton2.style.font = eightBitDragon;
	testButton2.style.textScale = 30;
	setColor(&testButton2.style.textColor, COLOR_DARK_GREY);
	setColor(&testButton2.style.textBorderColor, COLOR_RED);
	testButton2.style.textType = "bordered";
	testButton2.style.borderSize = 1;

	while (!shouldWindowClose(win)) {
		updateWindow(&win);

		clearWindowBackground(&win, COLOR_BLACK);

		drawButton(win, testButton);
		drawButton(win, testButton2);
		const char* text = "00";

		if (isButtonPressed(win, testButton)) {
			printf("You clicked the first button!\n");
			text = "B1";
		}
		if (isButtonPressed(win, testButton2)) {
			printf("You clicked the second button!\n");
			text = "B2";
		}
		drawText(&win, text, eightBitDragon, 20, 20, 30, COLOR_WHITE);

		renderWindow(win);
	}

	deleteWindow(&win);
	closeGrey();
}