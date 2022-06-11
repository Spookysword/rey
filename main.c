#include <grey.h>

#define size 12

float playerX = 1280/2, playerY = 720/2, playerWidth = 25, playerHeight = 25, playerRotation = 0, rotationSpeed = 100, moveSpeed = 100;
float circleX, circleY, circleR = 5;

int main() {
	initGrey(0);

	Window win = createWindow(1280, 720, "greytracing");
	
	int x[size] = {
		0, 0, 1280-50, 0, 200, 200, 200, 400, 400, 600, 600, 800
	};
	int y[size] = {
		0, 0, 0, 720-50, 250, 250, 450, 450, 600, 450, 100, 100
	};
	int w[size] = {
		1280, 50, 50, 1280, 250, 50, 250, 50, 200, 50, 50, 50
	};
	int h[size] = {
		50, 720, 720, 50, 50, 250, 50, 200, 50, 200, 200, 550
	};
	
	while (!shouldWindowClose(win)) {
		updateWindow(&win);

		clearWindowBackground(&win, COLOR_WHITE);

		for (int i = 0; i < size; i++) {
			drawRectangle(&win, x[i], y[i], w[i], h[i], 0, COLOR_BLACK);
		}

		float px = playerX + playerWidth, py = playerY + (playerHeight / 2);
		float ox = playerX + (playerWidth / 2), oy = playerY + (playerHeight / 2);
		float theta = playerRotation * (3.14159265359 / 180);

		circleX = cos(theta) * (px - ox) - sin(theta) * (py - oy) + ox;
		circleY = sin(theta) * (px - ox) + cos(theta) * (py - py) + oy;

		// Controls
		if (isKeyDown(win, KEY_LEFT)) {
			playerRotation -= rotationSpeed * win.deltaTime;
		}
		if (isKeyDown(win, KEY_RIGHT)) {
			playerRotation += rotationSpeed * win.deltaTime;
		}
		if (isKeyDown(win, KEY_UP)) {
			playerX += (moveSpeed * cos(theta)) * win.deltaTime;
			playerY += (moveSpeed * sin(theta)) * win.deltaTime;
		}
		if (isKeyDown(win, KEY_DOWN)) {
			playerX -= (moveSpeed * cos(theta)) * win.deltaTime;
			playerY -= (moveSpeed * sin(theta)) * win.deltaTime;
		}

		drawRectangle(&win, playerX, playerY, playerWidth, playerHeight, playerRotation, COLOR_YELLOW);
		drawCircle(&win, circleX, circleY, circleR, COLOR_RED);

		renderWindow(win);
	}

	deleteWindow(&win);
	closeGrey();
}