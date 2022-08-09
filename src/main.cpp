#include <grey/grey.h>
#include <grey/grey/obj.hpp>
#include <arey/arey.hpp>

int main() {
	initGrey(0);
	initArey();

	Window win = createWindow(1280, 720, "grey");
	Sound aeh = loadSound("resources/da.wav");
	aeh.loopSound = true;
	aeh.position[0] = -1000;
	playSound(&aeh);

	while (!shouldWindowClose(win)) {
		updateWindow(&win);

		renderWindow(win);
	}

	deleteSound(&aeh);
	deleteWindow(&win);
	closeGrey();
	closeArey();
}