#include <grey/grey.hpp>
#include <mrey/mrey.h>
#include <vector>
#include <string>
#include <algorithm>
using std::vector;
using std::pair;

int scale = 5;

int nScreenWidth = 1280/scale;
int nScreenHeight = 720/scale;
int nSpotSize = 1*scale;
float nSpotBorder = 0;

float reyspeed = 0.1;

float fPlayerX = 8.0f;
float fPlayerY = 8.0f;
float fPlayerA = 0.0f;

float fFOV = 3.14159265 / 4.0f;

int nMapHeight = 16;
int nMapWidth = 16;

float fDepth = sqrt(nMapWidth*nMapWidth + nMapHeight*nMapHeight);

float mapDisplaySize = 10.0f;

int getPosition(int x, int y) {
	return x + y * nScreenWidth;
}

Vec2 getPosition(int index) {
	return Vec2_new(index % nScreenWidth, index / nScreenWidth);
}


int main() {
	initGrey(4);

	Window win(1280, 720, "ReyCasting");
	win.setFlag(WINDOW_RESIZABLE, false);

	vector<Color> screen;

	for (int i = 0; i < nScreenWidth * nScreenHeight; i++) {
		screen.push_back(COLOR_BLACK);
	}

	std::wstring map;
	map += L"################";
	map += L"#..............#";
	map += L"#....##........#";
	map += L"#....##........#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#........#######";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"################";

	while (win) {
		win.update();
		win.clearColor(COLOR_BLACK);

		if (win.isKeyDown(KEY_A)) {
			fPlayerA -= 1.0f * win.win.deltaTime;
		}
		if (win.isKeyDown(KEY_D)) {
			fPlayerA += 1.0f * win.win.deltaTime;
		}

		if (win.isKeyDown(KEY_W)) {
			fPlayerX += sinf(fPlayerA) * 5.0f * win.win.deltaTime;
			fPlayerY += cosf(fPlayerA) * 5.0f * win.win.deltaTime;

			if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#') {
				fPlayerX -= sinf(fPlayerA) * 5.0f * win.win.deltaTime;
				fPlayerY -= cosf(fPlayerA) * 5.0f * win.win.deltaTime;
			}
		}

		if (win.isKeyDown(KEY_S)) {
			fPlayerX -= sinf(fPlayerA) * 5.0f * win.win.deltaTime;
			fPlayerY -= cosf(fPlayerA) * 5.0f * win.win.deltaTime;

			if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#') {
				fPlayerX += sinf(fPlayerA) * 5.0f * win.win.deltaTime;
				fPlayerY += cosf(fPlayerA) * 5.0f * win.win.deltaTime;
			}
		}


		for (int i = 0; i < nScreenWidth * nScreenHeight; i++) {
			win.drawRectangle(Vec2_addf(Vec2_mulf(getPosition(i), nSpotSize), -nSpotBorder), Vec2_new(nSpotSize-2*nSpotBorder, nSpotSize-2*nSpotBorder), 0, screen[i]);
		}

		win.drawRectangle(0, 0, nMapWidth*mapDisplaySize, nMapHeight*mapDisplaySize, 0, COLOR_WHITE);
		for (int i = 0; i < nMapWidth; i++) {
			for (int j = 0; j < nMapHeight; j++) {
				if (map[j * nMapWidth + ((nMapWidth-1)-i)] == '#')
					win.drawRectangle(i*mapDisplaySize, j*mapDisplaySize, mapDisplaySize, mapDisplaySize, 0, COLOR_RED);
			}
		}
		
		for (int x = 0; x < nScreenWidth; x++) {
			float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)nScreenWidth) * fFOV;
			float fDistanceToWall = 0.0f;
			bool bHitWall = false;
			bool bBoundary = false;

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

						vector<pair<float, float>> p;

						for (int tx = 0; tx < 2; tx++)
							for (int ty = 0; ty < 2; ty++) {
								float vy = (float)nTestY + ty - fPlayerY;
								float vx = (float)nTestX + tx - fPlayerX;
								float d = sqrt(vx*vx + vy*vy);
								float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
								p.push_back(std::make_pair(d, dot));
							}
						
						std::sort(p.begin(), p.end(), [](const pair<float, float> &left, const pair<float, float> &right) {return left.first < right.first; });

						float fBound = 0.002;
						if (acos(p.at(0).second) < fBound) bBoundary = true;
						if (acos(p.at(1).second) < fBound) bBoundary = true;

					}
				}
			}
			if (bHitWall) {
				int nCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistanceToWall);
				int nFloor = nScreenHeight - nCeiling;
				Color shade;


				for (int y = 0; y < nScreenHeight; y++) {
					if (y < nCeiling) {
						screen[getPosition(x, y)] = COLOR_BLACK; // ceiling
					} else if (y+1 > nCeiling && y < nFloor) {
						if (bBoundary)
							shade = Color(1/(pow(fDistanceToWall, 0.8))*255/5, 0, 0, 255);
						else 
							shade = Color(1/(pow(fDistanceToWall, 0.8))*255, 0, 0, 255);
						screen[getPosition(x, y)] = shade; // wall
					} else {
						float reflection = 1/(pow(fDistanceToWall, 0.8))*255;
						float val = abs(y - nScreenHeight / 2.0f)* (255.0f/ (nScreenHeight / 2.0f));
						float color = (reflection + val) / 2;
						shade = Color(color, color, color, 255);
						screen[getPosition(x, y)] = shade; // floor
					}
				}
			}
			float xoff = fDistanceToWall * cos(fRayAngle-3.14159/2)*mapDisplaySize;
			float yoff = fDistanceToWall * sin(fRayAngle-3.14159/2)*mapDisplaySize;
			win.drawLine(((nMapWidth)-fPlayerX)*mapDisplaySize, fPlayerY*mapDisplaySize, ((nMapWidth)-fPlayerX)*mapDisplaySize-xoff, fPlayerY*mapDisplaySize-yoff, 1, COLOR_GREEN);
		}
		
		win.drawCircle(((nMapWidth)-fPlayerX)*mapDisplaySize, fPlayerY*mapDisplaySize, mapDisplaySize/2, COLOR_BLUE);

		win.render();
	}

	win.del();
	closeGrey();
}