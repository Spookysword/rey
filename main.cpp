#include "grey++"
#include <iostream>

int main() {
	initGrey(4);

	Window win(1280, 720, "grey");

	while (!win.shouldClose()) {
		win.update();

		win.clearBackground(COLOR_DISCORD);

		if (win.isKeyDown(KEY_ESCAPE)) {
			win.close();
		}

		if (win.isKeyPressed(KEY_F11)) {
			win.fullscreen = !win.fullscreen;
		}

		if (win.isKeyDown(KEY_SPACE)) {
			win.setWireframeMode(true);
		} else {
			win.setWireframeMode(false);
		}

		if (win.isKeyDown(KEY_I)) {
			win.drawRectangle(0, 0, 250, 250, COLOR_SOFT_ORANGE);
		} else {
			win.drawRectangle(0, 0, 250, 250, Color{ 255, 128, 50, 100 });
		}

		win.drawRectangle(500, 250, 250, 250, COLOR_SOFT_BLUE);
		win.drawRectangle(500, 500, 250, 250, COLOR_SOFT_GREEN);
		win.drawRectangle(750, 250, 250, 250, COLOR_SOFT_CHARTREUSE);

		if (win.isKeyPressed(KEY_G)) {
			std::cout << "powered by grey\n";
		}
		
		win.render();
	}
	
	closeGrey();
	return 0;
}

/*#include <grey>
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
}*/