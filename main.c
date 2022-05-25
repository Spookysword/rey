#include "grey.h"

int main() {
	initGrey(4);

	Window win = createWindow(500, 500, "grey");

	while (!shouldWindowClose(win)) {
		updateWindow(&win);

		clearWindowBackground(win, 255, 255, 255, 255);
		
		if (isKeyDown(win, KEY_ESCAPE)) {
			closeWindow(win);
		}

		renderWindow(win);
	}

	closeGrey();
	return 0;
}