#include <grey/grey.hpp>
#include <vector>
#include "rand.h"
using std::vector;

int main() {
	initGrey(0);
	initRandom();

	Window win(1280, 720, "grey");

	win.clearColor(Color(0.2f, 0.2f, 0.2f, 1.0f));

	vector<vector<bool>> grid(12, vector<bool>(12, false));
	Vec2 player = Vec2_new(2, 2);
	Vec2 playerAnim = Vec2_new(0, 0);
	Vec2 playerReal = Vec2_new(2, 2);
	Vec2 playerOld = Vec2_new(2, 2);

	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			grid[i][j] = randBool();
		}
	}
	grid[2][2] = false;

	while (win) {
		win.update();

		if (win.isKeyPressed(KEY_UP)) {
			playerReal.y--;
		}
		if (win.isKeyPressed(KEY_DOWN)) {
			playerReal.y++;
		}
		if (win.isKeyPressed(KEY_LEFT)) {
			playerReal.x--;
		}
		if (win.isKeyPressed(KEY_RIGHT)) {
			playerReal.x++;
		}

		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid[i].size(); j++) {
				if (grid[i][j]) {
					win.drawRectangle(i * 32, j * 32, 32, 32, 0, COLOR_LIGHT_GREY);
				}
			}
		}

		if (playerReal.x > player.x) {
			player.x += (playerReal.x - player.x)/5;
		}
		if (playerReal.x < player.x) {
			player.x -= (player.x - playerReal.x)/5;
		}
		if (playerReal.y > player.y) {
			player.y += (playerReal.y - player.y)/5;
		}
		if (playerReal.y < player.y) {
			player.y -= (player.y - playerReal.y)/5;
		}
		if (abs(player.x - playerReal.x) < 0.1f && abs(player.y - playerReal.y) < 0.1f) {
			playerOld = playerReal;
			playerOld.x = playerReal.x;
			playerOld.y = playerReal.y;
		}

		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid[i].size(); j++) {
				if (grid[i][j]) {
					if (player.x*32+5+22 > i*32 && player.x*32+5 < (i+1)*32 && player.y*32+5+22 > j*32 && player.y*32+5 < (j+1)*32) {
						playerReal.x = playerOld.x;
						playerReal.y = playerOld.y;
					}
				}
			}
		}

		win.drawRectangle(player.x * 32+5, player.y * 32+5, 22, 22, 0, COLOR_RED);

		win.render();
	}

	win.del();
	closeGrey();
}