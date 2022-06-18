/*

FAIR WARNING
This demo is NOT finished, so do not expect much from it.

*/
#include <grey.h>

struct Style {
	// "rectangle" or "roundedRectangle"
	const char* drawType;
	float radius;
	Color color;
	Color hoverColor;
	Color clickColor;
};
typedef struct Style Style;
struct Button {
	float x, y, width, height;
	Style style;
};
typedef struct Button Button;
Button createButton(float x, float y, float width, float height) {
	Button returnButton;
	returnButton.x = x; returnButton.y = y; returnButton.width = width; returnButton.height = height;
	returnButton.style.drawType = "rectangle";
	returnButton.style.color[3] = 255;
	returnButton.style.hoverColor[3] = 255;
	returnButton.style.clickColor[3] = 255;
	returnButton.style.radius = 0.0f;
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
	Button testButton = createButton(100, 100, 100, 100);
	setColor(&testButton.style.color, COLOR_LIGHT_GREY);
	setColor(&testButton.style.clickColor, COLOR_DARK_GREY);
	Button testButton2 = createButton(300, 100, 100, 100);
	testButton2.style.drawType = "roundedRectangle";
	testButton2.style.radius = 25.0f;
	setColor(&testButton2.style.color, COLOR_LIGHT_GREY);
	setColor(&testButton2.style.clickColor, COLOR_DARK_GREY);

	while (!shouldWindowClose(win)) {
		updateWindow(&win);

		clearWindowBackground(&win, COLOR_BLACK);

		drawButton(win, testButton);
		drawButton(win, testButton2);

		if (isButtonPressed(win, testButton)) {
			printf("You clicked the first button!\n");
		}
		if (isButtonPressed(win, testButton2)) {
			printf("You clicked the second button!\n");
		}

		renderWindow(win);
	}

	deleteWindow(&win);
	closeGrey();
}