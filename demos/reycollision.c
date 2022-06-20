/*

FAIR WARNING
This demo is NOT finished, so do not expect much from it.

*/
/*

FAIR WARNING
This demo is NOT finished, so do not expect much from it.

*/
#include <grey/grey.h>

#define size 12

float playerX = 1280 / 2, playerY = 720 / 2, playerWidth = 25, playerHeight = 25, playerRotation = 0, rotationSpeed = 100, moveSpeed = 100;
float circleX, circleY, circleR = 5;
//int reys = 500;
//float fov = 360;
//int limit = 500;
//float reyspeed = 100; // a lower the value will be more accurate (but laggy)
//float thickness = 5; // size of reys and of the walls

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

int sendRey(int* x, int* y, int* w, int* h, Window* win, float fov, int reys, int limit, float reyspeed, float thickness, float rot, float cx, float cy) {
	float rotationInc = fov / reys;
	float rotation = (rot - (fov / 2)); //idk
	int hits = 0;

	for (int rey = 0; rey < reys; rey++) {
		// For each rey, we want to keep going forward until the x,y position intercepts with AABB with a rectangle, then draw a line from the start to the end
		float xStart = cx, yStart = cy;
		float curX = xStart, curY = yStart;

		float theta = rotation * (3.14159265359 / 180);
		boolean hit = TRUE;
		while (!inWall(x, y, w, h, curX, curY)) {
			curX += (reyspeed * cos(theta)) * win->deltaTime;
			curY += (reyspeed * sin(theta)) * win->deltaTime;
			if (distance(xStart, yStart, curX, curY) > limit) {
				hit = FALSE;
				break;
			}
		}

		if (hit) {
			hits += 1;
		}
		rotation += rotationInc;
	}
	return hits;
}

int main() {
	initGrey(4);

	Window win = createWindow(1280, 720, "greycollision");

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
			drawRectangle(&win, x[i], y[i], w[i], h[i], 0, COLOR_RED);
			drawRectangle(&win, x[i] + 2, y[i] + 2, w[i] - 4, h[i] - 4, 0, COLOR_BLACK);
		}


		float px = playerX + playerWidth, py = playerY + (playerHeight / 2);
		float ox = playerX + (playerWidth / 2), oy = playerY + (playerHeight / 2);
		float theta = playerRotation * (3.14159265359 / 180);

		circleX = cos(theta) * (px - ox) - sin(theta) * (py - oy) + ox;
		circleY = sin(theta) * (px - ox) + cos(theta) * (py - py) + oy;

		float c1 = playerX + playerWidth / 2;
		float c2 = playerY + playerHeight / 2;
		float rot = -playerRotation * (3.14159265359 / 180);

		float Rreys = 50;
		float Rlimit = 1;
		float Rspeed = 10;
		int spacing = Rreys / 1.5f; // Collision looks most natural when this value is between Rreys/2 and Rreys 
		//SPACING = 1-Rreys: the collision will only respond if it is fully colliding
		//SPACING = 0: Collision will happen even when they are Rlimit pixels away from each other
		//SPACING = Rreys/1.5f: the most consistent and realistic value for Rreys

		int backleft = sendRey(x, y, w, h, &win, 360, Rreys, Rlimit, Rspeed, 1, 0,
			rotateX(playerX, playerY, c1, c2, rot), rotateY(playerX, playerY, c1, c2, rot));
		int backright = sendRey(x, y, w, h, &win, 360, Rreys, Rlimit, Rspeed, 1, 0,
			rotateX(playerX, playerY + playerHeight, c1, c2, rot), rotateY(playerX, playerY + playerHeight, c1, c2, rot));
		int back = sendRey(x, y, w, h, &win, 360, Rreys, Rlimit, Rspeed, 1, 0,
			rotateX(playerX, playerY + playerHeight / 2, c1, c2, rot), rotateY(playerX, playerY + playerHeight / 2, c1, c2, rot));

		int frontleft = sendRey(x, y, w, h, &win, 360, Rreys, Rlimit, Rspeed, 1, 0,
			rotateX(playerX + playerWidth, playerY, c1, c2, rot), rotateY(playerX + playerWidth, playerY, c1, c2, rot));
		int frontright = sendRey(x, y, w, h, &win, 360, Rreys, Rlimit, Rspeed, 1, 0,
			rotateX(playerX + playerWidth, playerY + playerHeight, c1, c2, rot), rotateY(playerX + playerWidth, playerY + playerHeight, c1, c2, rot));
		int front = sendRey(x, y, w, h, &win, 360, Rreys, Rlimit, Rspeed, 1, 0,
			rotateX(playerX + playerWidth, playerY + playerHeight / 2, c1, c2, rot), rotateY(playerX + playerWidth, playerY + playerHeight / 2, c1, c2, rot));

		// Controls
		if (isKeyDown(win, KEY_LEFT) && backleft <= spacing && frontright <= spacing) {
			playerRotation -= rotationSpeed * win.deltaTime;
		}
		if (isKeyDown(win, KEY_RIGHT) && backright <= spacing && frontleft <= spacing) {
			playerRotation += rotationSpeed * win.deltaTime;
		}
		if (isKeyDown(win, KEY_UP) && frontleft <= spacing && frontright <= spacing && front <= spacing) {
			playerX += (moveSpeed * cos(theta)) * win.deltaTime;
			playerY += (moveSpeed * sin(theta)) * win.deltaTime;
		}
		if (isKeyDown(win, KEY_DOWN) && backleft <= spacing && backright <= spacing && back <= spacing) {
			playerX -= (moveSpeed * cos(theta)) * win.deltaTime;
			playerY -= (moveSpeed * sin(theta)) * win.deltaTime;
		}

		drawRectangle(&win, playerX, playerY, playerWidth, playerHeight, playerRotation, COLOR_YELLOW);
		drawCircle(&win, circleX, circleY, circleR, COLOR_RED);

		printf("%f\n", win.framesPerSecond);

		renderWindow(win);
	}

	deleteWindow(&win);
	closeGrey();
}