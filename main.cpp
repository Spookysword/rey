/*#include "grey++"

int main() {
	initGrey(4);

	Window win(500, 500, "grey");

	while (!win.shouldClose()) {
		win.update();

		win.clearBackground(COLOR_DISCORD);

		if (win.isKeyDown(KEY_ESCAPE)) {
			win.close();
		}

		if (!win.isKeyDown(KEY_I)) {
			win.drawRectangle(0, 0, 250, 250, COLOR_SOFT_ORANGE);
		}

		win.render();
	}

	closeGrey();
	return 0;
}*/

#include <grey>

int main() {
	initGrey(4);

	Window win = createWindow(500, 500, "grey");

	while (!shouldWindowClose(win)) {
		updateWindow(&win);

		clearWindowBackground(win, COLOR_DISCORD);

		if (isKeyDown(win, KEY_ESCAPE)) {
			closeWindow(win);
		}

		if (!isKeyDown(win, KEY_I)) {
			drawRectangle(&win, 0, 0, 250, 250, COLOR_SOFT_ORANGE);
		}

		renderWindow(win);
	}

	deleteWindow(&win);
	closeGrey();
	return 0;
}