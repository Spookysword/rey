/*#include "grey++"

int main() {
	initGrey(4);

	Window win(500, 500, "grey");

	while (!win.shouldClose()) {
		win.update();

		win.clearBackground(COLOR_DISCORD);

		if (win.isKeyDown(KEY_ESCAPE)) {
			win.close();
		}

		if (!win.isKeyDown(KEY_I)) {
			win.drawRectangle(0, 0, 250, 250, COLOR_SOFT_ORANGE);
		}

		std::cout << win.deltaTime << std::endl;
		win.render();
	}

	closeGrey();
	return 0;
}*/

#include <grey>
#include <prey>

int main() {
	initGrey(4);
	initPrey(10);

	Window win = createWindow(500, 500, "grey");
	PhysicsWorld world = createPhysicsWorld();

	PhysicsRectID rect = newRect(&world, NULL, 0, 0, 20, 20, 1.0f, 0.0f);

	while (!shouldWindowClose(win)) {
		updateWindow(&win);
		updatePhysicsWorld(&world, win.deltaTime);

		clearWindowBackground(win, COLOR_DISCORD);

		if (isKeyDown(win, KEY_ESCAPE)) {
			closeWindow(win);
		}

		if (!isKeyDown(win, KEY_I)) {
			drawRectangle(&win, world.rects[rect].rect.x, world.rects[rect].rect.y, world.rects[rect].rect.w, world.rects[rect].rect.h, COLOR_SOFT_ORANGE);
		}

		printf("%f", win.deltaTime);
		printf("\n");
		renderWindow(win);
	}

	deleteWindow(&win);
	closePrey();
	closeGrey();
	return 0;
}