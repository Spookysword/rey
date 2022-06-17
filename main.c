#include <grey.h>

int main()
{
	initGrey(0);

	Window win = createWindow(1280, 720, "grey");

	while (!shouldWindowClose(win)) {
		updateWindow(&win);

		renderWindow(win);
	}

	deleteWindow(&win);
	closeGrey();
}