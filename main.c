#include <grey.h>
#include <stdio.h>

int main() {
	initGrey(4);

	Window win = createWindow(720, 720, "grey");

	srand(NULL);

	int amtX = 10;
	int amtY = 10;
	float time = 0.0f;
	int frames = 0;

	Texture block = newTexture(&win, "resources/block.png", FILTER_LINEAR);

	while (!shouldWindowClose(win)) {
		updateWindow(&win);
		
		clearWindowBackground(win, COLOR_DISCORD);

		time += win.deltaTime;
		frames += 1;
		if (time >= 1.0f) {
			time = 0.0f;
			printf("%i\n", frames);
			frames = 0;
		}

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
		
		drawRectangle(&win, 0, 0, 100, 100, -30.0f, COLOR_BLUE);
		drawTexture(&win, block, 0, 0, 100, 100, 30.0f, COLOR_WHITE);
		
		renderWindow(win);
	}
	
	deleteTexture(&win, block);
	deleteWindow(&win);
	closeGrey();
	return 0;
}