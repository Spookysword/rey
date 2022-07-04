#include <grey/grey.h>

int main() {
	initGrey(0);

	Window win = createWindow(1280, 720, "grey");
	float sensitivity = 0.5f;
	Texture aggg = newTexture(&win, "resources/block.png", FILTER_LINEAR);
	float speed = 0.001f;

	while (!shouldWindowClose(win)) {
		updateWindow(&win);

		//printMat4(Transform_getProjectedTranformation(win.transform));

		if (isKeyDown(win, KEY_W)) {
			win.camera = Camera_move(win.camera, win.camera.forward, speed);
		}
		if (isKeyDown(win, KEY_S)) {
			win.camera = Camera_move(win.camera, win.camera.forward, -speed);
		}
		if (isKeyDown(win, KEY_A)) {
			win.camera = Camera_move(win.camera, Camera_left(win.camera), speed);
		}
		if (isKeyDown(win, KEY_D)) {
			win.camera = Camera_move(win.camera, Camera_right(win.camera), speed);
		}
		if (isKeyDown(win, KEY_SPACE)) {
			win.camera = Camera_move(win.camera, win.camera.up, speed);
		}
		if (isKeyDown(win, KEY_LEFT_SHIFT)) {
			win.camera = Camera_move(win.camera, win.camera.up, -speed);
		}


		if (isKeyPressed(win, KEY_DOWN)) {
			speed -= 0.001f;
		}
		if (isKeyPressed(win, KEY_UP)) {
			speed += 0.001f;
		}

		if (isKeyPressed(win, KEY_ESCAPE)) {
			setMouseLocked(&win, FALSE);
		}
		if (win.mouse.isPrimaryPressed) {
			setMousePos(&win, win.width / 2, win.height / 2);
			setMouseLocked(&win, TRUE);
		}

		win.transform.camera = win.camera;

		Vertice a = Vertice_new(-1.0f, -1.0f, 0.5773f, COLOR_RED); // 0
		Vertice b = Vertice_new(0.0f, -1.0f, -1.15475f, COLOR_RED); // 1
		Vertice c = Vertice_new(1.0f, -1.0f, 0.5773f, COLOR_RED); // 2
		Vertice d = Vertice_new(0.0f, 1.0f, 0.0f, COLOR_RED); // 3


		Vertices verts;
		verts.size = 12;
		verts.vertices = (Vertice[12]){ a, d, b,
										b, d, c,
										c, d, a,
										b, c, a};

		drawTexture(&win, aggg, 0, 0, 100, 100, 0, COLOR_WHITE);
		draw3DShape(&win, verts);
		renderWindow(win);
	}

	deleteWindow(&win);
	closeGrey();
}