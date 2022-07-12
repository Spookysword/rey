#include <grey/grey.h>
#include <grey/gui.h>

int main() {
	initGrey(8);

	Window win = createWindow(1280, 720, "grey");

	Button testButton = createButton(100, 100, 200, 100);
	testButton.style.drawShape = STYLE_SHAPE_ROUNDED_RECT;
	testButton.style.roundedness = 10;
	setColor(&testButton.style.borderColor, (Color){ 0, 0, 0, 255 });
	testButton.style.borderSize = 8;

	while (!shouldWindowClose(win)) {
		updateWindow(&win);

		clearWindowBackground(&win, COLOR_DARK_GREY);

		renderButton(win, &testButton);

		renderWindow(win);
	}

	deleteWindow(&win);
	closeGrey();
}