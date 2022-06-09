#include <grey.h>
#include <stdio.h>
#include <arey.h>

float resolutionDivider = 1.5;
float width = 884, height = 1080;
Color backgroundColor = { 40, 47, 51, 255 };
Color tetrisBackgroundColor = { 30, 35, 38, 255 };
Color borderColor = { 54, 68, 76, 255 };

float fX(float x) {
	return x/resolutionDivider;
}

int main() {
	initGrey(4);
	initArey();
	
	Window win = createWindow(width/resolutionDivider, height/resolutionDivider, "grey");

	win.fullscreen = FALSE;

	while (!shouldWindowClose(win)) {
		updateWindow(&win);

		if (win.width/width < win.height/height) {
			resolutionDivider = width/win.width;
		} else {
			resolutionDivider = height/win.height;
		}

		clearWindowBackground(win, backgroundColor);

		if (isKeyDown(win, KEY_ESCAPE)) {
			closeWindow(win);
		}

		if (isKeyPressed(win, KEY_F)) {
			printf("%f\n", win.framesPerSecond);
		}

		if (isKeyPressed(win, KEY_F11)) {
			win.fullscreen = !win.fullscreen;
		}

		setWireframeMode(win, isKeyDown(win, KEY_SPACE));

		// Draw UI
		/// Borders
		drawRectangle(&win, fX(36), fX(36), fX(552-36), fX(1042-36), 0, borderColor);
		drawRectangle(&win, fX(576), fX(85), fX(846-576), fX(230-85), 0, borderColor);
		/// Tetris background
		drawRectangle(&win, fX(49), fX(49), fX(539-49), fX(1029-49), 0, tetrisBackgroundColor);
		drawRectangle(&win, fX(589), fX(98), fX(833-589), fX(217-98), 0, tetrisBackgroundColor);

		renderWindow(win);
	}

	deleteWindow(&win);

	closeArey();
	closeGrey();
	return 0;
}