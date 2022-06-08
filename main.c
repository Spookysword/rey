#include <grey.h>
#include <stdio.h>
#include <arey.h>

int main() {
	initGrey(4);
	initArey();

	Window win = createWindow(720, 720, "grey");

	while (!shouldWindowClose(win)) {
		updateWindow(&win);

		clearWindowBackground(win, COLOR_DISCORD);

		if (isKeyDown(win, KEY_ESCAPE)) {
			closeWindow(win);
		}

		if (isKeyPressed(win, KEY_F)) {
			printf("%f\n", win.framesPerSecond);
		}

		if (isKeyPressed(win, KEY_F11)) {
			win.fullscreen = !win.fullscreen;
		}

		if (isKeyDown(win, KEY_SPACE)) {
			setWireframeMode(win, TRUE);
		}

		else {
			setWireframeMode(win, FALSE);
		}

		renderWindow(win);
	}

	deleteWindow(&win);

	closeArey();
	closeGrey();
	return 0;
}