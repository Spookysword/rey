#include <grey/grey.hpp>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "rand.h"
using std::vector;

void create_maze(vector<vector<bool>> &maze, int x, int y) {
	maze[x][y] = false;
	vector<vector<int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	std::shuffle(dirs.begin(), dirs.end(), gen);
	for (int i = 0; i < 4; i++) {
		int nx = x + dirs[i][0]*2;
		int ny = y + dirs[i][1]*2;
		if (0 <= nx && nx < maze.size() && 0 <= ny && ny < maze[0].size() && maze[nx][ny]) {
			int lx = x + dirs[i][0];
			int ly = y + dirs[i][1];
			maze[lx][ly] = false;
		
			create_maze(maze, nx, ny);
		}
	}
}

bool aabb(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
	return x1 < x2 + w2 && x2 < x1 + w1 && y1 < y2 + w2 && y2 < y1 + w1;
}

int main() {
	std::srand ( unsigned ( std::time(0) ) );
	initGrey(0);
	initRandom();

	Window win(1280, 720, "grey");
	
	int gridsize = 10;
	int playeroff = 2;
	float speed = 0.5f;

	int mazesizex = floor(win.win.width/gridsize);
	int mazesizey = floor(win.win.height/gridsize);
	win.clearColor(Color(0.2f, 0.2f, 0.2f, 1.0f));

	vector<vector<bool>> grid(mazesizex, vector<bool>(mazesizey, false));
	Vec2 player = Vec2_new(1, 1);

	
	for (int i = 0; i < mazesizex; i++) {
		for (int j = 0; j < mazesizey; j++) {
			grid[i][j] = true;
		}
	}
	create_maze(grid, 1, 1);
	bool canMoveD = true, canMoveU = true, canMoveL = true, canMoveR = true;

	while (win) {
		win.update();
		canMoveD = true; canMoveU = true; canMoveL = true; canMoveR = true;
		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid[i].size(); j++) {
				if (grid[i][j]) {
					if (aabb(player.x*gridsize+playeroff, (player.y-speed)*gridsize+playeroff, gridsize-(playeroff*2), gridsize-(playeroff*2), i*gridsize, j*gridsize, gridsize, gridsize)) {
						canMoveU = false;
					}
					if (aabb(player.x*gridsize+playeroff, (player.y+speed)*gridsize+playeroff, gridsize-(playeroff*2), gridsize-(playeroff*2), i*gridsize, j*gridsize, gridsize, gridsize)) {
						canMoveD = false;
					}
					if (aabb((player.x-speed)*gridsize+playeroff, player.y*gridsize+playeroff, gridsize-(playeroff*2), gridsize-(playeroff*2), i*gridsize, j*gridsize, gridsize, gridsize)) {
						canMoveL = false;
					}
					if (aabb((player.x+speed)*gridsize+playeroff, player.y*gridsize+playeroff, gridsize-(playeroff*2), gridsize-(playeroff*2), i*gridsize, j*gridsize, gridsize, gridsize)) {
						canMoveR = false;
					}
				}
			}
		}

		if (win.isKeyDown(KEY_UP) && canMoveU) {
			player.y -= speed;
		}
		if (win.isKeyDown(KEY_DOWN) && canMoveD) {
			player.y += speed;
		}
		if (win.isKeyDown(KEY_LEFT) && canMoveL) {
			player.x -= speed;
		}
		if (win.isKeyDown(KEY_RIGHT) && canMoveR) {
			player.x += speed;
		}

		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid[i].size(); j++) {
				if (grid[i][j]) {
					win.drawRectangle(i * gridsize, j * gridsize, gridsize, gridsize, 0, COLOR_LIGHT_GREY);
				}
			}
		}

		win.drawRectangle(player.x * gridsize+playeroff, player.y * gridsize+playeroff, gridsize-(playeroff*2), gridsize-(playeroff*2), 0, COLOR_RED);

		win.render();
	}

	win.del();
	closeGrey();
}