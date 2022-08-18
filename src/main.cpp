#include <grey/grey.hpp>
#include <mrey/mrey.h>
#include <vector>
#include <string>
#include <algorithm>
using std::vector;
using std::pair;

#define PID2   1.57079633
#define PIT2   6.28318531
#define PID4   0.78539816
#define PITP25 PID4
#define PITP75 2.35619449

int scale = 5;

int nScreenWidth = 1280/scale;
int nScreenHeight = 720/scale;
int nSpotSize = 1*scale;
float nSpotBorder = 0;

float reyspeed = 0.01;

int nHitPoints = 100;

float fPlayerX = 8.0f;
float fPlayerY = 8.0f;
float fPlayerRealA = 0.0f;
float fPlayerA = 0.0f;

float fFOV = PID4;

int nMapHeight = 32;
int nMapWidth = 32;

float maxBrightness = 0.8f;
float brightnessMod = 0.5f; // smaller values make it brighter up close, but darker farther away

bool scary = true;
bool garfiledMove = true;
int scaryModifier = 15;

bool bShowMap = true;

float fDepth = 18;

float mapDisplaySize = 5.0f;

int getPosition(int x, int y) {
	return x + y * nScreenWidth;
}

Vec2 getPosition(int index) {
	return Vec2_new(index % nScreenWidth, index / nScreenWidth);
}

bool isEnemy(vector<Vec2> enemies, int x, int y) {
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].x == x && enemies[i].y == y) {
			return true;
		}
	}
	return false;
}


int main() {
	initGrey(4);

	Window win(1280, 720, "garfiled simulator 2009");
	win.setFlag(WINDOW_RESIZABLE, false);

	Texture tex0 = win.loadTexture("resources/block.png");
	vector<vector<Color>> tex0colors = win.loadTexturePixels(tex0);

	// Texture tex1 = win.loadTexture("resources/monster.png");
	// vector<vector<Color>> tex1colors = win.loadTexturePixels(tex1);

	// Texture tex2 = win.loadTexture("resources/enemy.png");
	// vector<vector<Color>> tex2colors = win.loadTexturePixels(tex2);

	Texture enemyTex = win.loadTexture("resources/enemy.png");
	vector<vector<Color>> enemyColors = win.loadTexturePixels(enemyTex);

	FontID arial = win.loadFont("resources/arial.ttf", 50);

	float* fDepthBuffer = nullptr;


	vector<Color> screen;

	for (int i = 0; i < nScreenWidth * nScreenHeight; i++) {
		screen.push_back(COLOR_BLACK);
	}

	std::wstring map;
	map += L"################################";
	map += L"#                              #";
	map += L"#                      ###     #";
	map += L"#                      ###     #";
	map += L"#################              #";
	map += L"#                              #";
	map += L"#                #             #";
	map += L"#                #             #";
	map += L"#                ###############";
	map += L"#       #                      #";
	map += L"#       #                      #";
	map += L"#       #                      #";
	map += L"#       ########################";
	map += L"#                              #";
	map += L"#       #                      #";
	map += L"#       #                      #";
	map += L"#       ##############         #";
	map += L"#                    #         #";
	map += L"#     ############   #         #";
	map += L"#                #   #         #";
	map += L"#                #   #         #";
	map += L"#                #   #         #";
	map += L"#                #   #         #";
	map += L"#                #   #         #";
	map += L"#       ########### ##         #";
	map += L"#       #       ######         #";
	map += L"#       #                      #";
	map += L"#       #                      #";
	map += L"#       #                      #";
	map += L"#                              #";
	map += L"#                              #";
	map += L"################################";

	vector<Vec2> enemies;
	enemies.push_back(Vec2_new(15, 15));

	fDepthBuffer = new float[nScreenWidth];

	bool mouseLocked = false;
	int lastSecond = 0;

	while (win) {
		win.update();
		float diffx = fPlayerX - enemies[0].x;
		float diffy = fPlayerY - enemies[0].y;

		if (diffx == 0 && diffy == 0) {
			nHitPoints--;
		}
		while (abs(diffx) + abs(diffy) > 5.0f) {
			diffx /= 1.5f;
			diffy /= 1.5f;
		}

		enemies[0].x += diffx*win.win.deltaTime;
		enemies[0].y += diffy*win.win.deltaTime;

		if (nHitPoints <= 0) {
			fPlayerX = 8.0f;
			fPlayerY = 8.0f;
			fPlayerRealA = 0.0f;
			nHitPoints = 50;
		}

		win.clearColor(COLOR_BLACK);
		

		// if (win.isKeyDown(KEY_A)) {
		// 	fPlayerRealA -= 1.5f * win.win.deltaTime;
		// }
		// if (win.isKeyDown(KEY_D)) {
		// 	fPlayerRealA += 1.5f * win.win.deltaTime;
		// }
		
		if (win.isKeyPressed(KEY_ESCAPE)) {
			setMouseLocked(&win.win, false);
			mouseLocked = false;
		}

		if (win.win.mouse.isPrimaryPressed) {
			setMousePos(&win.win, win.win.width/2, win.win.height/2);
			setMouseLocked(&win.win, true);
			mouseLocked = true;
		}
		
		if (mouseLocked) {
			float deltax = win.win.mouse.x - win.win.width/2;

			fPlayerRealA += deltax * win.win.deltaTime * 0.1f;

			setMousePos(&win.win, win.win.width/2, win.win.height/2);
		}

		if (win.isKeyDown(KEY_E)) {
			fPlayerA = fPlayerRealA + PI;
		} else {
			fPlayerA = fPlayerRealA;
		}


		if (win.isKeyDown(KEY_W)) {
			fPlayerX += sinf(fPlayerRealA) * 5.0f * win.win.deltaTime;
			fPlayerY += cosf(fPlayerRealA) * 5.0f * win.win.deltaTime;

			if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#' || isEnemy(enemies, (int)fPlayerX, (int)fPlayerY)) {
				if (isEnemy(enemies, (int)fPlayerX, (int)fPlayerY)) nHitPoints--;
				fPlayerX -= sinf(fPlayerRealA) * 5.0f * win.win.deltaTime;
				fPlayerY -= cosf(fPlayerRealA) * 5.0f * win.win.deltaTime;
			}
		}

		if (win.isKeyDown(KEY_S)) {
			fPlayerX -= sinf(fPlayerRealA) * 5.0f * win.win.deltaTime;
			fPlayerY -= cosf(fPlayerRealA) * 5.0f * win.win.deltaTime;

			if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#' || isEnemy(enemies, (int)fPlayerX, (int)fPlayerY)) {
				if (isEnemy(enemies, (int)fPlayerX, (int)fPlayerY)) nHitPoints--;
				fPlayerX += sinf(fPlayerRealA) * 5.0f * win.win.deltaTime;
				fPlayerY += cosf(fPlayerRealA) * 5.0f * win.win.deltaTime;
			}
		}

		if (win.isKeyDown(KEY_D)) {
			fPlayerX += sinf(fPlayerRealA+PID2) * 3.0f * win.win.deltaTime;
			fPlayerY += cosf(fPlayerRealA+PID2) * 3.0f * win.win.deltaTime;

			if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#' || isEnemy(enemies, (int)fPlayerX, (int)fPlayerY)) {
				if (isEnemy(enemies, (int)fPlayerX, (int)fPlayerY)) nHitPoints--;
				fPlayerX -= sinf(fPlayerRealA+PID2) * 3.0f * win.win.deltaTime;
				fPlayerY -= cosf(fPlayerRealA+PID2) * 3.0f * win.win.deltaTime;
			}
		}

		if (win.isKeyDown(KEY_A)) {
			fPlayerX += sinf(fPlayerRealA-PID2) * 3.0f * win.win.deltaTime;
			fPlayerY += cosf(fPlayerRealA-PID2) * 3.0f * win.win.deltaTime;

			if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#' || isEnemy(enemies, (int)fPlayerX, (int)fPlayerY)) {
				if (isEnemy(enemies, (int)fPlayerX, (int)fPlayerY)) nHitPoints--;
				fPlayerX -= sinf(fPlayerRealA-PID2) * 3.0f * win.win.deltaTime;
				fPlayerY -= cosf(fPlayerRealA-PID2) * 3.0f * win.win.deltaTime;
			}
		}

		for (int i = 0; i < nScreenWidth * nScreenHeight; i++) {
			if ((Color)screen[i] == (Color)COLOR_BLACK) {
				continue;
			}
			win.drawRectangle(getPosition(i).x*nSpotSize-nSpotBorder,getPosition(i).y*nSpotSize-nSpotBorder, nSpotSize-2*nSpotBorder, nSpotSize-2*nSpotBorder, 0, screen[i]);
			screen[i] = COLOR_BLACK;
		}
		if (bShowMap) {
			win.drawRectangle(0, 0, nMapWidth*mapDisplaySize, nMapHeight*mapDisplaySize, 0, COLOR_WHITE);
			for (int i = 0; i < nMapWidth; i++) {
				for (int j = 0; j < nMapHeight; j++) {
					if (map[j * nMapWidth + ((nMapWidth-1)-i)] == '#')
						win.drawRectangle(i*mapDisplaySize, j*mapDisplaySize, mapDisplaySize, mapDisplaySize, 0, COLOR_BLACK);
					if (isEnemy(enemies, ((nMapWidth-1)-i), j))
						win.drawRectangle(i*mapDisplaySize, j*mapDisplaySize, mapDisplaySize, mapDisplaySize, 0, COLOR_RED);
					
				}
			}
		}
		
		for (int x = 0; x < nScreenWidth; x++) {
			float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)nScreenWidth) * fFOV;
			float fDistanceToWall = 0.0f;
			bool bHitWall = false;
			int walltype = 0;

			float fSampleX = 0.0f;

			float fEyeX = sinf(fRayAngle);
			float fEyeY = cosf(fRayAngle);

			while (!bHitWall && fDistanceToWall < fDepth) {
				fDistanceToWall += reyspeed;

				int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
				int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

				if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight) {
					bHitWall = true;
					fDistanceToWall = fDepth;
				} else {
					if (map[nTestY * nMapWidth + nTestX] == L'#') {
						bHitWall = true;
						// if (isEnemy(enemies, nTestX, nTestY))
						// 	walltype = 1;
						// if (map[nTestY * nMapWidth + nTestX] == L'#' && isEnemy(enemies, nTestX, nTestY))
						// 	walltype = 2;


						float fBlockMidX = (float)nTestX + 0.5f;
						float fBlockMidY = (float)nTestY + 0.5f;

						float fTestPointX = fPlayerX + fEyeX * fDistanceToWall;
						float fTestPointY = fPlayerY + fEyeY * fDistanceToWall;

						float fTestAngle = atan2f((fTestPointY - fBlockMidY), (fTestPointX - fBlockMidX));
						if (fTestAngle >= -PITP25 && fTestAngle < PITP25)
							fSampleX = fTestPointY - (float)nTestY;
						if (fTestAngle >= PITP25 && fTestAngle < PITP75)
							fSampleX = fTestPointX - (float)nTestX;
						if (fTestAngle < -PITP25 && fTestAngle >= -PITP75)
							fSampleX = fTestPointX - (float)nTestX;
						if (fTestAngle >= PITP75 || fTestAngle < -PITP75)
							fSampleX = fTestPointY - (float)nTestY;

					}
				}
			}
			int nCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistanceToWall);
			int nFloor = nScreenHeight - nCeiling;

			fDepthBuffer[x] = fDistanceToWall;

			for (int y = 0; y < nScreenHeight; y++) {
				if (y < nCeiling) {
					float color = ((float)(nScreenHeight-y)-(nScreenHeight/2)) / (float)nScreenHeight * 255;
					screen[getPosition(x, y)] = Color(color, color, color, 255);
				} else if (y+1 > nCeiling && y < nFloor) {
					float fSampleY = ((float)y - (float)nCeiling) / ((float)nFloor - (float)nCeiling);
					
					float multiplier = (1/(fDistanceToWall*brightnessMod)-(1/(fDepth*brightnessMod)));
					if (multiplier > maxBrightness) {
						multiplier = maxBrightness;
					}

					if (fDistanceToWall >= fDepth) {
						screen[getPosition(x, y)] = COLOR_BLACK;
					} else {
						float threshold =fDistanceToWall*0.005f + 0.02f;
						if (fSampleX > 1.0f-threshold || fSampleX < 0.0f+threshold || fSampleY > 1.0f-threshold || fSampleY < 0.0f+threshold) {
							screen[getPosition(x, y)] = (((Color)COLOR_WHITE) * multiplier).rgb_(255);
						} else {
							if (walltype == 0) {
								screen[getPosition(x, y)] = (tex0colors[fSampleX*tex0colors.size()][fSampleY*tex0colors[0].size()] * multiplier ).rgb_(255); // wall
							 } // else if (walltype == 1) {
							// 	screen[getPosition(x, y)] = (tex2colors[fSampleX*tex2colors.size()][fSampleY*tex2colors[0].size()] * multiplier ).rgb_(255); // garfiled
							// } else if (walltype == 2) {
							// 	screen[getPosition(x, y)] = (tex1colors[fSampleX*tex2colors.size()][fSampleY*tex2colors[0].size()] * multiplier ).rgb_(255); // garfiled wall
							// }
						}
					}

				} else {
					float color = ((float)y-(nScreenHeight/2)) / (float)nScreenHeight * 255;
					screen[getPosition(x, y)] = Color(color, color, color, 255);
				}
			}
			float xoff = fDistanceToWall * cos(fRayAngle-PID2)*mapDisplaySize;
			float yoff = fDistanceToWall * sin(fRayAngle-PID2)*mapDisplaySize;
			win.drawLine(((nMapWidth)-fPlayerX)*mapDisplaySize, fPlayerY*mapDisplaySize, ((nMapWidth)-fPlayerX)*mapDisplaySize-xoff, fPlayerY*mapDisplaySize-yoff, 1, COLOR_GREEN);
		}
		if (bShowMap)
		for (int i = 0; i < enemies.size(); i++) {
			win.drawLine(((nMapWidth)-fPlayerX)*mapDisplaySize, fPlayerY*mapDisplaySize, ((nMapWidth)-enemies[i].x)*mapDisplaySize, enemies[i].y*mapDisplaySize, 1, COLOR_RED);
		}
		bool bFoundScary = false;
		for (int i = 0; i < enemies.size(); i++) {
			float fVecX = enemies[i].x - fPlayerX;
			float fVecY = enemies[i].y - fPlayerY;
			float fDistanceFromPlayer = sqrtf(fVecX * fVecX + fVecY * fVecY);

			float fEyeX = sinf(fPlayerA);
			float fEyeY = cosf(fPlayerA);
			float fObjectAngle = atan2f(fEyeY, fEyeX) - atan2f(fVecY, fVecX);
			if (fObjectAngle < -PI)
				fObjectAngle += PIT2;
			if (fObjectAngle > PI)
				fObjectAngle -= PIT2;

			bool bInPlayerFOV = fabs(fObjectAngle) < fFOV / 2.0f;

			if (bInPlayerFOV && fDistanceFromPlayer >= 0.5f && fDistanceFromPlayer < fDepth) {
				float fObjectCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistanceFromPlayer);
				float fObjectFloor = nScreenHeight - fObjectCeiling;
				float fObjectHeight = fObjectFloor - fObjectCeiling;
				float fObjectAspectRatio =  enemyColors[0].size() / enemyColors.size(); // ############## MIGHT BE BACKWARDS :/
				float fObjectWidth = fObjectHeight / fObjectAspectRatio;

				float fMiddleOfObject = (0.5f * (fObjectAngle / (fFOV / 2.0f)) + 0.5f) * nScreenWidth;

				// #################### https://www.youtube.com/watch?v=HEb2akswCcw      30:38
				
				//win.drawTexture(enemyTex, (fMiddleOfObject - fObjectWidth / 2.0f)*nSpotSize, (fObjectCeiling)*nSpotSize, fObjectWidth*nSpotSize, fObjectHeight*nSpotSize, 0, COLOR_WHITE);
				float multiplier = (1/(fDistanceFromPlayer*brightnessMod)-(1/(fDepth*brightnessMod)));
					if (multiplier > maxBrightness) {
						multiplier = maxBrightness;
					}
				for (float lx = 0; lx < fObjectWidth; lx++) {
					for (float ly = 0; ly < fObjectHeight; ly++) {
						float fSampleX = lx / fObjectWidth;
						float fSampleY = ly / fObjectHeight;

						Color c = enemyColors[(int)(fSampleX*enemyColors.size())][(int)(fSampleY*enemyColors[0].size())];
						int nPixelX = (int)(fMiddleOfObject - fObjectWidth / 2.0f + lx);
						if (nPixelX >= 0 && nPixelX < nScreenWidth && (int)(fObjectCeiling + ly) >= 0 && (int)(fObjectCeiling + ly) < nScreenWidth && c.a > 0.5f && fDepthBuffer[nPixelX] >= fDistanceFromPlayer) {
							bFoundScary = true;
							screen[getPosition(nPixelX, (int)(fObjectCeiling + ly))] = (Color)(c * multiplier).rgb_(255);
						}
					}
				}

			}

		}

		if (bFoundScary) {
			for (int i = 0; i < nScreenWidth * nScreenHeight; i++) {
				screen[i].r += 15;
			}
		}
		
		if (bShowMap)
			win.drawCircle(((nMapWidth)-fPlayerX)*mapDisplaySize, fPlayerY*mapDisplaySize, mapDisplaySize/2, COLOR_BLUE);

		win.drawRectangle(win.win.width-200-10, 0, 210, 60, 0, COLOR_BLACK);
		win.drawRectangle(win.win.width-200-5, 5, nHitPoints*2, 50, 0, COLOR_RED);

		win.drawBorderedText("FPS: " + std::to_string((int)(1.0f/win.win.deltaTime)), arial, win.win.width - win.getWidthOfText("FPS: " + std::to_string((int)(1.0f/win.win.deltaTime)), arial, 50), 50, 50, 1, COLOR_WHITE, COLOR_BLACK);
		win.drawBorderedText(std::to_string(nHitPoints), arial, win.win.width-200-5 + nHitPoints - win.getWidthOfText(std::to_string(nHitPoints), arial, 50)/2, -win.getWidthOfText(std::to_string(nHitPoints), arial, 50)/16, 50, 1, COLOR_WHITE, COLOR_BLACK);


		win.render();
	}


	win.del();
	closeGrey();
}