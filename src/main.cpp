#include <arey/arey.hpp>
#include <grey/grey.h>
#include <grey/grey/obj.hpp>

int main() {
	initGrey(0);
	initArey();

	Window win = createWindow(1280, 720, "grey");
	Sound aeh = loadSound("resources/aeh.flac");
	aeh.loopSound = false;
	aeh.position[0] = -1000;
	aeh.position[1] = 0;
	aeh.position[2] = 0;

	while (!shouldWindowClose(win)) {
		updateWindow(&win);

		if (isKeyDown(win, KEY_LEFT)) {
			aeh.position[0] -= 5;
			
		}

		if (isKeyDown(win, KEY_RIGHT)) {
			aeh.position[0] += 5;
		}

		if (isKeyPressed(win, KEY_A)) {
			playSound(&aeh);
		}

		renderWindow(win);
	}

	deleteSound(&aeh);
	deleteWindow(&win);
	closeGrey();
	closeArey();
}