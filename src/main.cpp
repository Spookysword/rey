#include <arey/arey.hpp>
#include <grey/grey.hpp>

int main() {
	initGrey(0);
	initArey();

	Window win(1280, 720, "grey");
	Sound aeh = loadSound("resources/aeh.flac");
	aeh.loopSound = false;
	aeh.position[0] = -1000;
	aeh.position[1] = 0;
	aeh.position[2] = 0;

	while (win) {
		win.update();

		if (win.isKeyDown(KEY_LEFT)) {
			aeh.position[0] -= 5;
			
		}

		if (win.isKeyDown(KEY_RIGHT)) {
			aeh.position[0] += 5;
		}

		if (win.isKeyPressed(KEY_A)) {
			playSound(&aeh);
		}

		win.render();
	}

	deleteSound(&aeh);
	win.del();
	closeGrey();
	closeArey();
}