/*

FAIR WARNING
This demo is NOT finished, so do not expect much from it.

*/
/*

FAIR WARNING
This demo is NOT finished, so do not expect much from it.

*/
#include <grey.h>

#define size 12

float playerX = 1280 / 2, playerY = 720 / 2, playerWidth = 25, playerHeight = 25, playerRotation = 0, rotationSpeed = 100, moveSpeed = 100;
float circleX, circleY, circleR = 5;
int reys = 1000;
float fov = 90 + 45;
int limit = 200;
float reyspeed = 50; // a lower the value will be more accurate (but laggy)

float distance(float x1, float y1, float x2, float y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}


boolean AABB(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
	if (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2) { return TRUE; }
	return FALSE;
}

boolean inWall(int* x, int* y, int* w, int* h, float px, float py) {
	for (int i = 0; i < size; i++) {
		float rx = x[i], ry = y[i], rw = w[i], rh = h[i];
		if (AABB(px, py, 0, 0, rx, ry, rw, rh) == TRUE) return TRUE;
	}
	return FALSE;
}

int main() {
	initGrey(0);

	Window win = createWindow(1280, 720, "greytracing");

	int x[size] = {
		0, 0, 1280 - 50, 0, 200, 200, 200, 400, 400, 600, 600, 800
	};
	int y[size] = {
		0, 0, 0, 720 - 50, 250, 250, 450, 450, 600, 450, 100, 100
	};
	int w[size] = {
		1280, 50, 50, 1280, 250, 50, 250, 50, 200, 50, 50, 50
	};
	int h[size] = {
		50, 720, 720, 50, 50, 250, 50, 200, 50, 200, 200, 550
	};

	while (!shouldWindowClose(win)) {
		updateWindow(&win);

		clearWindowBackground(&win, COLOR_BLACK);

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

		float rotationInc = fov / reys;
		float rotation = (playerRotation - (fov / 2)); //idk

		for (int rey = 0; rey < reys; rey++) {
			// For each rey, we want to keep going forward until the x,y position intercepts with AABB with a rectangle, then draw a line from the start to the end
			float xStart = circleX, yStart = circleY;
			float curX = xStart, curY = yStart;

			float theta = rotation * (3.14159265359 / 180);

			while (!inWall(x, y, w, h, curX, curY)) {
				curX += (reyspeed * cos(theta)) * win.deltaTime;
				curY += (reyspeed * sin(theta)) * win.deltaTime;
				if (distance(xStart, yStart, curX, curY) > limit) break;
			}
			rotation += rotationInc;
			float lengthX = xStart - curX;
			float lengthY = yStart - curY;
			if (lengthX < 0) { lengthX = -lengthX; }
			if (lengthY < 0) { lengthY = -lengthY; }
			drawLine(&win, xStart, yStart, curX, curY, 1, COLOR_WHITE);
		}

		renderWindow(win);
	}

	deleteWindow(&win);
	closeGrey();
}