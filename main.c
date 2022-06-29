#include <grey/grey.h>

int main()
{
	initGrey(0);

	Window win = createWindow(1280, 720, "grey");

	while (!shouldWindowClose(win)) {
		updateWindow(&win);
		drawRectangle(&win, 0, 0, 100, 100, 0, COLOR_RED);
		win.offset.x = win.offset.x - (int)isKeyDown(win, KEY_A) + (int)isKeyDown(win, KEY_D);
		win.offset.y = win.offset.y - (int)isKeyDown(win, KEY_W) + (int)isKeyDown(win, KEY_S);
		renderWindow(win);
	}

	deleteWindow(&win);
	closeGrey();
}