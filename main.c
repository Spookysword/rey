#include <grey.h>
#include <stdio.h>
#include <arey.h>

// Menu
float resolutionDivider = 1.5;
float width = 884, height = 1080;
Color backgroundColor = { 40, 47, 51, 255 };
Color tetrisBackgroundColor = { 30, 35, 38, 255 };
Color borderColor = { 54, 68, 76, 255 };
float fX(float x) {
	return x / resolutionDivider;
}

// Pieces
int currentPiece = 0;
int PIECES[7][8] = {
	{ // I
		0, 0, 1, 0, 2, 0, 3, 0
	},
	{ // L
		1, 0, 1, 1, 1, 2, 0, 2
	},
	{ // J
		0, 0, 0, 1, 0, 2, 1, 2
	},
	{ // S
		0, 0, 1, 0, 0, 1, 1, 1
	},
	{ // Q
		1, 0, 2, 0, 0, 1, 1, 1
	},
	{ // T
		1, 0, 0, 1, 1, 1, 2, 1
	},
	{ // Z
		0, 0, 1, 0, 1, 1, 2, 1
	}
};
int PIECE_ROTATIONS[7][8] = {
	{ // I
		2, -1, 1, 1, -1, 2, -2, -2
	},
	{ // L
		1, 1, -1, 1, -1, -1, 1, -1
	},
	{ // J
		2, 0, 0, 2, -2, 0, 0, -2
	},
	{ // S
		1, 0, 0, 1, -1, 0, 0, -1
	},
	{ // Q
		1, -1, 1, 2, -2, 0, 0, -1
	},
	{ // T
		2, 0, 0, 2, -2, 0, 0, -2
	},
	{ // Z
		2, -1, 0, 2, -1, 0, -1, -1
	}
};
int PIECE_COLORS[7] = {
	0, 0, 1, 1, 2, 2, 2
};
int currentPieceArray[8];
int rotateCycle = 0;
void changePiece(int piece[8]) {
	for (int i = 0; i < 8; i++) {
		currentPieceArray[i] = piece[i];
	}
}

// Tetris
float blockWidth = 539-49/10;
int x = 4, y = 0;
float accurateY = 0;
float fallSpeed = 1.0f;
float holdSpeed = 10.0f;
int pieceColor = 0;
Color pieceColors[3] = {
	{ 114, 132, 142, 255 },
	{ 97, 107, 137, 255 },
	{ 19, 142, 99, 255 }
};
int garbage[10][20];
int testGarbageCollisionManual(int piece[8]) {
	for (int i = 0; i < 10; i++) {
		for (int z = 0; z < 20; z++) {
			if (garbage[i][z] != 0) {
				for (int j = 0; j < 4; j++) {
					int drawX = x + (piece[j * 2]), drawY = y + (piece[j * 2 + 1]) - 1;
					if (drawX == i && drawY + 1 == z) {
						return -1;
					}
				}
			}
		}
	}
	return 0;
}
int testGarbageCollision() {
	return testGarbageCollisionManual(currentPieceArray);
}
int testCollision(int piece[8]) {
	for (int i = 0; i < 4; i++) {
		int drawX = x + (piece[i * 2]), drawY = y + (piece[i * 2 + 1]);
		if (drawX < 0 || drawX > 9) { return -1; }
	}
	if (testGarbageCollisionManual(piece) == -1) {
		return -1;
	}
	return 0;
}
int testCollisionY(int piece[8]) {
	for (int i = 0; i < 4; i++) {
		int drawX = x + (piece[i * 2]), drawY = y + (piece[i * 2 + 1]);
		if (drawY > 19) { return -1; }
	}
	if (testGarbageCollision() == -1) {
		return -1;
	}
	return 0;
}
int moveX(int direction) {
	x += direction;
	if (testCollision(currentPieceArray) == -1) {
		x -= direction; return -1;
	}
	return 0;
}
int moveY(float deltaTime, float _fallSpeed) {
	accurateY += (_fallSpeed) * deltaTime;
	y = (int)accurateY;
	return 0;
}
int rotate(int direction) {
	x += PIECE_ROTATIONS[currentPiece][rotateCycle*2];
	accurateY += PIECE_ROTATIONS[currentPiece][rotateCycle*2+1];
	y = (int)accurateY;
	int duplicateArray[8];
	if (direction > 0) {
		for (int i = 0; i < 4; i++) {
			duplicateArray[i*2] = currentPieceArray[i*2+1];
			duplicateArray[i*2+1] = -currentPieceArray[i*2];
		}
	} else {
		for (int i = 0; i < 4; i++) {
			duplicateArray[i*2] = -currentPieceArray[i*2+1];
			duplicateArray[i*2+1] = currentPieceArray[i*2];
		}
	}
	if (testCollision(duplicateArray) == -1) {
		x -= PIECE_ROTATIONS[currentPiece][rotateCycle * 2];
		accurateY -= PIECE_ROTATIONS[currentPiece][rotateCycle * 2 + 1];
		y = (int)accurateY;
		return -1;
	}
	else {
		for (int i = 0; i < 8; i++) {
			currentPieceArray[i] = duplicateArray[i];
		}
		if (rotateCycle+1 < 4) {
			rotateCycle += 1;
		} else {
			rotateCycle = 0;
		}
		return 0;
	}
}
void checkLines() {
	int lineCounts[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int i = 0; i < 10; i++) {
		for (int z = 0; z < 20; z++) {
			if (garbage[i][z] != 0) {
				lineCounts[z]++;
			}
		}
	}
	for (int i = 0; i < 20; i++) {
		if (lineCounts[i] >= 10) {
			for (int z = 0; z < 10; z++) {
				garbage[i][z] = 0;
			}
			for (int z = i-1; z >= 0; z--) {
				for (int p = 0; p < 10; p++) {
					garbage[p][z+1] = garbage[p][z];
				}
			}
		}
	}
}

int main() {
	initGrey(4);
	initArey();

	float offsetX = 0.0f, offsetY = 0.0f;

	Window win = createWindow(width/resolutionDivider, height/resolutionDivider, "grey");
	srand(win.startTime * 1000);

	FontID eightBitDragon = loadFont(&win, "resources/EightBitDragon.ttf", 50);
	
	currentPiece = rand()%7;
	changePiece(PIECES[currentPiece]);

	while (!shouldWindowClose(win)) {
		updateWindow(&win);
		srand(win.time*1000);
		checkLines();
		moveY(win.deltaTime, fallSpeed);
		if (isKeyDown(win, KEY_S) || isKeyDown(win, KEY_DOWN)) { moveY(win.deltaTime, holdSpeed); }
		if (testCollisionY(currentPieceArray) == -1) {
			for (int i = 0; i < 4; i++) {
				int drawX = x+(currentPieceArray[i*2]), drawY = y+(currentPieceArray[i*2+1])-1;
				garbage[drawX][drawY] = PIECE_COLORS[currentPiece]+1;
			}
			x = 4;
			accurateY = 0.0f;
			y = 0;
			rotateCycle = 0;
			currentPiece = rand()%7;
			changePiece(PIECES[currentPiece]);
		}

		if (win.width/width < win.height/height) {
			resolutionDivider = width/win.width;
			offsetX = 0.0f;
		} else {
			resolutionDivider = height/win.height;
			offsetX = -((width/resolutionDivider)-win.width)/2;
		}
		blockWidth = (539-49)/10;

		clearWindowBackground(win, backgroundColor);

		if (isKeyDown(win, KEY_ESCAPE)) {
			closeWindow(win);
		}

		if (isKeyPressed(win, KEY_F)) {
			printf("%f\n", win.framesPerSecond);
		}

		if (isKeyPressed(win, KEY_F11)) {
			win.fullscreen = !win.fullscreen;
		}

		//setWireframeMode(win, isKeyDown(win, KEY_SPACE));

		// Input
		if (isKeyPressed(win, KEY_A) || isKeyPressed(win, KEY_LEFT)) { moveX(-1); }
		if (isKeyPressed(win, KEY_D) || isKeyPressed(win, KEY_RIGHT)) { moveX(1); }
		if (isKeyPressed(win, KEY_W) || isKeyPressed(win, KEY_UP)) { rotate(-1); }

		// Draw UI
		/// Borders
		drawRectangle(&win, offsetX+fX(36), fX(36), fX(552-36), fX(1042-36), 0, borderColor);
		drawRectangle(&win, offsetX+fX(576), fX(85), fX(846-576), fX(230-85), 0, borderColor);
		drawRectangle(&win, offsetX+fX(576), fX(330), fX(846-576), fX(601-330), 0, borderColor);
		drawRectangle(&win, offsetX+fX(576), fX(919), fX(846-576), fX(1042-919), 0, borderColor);
		/// Tetris background
		drawRectangle(&win, offsetX+fX(49), fX(49), fX(539-49), fX(1029-49), 0, tetrisBackgroundColor);
		drawRectangle(&win, offsetX+fX(589), fX(98), fX(833-589), fX(217-98), 0, tetrisBackgroundColor);
		drawRectangle(&win, offsetX+fX(589), fX(343), fX(833-589), fX(588-343), 0, tetrisBackgroundColor);
		drawRectangle(&win, offsetX+fX(589), fX(932), fX(833-589), fX(1029-932), 0, tetrisBackgroundColor);

		// Draw garbage
		for (int i = 0; i < 10; i++) {
			for (int z = 0; z < 20; z++) {
				if (garbage[i][z] != 0) {
					drawRectangle(&win, offsetX+fX(49+(i*blockWidth)), fX(49+(z*blockWidth)), fX(blockWidth), fX(blockWidth), 0, pieceColors[garbage[i][z]-1]);
				}
			}
		}
		// Draw piece
		for (int i = 0; i < 4; i++) {
			int drawX = x+(currentPieceArray[i*2]), drawY = y+(currentPieceArray[i*2+1]);
			drawRectangle(&win, offsetX+fX(49+(drawX*blockWidth)), fX(49+(drawY*blockWidth)), fX(blockWidth), fX(blockWidth), 0, pieceColors[PIECE_COLORS[currentPiece]]);
		}

		drawText(&win, "test", eightBitDragon, 0, 0, 10.0f, COLOR_WHITE);

		renderWindow(win);
	}

	deleteWindow(&win);

	closeArey();
	closeGrey();
	return 0;
}