#include <grey/grey.h>
#include <vector>
#include <algorithm>
#include "rand.h"

using std::vector;

typedef unsigned int uint;

typedef enum ParticleType : int {
    BLANK = 0,
    WOOD = 1,
    SAND = 2,
    WATER = 3
} ParticleType;
#define LASTTYPE WATER

typedef struct Particle {
    ParticleType id;
    float lifetime;
    Vec2 velocity;
    Color color;
    bool updated;
} Particle;

vector<vector<Particle>> particles;

int width = 50;
int height = 40;

Particle get_p(uint x, uint y) {
    return particles[x][y];
}

void swapParticle(uint x1, uint y1, uint x2, uint y2) {
    Particle temp = get_p(x1, y1);
    particles[x1][y1] = get_p(x2, y2);
    particles[x2][y2] = temp;
}

bool isEmpty(uint x, uint y, bool isSand=false) {
    if (x > width-1 || y > height-1) return false;
    if (get_p(x, y).id == 0) return true;
    if (isSand && get_p(x, y).id == WATER) return true;
    return false;
}

void updateWater(uint x, uint y) {
    if (isEmpty(x, y+1)) {
        swapParticle(x, y, x, y+1);
    } else if (isEmpty(x-1, y+1) || isEmpty(x+1, y+1)) {
        bool r = randBool();
        if (r) {
            if (isEmpty(x-1, y+1)) {
                swapParticle(x, y, x-1, y+1);
            } else if (isEmpty(x+1, y+1)) {
                swapParticle(x, y, x+1, y+1);
            }
        } else {
            if (isEmpty(x+1, y+1)) {
                swapParticle(x, y, x+1, y+1);
            } else if (isEmpty(x-1, y+1)) {
                swapParticle(x, y, x-1, y+1);
            }
        }
    } else if (isEmpty(x-1, y) || isEmpty(x+1, y)) {
        bool r = randBool();
        if (r) {
            if (isEmpty(x - 1, y)) {
                swapParticle(x, y, x - 1, y);
            } else if (isEmpty(x + 1, y)) {
                swapParticle(x, y, x + 1, y);
            }
        } else {
            if (isEmpty(x + 1, y)) {
                swapParticle(x, y, x + 1, y);
            } else if (isEmpty(x - 1, y)) {
                swapParticle(x, y, x - 1, y);
            }
        }
    }
}


void updateSand(uint x, uint y) {
    if (isEmpty(x, y+1, true)) {
        swapParticle(x, y, x, y+1);
    } else if (isEmpty(x-1, y+1, true)) {
        swapParticle(x, y, x-1, y+1);
    } else if (isEmpty(x+1, y+1, true)) {
        swapParticle(x, y, x+1, y+1);
    }
}

void renderScreen(Window* win) {
    float x_mod = win->width / width;
    float y_mod = win->height / height;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Particle p = get_p(i, j);
            drawRectangle(win, i*x_mod, j*y_mod, x_mod, y_mod, 0, p.color);
            drawLine(win, i*x_mod, j*y_mod, i*x_mod+x_mod, j*y_mod, 1, COLOR_WHITE);
            drawLine(win, i*x_mod, j*y_mod, i*x_mod, j*y_mod+y_mod, 1, COLOR_WHITE);
        }
    }
}

void createWorld() {
    Particle p;
    p.color = COLOR_DARK_GREY;
    p.id = BLANK;
    p.velocity = Vec2_create();
    p.updated = false;
    p.lifetime = 0;

    particles = vector<vector<Particle>>(width, vector<Particle>(height, p));
}

int main() {
	initGrey(4);
    initRandom();
    float time = 0.0f;

    ParticleType currentMode = BLANK;

	Window win = createWindow(1280, 720, "Simple Particles");
   createWorld();

	while (!shouldWindowClose(win)) {
		updateWindow(&win);
        if (win.deltaTime > 0)
            time += win.deltaTime;

        if (isKeyPressed(win, KEY_UP) && currentMode < LASTTYPE) {
            currentMode = (ParticleType)(currentMode + 1);
        }
        if (isKeyPressed(win, KEY_DOWN) && currentMode > 0) {
            currentMode = (ParticleType)(currentMode - 1);
        }

        if (time >= .01) {
            if (win.mouse.isPrimaryDown) {
                int mx = win.mouse.x*width/(float)win.width;
                int my = win.mouse.y*height/(float)win.height;
                if (mx >= 0 && my >= 0 && mx < width && my < height) {
                    if (currentMode == BLANK) {
                        particles[mx][my].id = BLANK;
                        particles[mx][my].color = COLOR_DARK_GREY;
                    } else if (currentMode == SAND) {
                        particles[mx][my].id = SAND;
                        particles[mx][my].color = COLOR_YELLOW;
                    } else if (currentMode == WOOD) {
                        particles[mx][my].id = WOOD;
                        particles[mx][my].color = COLOR_BROWN;
                    } else if (currentMode == WATER) {
                        particles[mx][my].id = WATER;
                        particles[mx][my].color = COLOR_BLUE;
                    }
                }

            }

            for (uint y = height; y > 0; --y) {
                for (uint x = 0; x < width; ++x) {
                    uint id = get_p(x,y-1).id;
                    switch (id) {
                        default:
                        case BLANK:
                        case WOOD:
                            break;
                        case SAND:
                            updateSand(x, y-1);
                            break;
                        case WATER:
                            updateWater(x, y-1);
                            break;
                    }
                }
            }
            time = 0;
        }




        renderScreen(&win);

        float w = 10, h = 10;
        if (currentMode == BLANK) {
            drawRectangle(&win, 0, 0, w, h, 0, COLOR_DARK_GREY);
        } else if (currentMode == SAND) {
            drawRectangle(&win, 0, 0, w, h, 0, COLOR_YELLOW);
        } else if (currentMode == WOOD) {
            drawRectangle(&win, 0, 0, w, h, 0, COLOR_BROWN);
        } else if (currentMode == WATER) {
            drawRectangle(&win, 0, 0, w, h, 0, COLOR_BLUE);
        }


		renderWindow(win);
	}

	deleteWindow(&win);
	closeGrey();
}