#include <grey.h>
#include <stdio.h>
#include <prey.h>

int main() {
	initGrey(4);
	initPrey(0);

	Window win = createWindow(1280, 720, "grey");
	PhysicsWorld world = createPhysicsWorld();
	PhysicsRectID b = newRect(&world, NULL, 0, 200, 50, 50, 0.1, 0);
	PhysicsRectID a = newRect(&world, NULL, 0, 0, 50, 50, 0.3, 0);

	while (!shouldWindowClose(win)) {
		updateWindow(&win);
		updatePhysicsWorld(&world, win.deltaTime);
		
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

		if (isKeyPressed(win, KEY_G)) {
			printf("powered by grey\n");
		}

		drawRectangle(&win, world.rects[a].rect.x, world.rects[a].rect.y, world.rects[a].rect.w, world.rects[a].rect.h, COLOR_RED);
		drawRectangle(&win, world.rects[b].rect.x, world.rects[b].rect.y, world.rects[b].rect.w, world.rects[b].rect.h, COLOR_BLUE);


		
		renderWindow(win);
	}
	
	deleteWindow(&win);
	closeGrey();
	return 0;
}