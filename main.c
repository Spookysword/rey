#include <grey.h>
#include <stdio.h>

int main() {
	initGrey(4);

	Window win = createWindow(720, 720, "grey");

	srand(NULL);
	
	float moveSpeed = 250.0f;

	Texture block = newTexture(&win, "resources/block.png", FILTER_LINEAR);

	while (!shouldWindowClose(win)) {
		updateWindow(&win);
		
		clearWindowBackground(win, COLOR_DISCORD);

		printf("%f\n", win.framesPerSecond);

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

		if (isKeyDown(win, KEY_W)) { win.camera.y -= moveSpeed * win.deltaTime; }
		if (isKeyDown(win, KEY_S)) { win.camera.y += moveSpeed * win.deltaTime; }
		if (isKeyDown(win, KEY_A)) { win.camera.x -= moveSpeed * win.deltaTime; }
		if (isKeyDown(win, KEY_D)) { win.camera.x += moveSpeed * win.deltaTime; }
		
		drawRectangle(&win, 0, 0, 100, 100, -30.0f, COLOR_BLUE);
		drawTexture(&win, block, 0, 0, 100, 100, 30.0f, COLOR_WHITE);
		
		renderWindow(win);
	}
	
	deleteTexture(&win, block);
	deleteWindow(&win);
	closeGrey();
	return 0;
}