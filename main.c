#include <grey.h>
#include <stdio.h>

int main() {
	initGrey(4);

	Window win = createWindow(1280, 720, "grey");

	while (!shouldWindowClose(win)) {
		updateWindow(&win);
		
		clearWindowBackground(win, COLOR_DISCORD);

		if (isKeyDown(win, KEY_ESCAPE)) {
			closeWindow(win);
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
		
		if (isKeyDown(win, KEY_I)) {
			drawRectangle(&win, 0, 0, 250, 250, COLOR_SOFT_ORANGE);
		} else {
			drawRectangle(&win, 0, 0, 250, 250, (Color){ 255, 128, 50, 50 });
		}

		if (isKeyPressed(win, KEY_G)) {
			printf("powered by grey\n");
		}
		
		renderWindow(win);
	}
	
	deleteWindow(&win);
	closeGrey();
	return 0;
}