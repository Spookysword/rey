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
	{ // L
		0, 0, 0, 1, 0, 2, 1, 2
	}
};
int PIECE_ROTATIONS[7][8] = {
	{ // L
		2, 0, 0, 2, -2, 0, 0, -2
	}
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
int x = 0, y = 0;
float accurateY = 0;
float fallSpeed = 1.0f;
float holdSpeed = 10.0f;
Color pieceColor1 = { 114, 132, 142, 255 };
Color pieceColor2 = { 97, 107, 137, 255 };
int testCollision(int piece[8]) {
	for (int i = 0; i < 4; i++) {
		int drawX = x + (piece[i * 2]), drawY = y + (piece[i * 2 + 1]);
		if (drawX < 0 || drawX > 9) { return -1; }
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

int main() {
	initGrey(4);
	initArey();
	
	Window win = createWindow(width/resolutionDivider, height/resolutionDivider, "grey");
	
	changePiece(PIECES[currentPiece]);

	while (!shouldWindowClose(win)) {
		updateWindow(&win);
		moveY(win.deltaTime, fallSpeed);

		if (win.width/width < win.height/height) {
			resolutionDivider = width/win.width;
		} else {
			resolutionDivider = height/win.height;
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
		if (isKeyPressed(win, KEY_UP)) { rotate(-1); }
		if (isKeyDown(win, KEY_S) || isKeyDown(win, KEY_DOWN)) { moveY(win.deltaTime, holdSpeed); }

		// Draw UI
		/// Borders
		drawRectangle(&win, fX(36), fX(36), fX(552-36), fX(1042-36), 0, borderColor);
		drawRectangle(&win, fX(576), fX(85), fX(846-576), fX(230-85), 0, borderColor);
		drawRectangle(&win, fX(576), fX(330), fX(846-576), fX(601-330), 0, borderColor);
		drawRectangle(&win, fX(576), fX(919), fX(846-576), fX(1042-919), 0, borderColor);
		/// Tetris background
		drawRectangle(&win, fX(49), fX(49), fX(539-49), fX(1029-49), 0, tetrisBackgroundColor);
		drawRectangle(&win, fX(589), fX(98), fX(833-589), fX(217-98), 0, tetrisBackgroundColor);
		drawRectangle(&win, fX(589), fX(343), fX(833-589), fX(588-343), 0, tetrisBackgroundColor);
		drawRectangle(&win, fX(589), fX(932), fX(833-589), fX(1029-932), 0, tetrisBackgroundColor);

		// Draw piece
		for (int i = 0; i < 4; i++) {
			int drawX = x+(currentPieceArray[i*2]), drawY = y+(currentPieceArray[i*2+1]);
			drawRectangle(&win, fX(49+(drawX *blockWidth)), fX(49+(drawY*blockWidth)), fX(blockWidth), fX(blockWidth), 0, pieceColor1);
		}

		renderWindow(win);
	}

	deleteWindow(&win);

	closeArey();
	closeGrey();
	return 0;
}