#include "grey++"

int main() {
	initGrey(4);

	Window win(500, 500, "grey");

	while (!win.shouldClose()) {
		win.update();

		win.clearBackground(COLOR_DISCORD);

		if (win.isKeyDown(KEY_ESCAPE)) {
			win.close();
		}

		win.render();
	}

	closeGrey();
	return 0;
}


/*#include <grey>

int main() {
	initGrey(4);

	Window win = createWindow(500, 500, "grey");

	while (!shouldWindowClose(win)) {
		updateWindow(&win);

		clearWindowBackground(win, COLOR_DISCORD);

		if (isKeyDown(win, KEY_ESCAPE)) {
			closeWindow(win);
		}

		renderWindow(win);
	}

	closeGrey();
	return 0;
}*/