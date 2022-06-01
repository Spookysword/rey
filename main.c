#include <grey.h>
#include <stdio.h>

int main() {
	initGrey(4);

	Window win = createWindow(720, 720, "grey");

	srand(NULL);

	int amtX = 10;
	int amtY = 10;
	float time = 0.0f;
	int frames = 0;

	while (!shouldWindowClose(win)) {
		float updateTime = glfwGetTime();
		updateWindow(&win);
		updateTime = glfwGetTime() - updateTime;
		
		clearWindowBackground(win, COLOR_DISCORD);

		time += win.deltaTime;
		frames += 1;
		if (time >= 1.0f) {
			time = 0.0f;
			printf("%i\n", frames);
			frames = 0;
		}

		if (isKeyDown(win, KEY_ESCAPE)) {
			closeWindow(win);
		}


		if (isKeyPressed(win, KEY_F11)) {
			win.fullscreen = !win.fullscreen;
		}

		if (isKeyDown(win, KEY_SPACE)) {
			setWireframeMode(win, TRUE);
		}
		else {
			setWireframeMode(win, FALSE);
		}

		if (isKeyPressed(win, KEY_G)) {
			printf("powered by grey\n");
		}

		float drawCallTime = glfwGetTime();
		for (int i = 0; i < amtX+1; i++) {
			for (int z = 0; z < amtY+1; z++) {
				drawRectangle(&win, (win.width/amtX)*i, (win.height/amtY)*z, win.width/amtX, win.height/amtY, (Color){ rand()%255+1, rand()%255+1, rand()%255+1, 255 });
			}
		}
		drawCallTime = glfwGetTime() - drawCallTime;
		
		float renderTime = glfwGetTime();
		renderWindow(win);
		renderTime = glfwGetTime() - renderTime;

		//if (updateTime > drawCallTime && updateTime > renderTime) { printf("Update time took the longest\n"); }
		//else if (drawCallTime > updateTime && drawCallTime > renderTime) { printf("Draw call time took the longest\n"); }
		//else if (renderTime > drawCallTime && renderTime > updateTime) { printf("Render time took the longest\n"); }
	}
	
	deleteWindow(&win);
	closeGrey();
	return 0;
}