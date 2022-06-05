#include <grey.h>
#include <stdio.h>
#include <arey.h>

int main() {
	initGrey(4);
	initArey();

	Window win = createWindow(720, 720, "grey");
	playSound("resources/aeh.wav");
	
	float moveSpeed = 250.0f;

	Texture block = newTexture(&win, "resources/block.png", FILTER_LINEAR);
	float rot = 0.0f;

	while (!shouldWindowClose(win)) {
		updateWindow(&win);
		rot += 1.0f;

		clearWindowBackground(win, COLOR_DISCORD);

		if (isKeyDown(win, KEY_ESCAPE)) {
			closeWindow(win);
		}

		if (isKeyPressed(win, KEY_F)) {
			printf("%f\n", win.framesPerSecond);
		}

		if (isKeyPressed(win, KEY_F11)) {
			win.fullscreen = !win.fullscreen;
		}

		if (isKeyPressed(win, KEY_SPACE)) {
			playSound("resources/aeh.ogg");
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
		
		drawTexture(&win, block, 0, 0, 100, 100, rot, COLOR_WHITE);
		
		renderWindow(win);
	}
	
	deleteTexture(&win, block);
	deleteWindow(&win);

	closeArey();
	closeGrey();
	return 0;
}