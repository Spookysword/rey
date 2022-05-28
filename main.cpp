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
			win.drawTriangle(-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, COLOR_SOFT_ORANGE);
			win.drawTriangle(-0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, COLOR_SOFT_ORANGE);
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
			drawTriangle(&win, -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, COLOR_SOFT_ORANGE);
			drawTriangle(&win, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, COLOR_SOFT_ORANGE);
		}

		renderWindow(win);
	}

	deleteWindow(&win);
	closeGrey();
	return 0;
}