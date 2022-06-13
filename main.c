/*

FAIR WARNING
This demo is NOT finished, so do not expect much from it.

*/
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
float PIECE_NEXT_OFFSET[7][2] = {
	{ // I
		0.5f, 2
	},
	{ // L
		1.5f, 1
	},
	{ // J
		1.5f, 1
	},
	{ // S
		1.5f, 1.5f
	},
	{ // Q
		1, 1.5f
	},
	{ // T
		1, 1.5f
	},
	{ // Z
		1, 1.5f
	}
};
int PIECE_COLORS[7] = {
	0, 0, 1, 1, 2, 2, 2
};
int currentPieceArray[8];
int nextPiece;
int nextPieceArray[8];
int rotateCycle = 0;
void changePiece(int piece[8]) {
	for (int i = 0; i < 8; i++) {
		currentPieceArray[i] = piece[i];
	}
}
void changeNextPiece(int piece[8]) {
	for (int i = 0; i < 8; i++) {
		nextPieceArray[i] = piece[i];
	}
}

// Tetris
float blockWidth = 539 - 49 / 10;
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
int garbage[10][21];
int testGarbageCollisionManual(int piece[8]) {
	for (int i = 0; i < 10; i++) {
		for (int z = 0; z < 21; z++) {
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
	accurateY += (_fallSpeed)*deltaTime;
	y = (int)accurateY;
	return 0;
}
int rotate(int direction) {
	x += PIECE_ROTATIONS[currentPiece][rotateCycle * 2];
	accurateY += PIECE_ROTATIONS[currentPiece][rotateCycle * 2 + 1];
	y = (int)accurateY;
	int duplicateArray[8];
	if (direction > 0) {
		for (int i = 0; i < 4; i++) {
			duplicateArray[i * 2] = currentPieceArray[i * 2 + 1];
			duplicateArray[i * 2 + 1] = -currentPieceArray[i * 2];
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			duplicateArray[i * 2] = -currentPieceArray[i * 2 + 1];
			duplicateArray[i * 2 + 1] = currentPieceArray[i * 2];
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
		if (rotateCycle + 1 < 4) {
			rotateCycle += 1;
		}
		else {
			rotateCycle = 0;
		}
		return 0;
	}
}
int checkLines() {
	int lineCounts[21] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int lines = 0;
	for (int i = 0; i < 10; i++) {
		for (int z = 0; z < 21; z++) {
			if (garbage[i][z] != 0) {
				lineCounts[z]++;
			}
		}
	}
	for (int i = 0; i < 21; i++) {
		if (lineCounts[i] >= 10) {
			lines++;
			for (int z = 0; z < 10; z++) {
				garbage[i][z] = 0;
			}
			for (int z = i - 1; z >= 0; z--) {
				for (int p = 0; p < 10; p++) {
					garbage[p][z + 1] = garbage[p][z];
				}
			}
		}
	}
	return lines;
}
float score = 0;
int lineCount = 0;
int lineCountTracker = 0;
int scoreFallMultiplier = 5;
int level = 0;
void clearGarbage() {
	for (int i = 0; i < 10; i++) {
		for (int z = 0; z < 21; z++) {
			garbage[i][z] = 0;
		}
	}
}
void changeLevel(int newLevel) {
	switch (newLevel) {
	default:
		backgroundColor[0] = 0; backgroundColor[1] = 0; backgroundColor[2] = 0; backgroundColor[3] = 255;
		tetrisBackgroundColor[0] = 0; tetrisBackgroundColor[1] = 0; tetrisBackgroundColor[2] = 0; tetrisBackgroundColor[3] = 255;
		borderColor[0] = 255; borderColor[1] = 255; borderColor[2] = 255; borderColor[3] = 255;
		pieceColors[0][0] = 255; pieceColors[0][1] = 255; pieceColors[0][2] = 255; pieceColors[0][3] = 255;
		pieceColors[1][0] = 255; pieceColors[1][1] = 255; pieceColors[1][2] = 255; pieceColors[1][3] = 255;
		pieceColors[2][0] = 255; pieceColors[2][1] = 255; pieceColors[2][2] = 255; pieceColors[2][3] = 255;
		break;
	case 0:
		backgroundColor[0] = 40; backgroundColor[1] = 47; backgroundColor[2] = 51; backgroundColor[3] = 255;
		tetrisBackgroundColor[0] = 30; tetrisBackgroundColor[1] = 35; tetrisBackgroundColor[2] = 38; tetrisBackgroundColor[3] = 255;
		borderColor[0] = 54; borderColor[1] = 68; borderColor[2] = 76; borderColor[3] = 255;
		pieceColors[0][0] = 114; pieceColors[0][1] = 132; pieceColors[0][2] = 142; pieceColors[0][3] = 255;
		pieceColors[1][0] = 97; pieceColors[1][1] = 107; pieceColors[1][2] = 137; pieceColors[1][3] = 255;
		pieceColors[2][0] = 19; pieceColors[2][1] = 142; pieceColors[2][2] = 99; pieceColors[2][3] = 255;
		break;
	case 1:
		backgroundColor[0] = 73; backgroundColor[1] = 218; backgroundColor[2] = 170; backgroundColor[3] = 255;
		tetrisBackgroundColor[0] = 182; tetrisBackgroundColor[1] = 239; tetrisBackgroundColor[2] = 206; tetrisBackgroundColor[3] = 255;
		borderColor[0] = 58; borderColor[1] = 174; borderColor[2] = 139; borderColor[3] = 255;
		pieceColors[0][0] = 66; pieceColors[0][1] = 197; pieceColors[0][2] = 155; pieceColors[0][3] = 255;
		pieceColors[1][0] = 71; pieceColors[1][1] = 217; pieceColors[1][2] = 152; pieceColors[1][3] = 255;
		pieceColors[2][0] = 55; pieceColors[2][1] = 125; pieceColors[2][2] = 101; pieceColors[2][3] = 255;
		break;
	case 2:
		backgroundColor[0] = 182; backgroundColor[1] = 37; backgroundColor[2] = 85; backgroundColor[3] = 255;
		tetrisBackgroundColor[0] = 73; tetrisBackgroundColor[1] = 16; tetrisBackgroundColor[2] = 49; tetrisBackgroundColor[3] = 255;
		borderColor[0] = 197; borderColor[1] = 81; borderColor[2] = 116; borderColor[3] = 255;
		pieceColors[0][0] = 198; pieceColors[0][1] = 58; pieceColors[0][2] = 89; pieceColors[0][3] = 255;
		pieceColors[1][0] = 142; pieceColors[1][1] = 29; pieceColors[1][2] = 80; pieceColors[1][3] = 255;
		pieceColors[2][0] = 200; pieceColors[2][1] = 130; pieceColors[2][2] = 154; pieceColors[2][3] = 255;
		break;
	case 3: // piiiink
		backgroundColor[0] = 255; backgroundColor[1] = 159; backgroundColor[2] = 201; backgroundColor[3] = 255;
		tetrisBackgroundColor[0] = 255; tetrisBackgroundColor[1] = 170; tetrisBackgroundColor[2] = 194; tetrisBackgroundColor[3] = 255;
		borderColor[0] = 250; borderColor[1] = 211; borderColor[2] = 212; borderColor[3] = 255;
		pieceColors[0][0] = 252; pieceColors[0][1] = 183; pieceColors[0][2] = 128; pieceColors[0][3] = 255;
		pieceColors[1][0] = 162; pieceColors[1][1] = 124; pieceColors[1][2] = 155; pieceColors[1][3] = 255;
		pieceColors[2][0] = 217; pieceColors[2][1] = 255; pieceColors[2][2] = 255; pieceColors[2][3] = 255;
		break;
	case 4: // strawberry
		backgroundColor[0] = 91; backgroundColor[1] = 16; backgroundColor[2] = 30; backgroundColor[3] = 255;
		tetrisBackgroundColor[0] = 175; tetrisBackgroundColor[1] = 87; tetrisBackgroundColor[2] = 105; tetrisBackgroundColor[3] = 255;
		borderColor[0] = 225; borderColor[1] = 212; borderColor[2] = 199; borderColor[3] = 255;
		pieceColors[0][0] = 188; pieceColors[0][1] = 74; pieceColors[0][2] = 151; pieceColors[0][3] = 255;
		pieceColors[1][0] = 188; pieceColors[1][1] = 213; pieceColors[1][2] = 151; pieceColors[1][3] = 255;
		pieceColors[2][0] = 255; pieceColors[2][1] = 213; pieceColors[2][2] = 151; pieceColors[2][3] = 255;
		break;
	case 5: // dark mode
		backgroundColor[0] = 38; backgroundColor[1] = 38; backgroundColor[2] = 38; backgroundColor[3] = 255;
		tetrisBackgroundColor[0] = 76; tetrisBackgroundColor[1] = 76; tetrisBackgroundColor[2] = 76; tetrisBackgroundColor[3] = 255;
		borderColor[0] = 63; borderColor[1] = 63; borderColor[2] = 63; borderColor[3] = 255;
		pieceColors[0][0] = 0; pieceColors[0][1] = 0; pieceColors[0][2] = 255; pieceColors[0][3] = 255;
		pieceColors[1][0] = 25; pieceColors[1][1] = 25; pieceColors[1][2] = 25; pieceColors[1][3] = 255;
		pieceColors[2][0] = 127; pieceColors[2][1] = 127; pieceColors[2][2] = 127; pieceColors[2][3] = 255;
		break;
	case 6: // burnt
		backgroundColor[0] = 100; backgroundColor[1] = 0; backgroundColor[2] = 0; backgroundColor[3] = 255;
		tetrisBackgroundColor[0] = 62; tetrisBackgroundColor[1] = 14; tetrisBackgroundColor[2] = 0; tetrisBackgroundColor[3] = 255;
		borderColor[0] = 145; borderColor[1] = 35; borderColor[2] = 0; borderColor[3] = 255;
		pieceColors[0][0] = 40; pieceColors[0][1] = 17; pieceColors[0][2] = 17; pieceColors[0][3] = 255;
		pieceColors[1][0] = 181; pieceColors[1][1] = 62; pieceColors[1][2] = 23; pieceColors[1][3] = 255;
		pieceColors[2][0] = 210; pieceColors[2][1] = 0; pieceColors[2][2] = 0; pieceColors[2][3] = 255;
		break;
	case 7: // LED
		backgroundColor[0] = 0; backgroundColor[1] = 0; backgroundColor[2] = 0; backgroundColor[3] = 255;
		tetrisBackgroundColor[0] = 127; tetrisBackgroundColor[1] = 127; tetrisBackgroundColor[2] = 127; tetrisBackgroundColor[3] = 255;
		borderColor[0] = 255; borderColor[1] = 255; borderColor[2] = 255; borderColor[3] = 255;
		pieceColors[0][0] = 0; pieceColors[0][1] = 0; pieceColors[0][2] = 255; pieceColors[0][3] = 255;
		pieceColors[1][0] = 0; pieceColors[1][1] = 255; pieceColors[1][2] = 0; pieceColors[1][3] = 255;
		pieceColors[2][0] = 255; pieceColors[2][1] = 0; pieceColors[2][2] = 0; pieceColors[2][3] = 255;
		break;
	case 8: // 50's
		backgroundColor[0] = 84; backgroundColor[1] = 84; backgroundColor[2] = 84; backgroundColor[3] = 255;
		tetrisBackgroundColor[0] = 36; tetrisBackgroundColor[1] = 36; tetrisBackgroundColor[2] = 36; tetrisBackgroundColor[3] = 255;
		borderColor[0] = 118; borderColor[1] = 118; borderColor[2] = 118; borderColor[3] = 255;
		pieceColors[0][0] = 102; pieceColors[0][1] = 102; pieceColors[0][2] = 102; pieceColors[0][3] = 255;
		pieceColors[1][0] = 67; pieceColors[1][1] = 67; pieceColors[1][2] = 67; pieceColors[1][3] = 255;
		pieceColors[2][0] = 151; pieceColors[2][1] = 151; pieceColors[2][2] = 151; pieceColors[2][3] = 255;
		break;
	case 9: // YIELD "it's time to slow down."
		backgroundColor[0] = 255; backgroundColor[1] = 255; backgroundColor[2] = 0; backgroundColor[3] = 255;
		tetrisBackgroundColor[0] = 255; tetrisBackgroundColor[1] = 255; tetrisBackgroundColor[2] = 0; tetrisBackgroundColor[3] = 255;
		borderColor[0] = 0; borderColor[1] = 0; borderColor[2] = 0; borderColor[3] = 255;
		pieceColors[0][0] = 0; pieceColors[0][1] = 0; pieceColors[0][2] = 0; pieceColors[0][3] = 255;
		pieceColors[1][0] = 0; pieceColors[1][1] = 0; pieceColors[1][2] = 0; pieceColors[1][3] = 255;
		pieceColors[2][0] = 0; pieceColors[2][1] = 0; pieceColors[2][2] = 0; pieceColors[2][3] = 255;
		break;
	}
}
void reset() {
	clearGarbage();
	changeLevel(0);
	currentPiece = rand() % 7;
	changePiece(PIECES[currentPiece]);
	nextPiece = rand() % 7;
	changeNextPiece(PIECES[nextPiece]);
	score = 0;
	lineCount = 0;
	lineCountTracker = 0;
	scoreFallMultiplier = 5;
	level = 0;
	x = 4, y = 0;
	accurateY = 0;
	fallSpeed = 1.0f;
	holdSpeed = 10.0f;
	pieceColor = 0;
	rotateCycle = 0;
}

int main() {
	initGrey(4);
	initArey();

	float offsetX = 0.0f, offsetY = 0.0f;

	Window win = createWindow(width / resolutionDivider, height / resolutionDivider, "grey");
	srand(win.startTime * 1000);

	FontID eightBitDragon = loadFont(&win, "resources/EightBitDragon.ttf", 50);

	currentPiece = rand() % 7;
	changePiece(PIECES[currentPiece]);

	nextPiece = rand() % 7;
	changeNextPiece(PIECES[nextPiece]);

	while (!shouldWindowClose(win)) {
		updateWindow(&win);

		srand(win.time * 1000);
		int lineCheck = checkLines();
		float addAmount = fallSpeed - 0.5f;
		addAmount *= 0.5f;
		switch (lineCheck) {
		case 0:
			// do nuting
			break;
		case 1:
			score += 100 * addAmount;
			break;
		case 2:
			score += 250 * addAmount;
			break;
		case 3:
			score += 500 * addAmount;
			break;
		case 4:
			score += 1000 * addAmount;
			break;
		default:
			// what
			break;
		}
		lineCount += lineCheck;
		lineCountTracker += lineCheck;
		if (lineCountTracker >= 10) {
			level += 1;
			fallSpeed += 0.4f;
			lineCountTracker -= 10;
			changeLevel(level);
		}
		moveY(win.deltaTime, fallSpeed);
		if (isKeyDown(win, KEY_S) || isKeyDown(win, KEY_DOWN)) {
			moveY(win.deltaTime, holdSpeed);
			score += (scoreFallMultiplier * fallSpeed * win.deltaTime);
		}
		if (testCollisionY(currentPieceArray) == -1) {
			for (int i = 0; i < 4; i++) {
				int drawX = x + (currentPieceArray[i * 2]), drawY = y + (currentPieceArray[i * 2 + 1]) - 1;
				garbage[drawX][drawY] = PIECE_COLORS[currentPiece]+1;
			}
			x = 4;
			accurateY = 0.0f;
			y = 0;
			rotateCycle = 0;
			changePiece(PIECES[nextPiece]);
			currentPiece = nextPiece;
			nextPiece = rand() % 7;
			changeNextPiece(PIECES[nextPiece]);
			if (testCollisionY(currentPieceArray) == -1 || testGarbageCollision() == -1) {
				reset();
			}
		}

		if (win.width / width < win.height / height) {
			resolutionDivider = width / win.width;
			offsetX = 0.0f;
		}
		else {
			resolutionDivider = height / win.height;
			offsetX = -((width / resolutionDivider) - win.width) / 2;
		}
		blockWidth = (539 - 49) / 10;

		clearWindowBackground(&win, backgroundColor);

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
		if (isKeyPressed(win, KEY_SPACE)) {
			int origY = y;
			int pointAdd = 0;
			while (testCollisionY(currentPieceArray) != -1) {
				y += 1;
				pointAdd += 1;
			}
			y -= 1;
			accurateY = (float)y + 1;
			score += pointAdd * fallSpeed;
		}
		if (isKeyPressed(win, KEY_LEFT_SHIFT) || isKeyPressed(win, KEY_RIGHT_SHIFT)) {
			int origY = y;
			int pointAdd = 0;
			while (testCollisionY(currentPieceArray) != -1) {
				y += 1;
				pointAdd += 1;
			}
			y -= 1;
			accurateY = (float)y;
			score += pointAdd * fallSpeed;
		}

		// Draw UI
		/// Borders
		drawRectangle(&win, offsetX + fX(36), fX(36), fX(552 - 36), fX(1042 - 36), 0, borderColor);
		drawRectangle(&win, offsetX + fX(576), fX(85), fX(846 - 576), fX(230 - 85), 0, borderColor);
		drawRectangle(&win, offsetX + fX(576), fX(330), fX(846 - 576), fX(601 - 330), 0, borderColor);
		drawRectangle(&win, offsetX + fX(576), fX(919), fX(846 - 576), fX(1042 - 919), 0, borderColor);
		/// Tetris background
		drawRectangle(&win, offsetX + fX(49), fX(49), fX(539 - 49), fX(1029 - 49), 0, tetrisBackgroundColor);
		drawRectangle(&win, offsetX + fX(589), fX(98), fX(833 - 589), fX(217 - 98), 0, tetrisBackgroundColor);
		drawRectangle(&win, offsetX + fX(589), fX(343), fX(833 - 589), fX(588 - 343), 0, tetrisBackgroundColor);
		drawRectangle(&win, offsetX + fX(589), fX(932), fX(833 - 589), fX(1029 - 932), 0, tetrisBackgroundColor);

		// Draw garbage
		for (int i = 0; i < 10; i++) {
			for (int z = 0; z < 20; z++) {
				if (garbage[i][z] != 0) {
					drawRectangle(&win, offsetX + fX(49 + (i * blockWidth)), fX(49 + (z * blockWidth)), fX(blockWidth), fX(blockWidth), 0, pieceColors[garbage[i][z] - 1]);
				}
			}
		}
		// Draw piece
		for (int i = 0; i < 4; i++) {
			int drawX = x + (currentPieceArray[i * 2]), drawY = y + (currentPieceArray[i * 2 + 1]);
			drawRectangle(&win, offsetX + fX(49 + (drawX * blockWidth)), fX(49 + (drawY * blockWidth)), fX(blockWidth), fX(blockWidth), 0, pieceColors[PIECE_COLORS[currentPiece]]);
		}
		// Draw drop piece
		int origY = y;
		int dropY = y;
		while (testCollisionY(currentPieceArray) != -1) {
			y += 1;
		}
		dropY = y - 1;
		y = origY;
		for (int i = 0; i < 4; i++) {
			int drawX = x + (currentPieceArray[i * 2]), drawY = dropY + (currentPieceArray[i * 2 + 1]);
			Color drawColor;
			for (int z = 0; z < 4; z++) {
				drawColor[z] = pieceColors[PIECE_COLORS[currentPiece]][z];
			}
			drawColor[3] = 100;
			drawRectangle(&win, offsetX + fX(49 + (drawX * blockWidth)), fX(49 + (drawY * blockWidth)), fX(blockWidth), fX(blockWidth), 0, drawColor);
		}
		// Draw next piece
		for (int i = 0; i < 4; i++) {
			float drawX = 0 + (nextPieceArray[i * 2] + PIECE_NEXT_OFFSET[nextPiece][0]), drawY = 0 + (nextPieceArray[i * 2 + 1] + PIECE_NEXT_OFFSET[nextPiece][1]);
			drawRectangle(&win, offsetX + fX(589 + (drawX * blockWidth)), fX(343 + (drawY * blockWidth)), fX(blockWidth), fX(blockWidth), 0, pieceColors[PIECE_COLORS[nextPiece]]);
		}

		int length = snprintf(NULL, 0, "Score: %i", (int)score);
		char* scoreText = malloc((double)length + 1);
		snprintf(scoreText, (double)length + 1, "Score: %i", (int)score);

		float scale = 153 - 113;
		while (813 - (607 + getWidthOfText(&win, scoreText, eightBitDragon, scale)) > 0) {
			scale += 1;
		}
		while (813 - (607 + getWidthOfText(&win, scoreText, eightBitDragon, scale)) < 0) {
			scale -= 1;
		}

		int linesLength = snprintf(NULL, 0, "Lines: %i", lineCount);
		char* linesText = malloc((double)linesLength + 1);
		snprintf(linesText, (double)linesLength + 1, "Lines: %i", lineCount);

		float linesTextScale = 153 - 113;
		while (813 - (607 + getWidthOfText(&win, linesText, eightBitDragon, linesTextScale)) > 0) {
			linesTextScale += 1;
		}
		while (813 - (607 + getWidthOfText(&win, linesText, eightBitDragon, linesTextScale)) < 0) {
			linesTextScale -= 1;
		}

		int levelLength = snprintf(NULL, 0, "Level: %i", level);
		char* levelText = malloc((double)levelLength + 1);
		snprintf(levelText, (double)levelLength + 1, "Level: %i", level);

		float levelTextScale = 153 - 113;
		while (813 - (607 + getWidthOfText(&win, levelText, eightBitDragon, levelTextScale)) > 0) {
			levelTextScale += 1;
		}
		while (813 - (607 + getWidthOfText(&win, levelText, eightBitDragon, levelTextScale)) < 0) {
			levelTextScale -= 1;
		}

		drawBorderedText(&win, scoreText, eightBitDragon, offsetX + fX(611), fX(107), fX(scale), fX(2), borderColor, backgroundColor);
		drawBorderedText(&win, linesText, eightBitDragon, offsetX + fX(611), fX(954), fX(linesTextScale), fX(2), borderColor, backgroundColor);
		drawBorderedText(&win, levelText, eightBitDragon, offsetX + fX(611), fX(152), fX(levelTextScale), fX(2), borderColor, backgroundColor);
		free(scoreText);
		free(linesText);
		free(levelText);

		renderWindow(win);
	}

	deleteWindow(&win);

	closeArey();
	closeGrey();
	return 0;
}