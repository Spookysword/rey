#include <grey/grey.h>
#include <grey/grey/obj.hpp>

int main() {
	initGrey(0);

	Window win = createWindow(1280, 720, "grey");
	float sensitivity = 50.0f;
	Texture aggg = new3DTexture(&win, "resources/white.png", FILTER_LINEAR);
	float speed = 0.01f;
    bool locked = false;

	while (!shouldWindowClose(win)) {
		updateWindow(&win);

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

		if (isKeyPressed(win, KEY_ESCAPE)) {
			setMouseLocked(&win, FALSE);
            locked = false;
		}
		if (win.mouse.isPrimaryPressed) {
			setMousePos(&win, win.width / 2, win.height / 2);
			setMouseLocked(&win, TRUE);
            locked = true;
		}
        if (locked) {
            double dx = win.mouse.x - win.width / 2;
            double dy = win.mouse.y - win.height / 2;

            bool rotY = dx != 0;
            bool rotX = dy != 0;

            if (rotY) {
                win.camera = Camera_rotateY(win.camera, dx * sensitivity/win.width);
            }
            if (rotX) {
                win.camera = Camera_rotateX(win.camera, dy * sensitivity/win.height);
            }
            if (rotX || rotY) 
                setMousePos(&win, win.width / 2, win.height / 2);
        }

		win.transform.camera = win.camera;

		draw3DShape(&win, aggg, loadObj("resources/cube.obj"));
		renderWindow(win);
	}

	deleteWindow(&win);
	closeGrey();
}