#include <grey.h>

int main() {
	initGrey(0);

	Window win = createWindow(1280, 720, "grey");
	
	while (!shouldWindowClose(win)) {
		updateWindow(&win);

		clearWindowBackground(&win, COLOR_WHITE);

		drawRectangle(&win, 100, 100, 100, 100, 0, COLOR_SOFT_ORANGE);

		renderWindow(win);
	}

	deleteWindow(&win);
	closeGrey();
}