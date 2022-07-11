#include <grey/grey.h>

#define VERT(a, b, c) Vertice_create(v##a, COLOR_WHITE, vt##b, vn0)

int main() {
	initGrey(0);

	Window win = createWindow(1280, 720, "grey");
	float sensitivity = 0.5f;
	Texture aggg = new3DTexture(&win, "resources/white.png", FILTER_LINEAR);
	float speed = 0.01f;

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
		}
		if (win.mouse.isPrimaryPressed) {
			setMousePos(&win, win.width / 2, win.height / 2);
			setMouseLocked(&win, TRUE);
		}

		//if (isKeyDown(win, KEY_RIGHT)) {
		//	win.camera.forward.x += 0.005f;
		//}
		//if (isKeyDown(win, KEY_LEFT)) {
		//	win.camera.forward.x -= 0.005f;
		//}

		//if (isKeyDown(win, KEY_UP)) {
		//	win.camera.forward.y += 0.005f;
		//	win.camera.up.y += 0.005f;
		//}
		//if (isKeyDown(win, KEY_DOWN)) {
		//	win.camera.forward.y -= 0.005f;
		//	win.camera.up.y -= 0.005f;
		//}

		win.transform.camera = win.camera;

		Vec3 v1 = Vec3_new( 1.00f, -1.00f, -1.00f);
		Vec3 v2 = Vec3_new( 1.00f, -1.00f,  1.00f);
		Vec3 v3 = Vec3_new(-1.00f, -1.00f,  1.00f);
		Vec3 v4 = Vec3_new(-1.00f, -1.00f, -1.00f);
		Vec3 v5 = Vec3_new( 1.00f,  1.00f, -0.99f);
		Vec3 v6 = Vec3_new( 0.99f,  1.00f,  1.01f);
		Vec3 v7 = Vec3_new(-1.00f,  1.00f,  1.00f);
		Vec3 v8 = Vec3_new(-1.00f,  1.00f, -1.00f);
		//14
		Vec2 vt1 = Vec2_new(1.000000f, 0.333333);
		Vec2 vt2 = Vec2_new(1.000000f, 0.666667);
		Vec2 vt3 = Vec2_new(0.666667f, 0.666667);
		Vec2 vt4 = Vec2_new(0.666667f, 0.333333);
		Vec2 vt5 = Vec2_new(0.666667f, 0.000000);
		Vec2 vt6 = Vec2_new(0.000000f, 0.333333);
		Vec2 vt7 = Vec2_new(0.000000f, 0.000000);
		Vec2 vt8 = Vec2_new(0.333333f, 0.000000);
		Vec2 vt9 = Vec2_new(0.333333f, 1.000000);
		Vec2 vt10 = Vec2_new(0.000000f, 1.000000);
		Vec2 vt11 = Vec2_new(0.000000f, 0.666667);
		Vec2 vt12 = Vec2_new(0.333333f, 0.333333);
		Vec2 vt13 = Vec2_new(0.333333f, 0.666667);
		Vec2 vt14 = Vec2_new(1.000000f, 0.000000);


		Vec3 vn0 = Vec3_new(0.0, 0.0, 0.0);

		Vertices verts;
		verts.size = 12*3;
		verts.vertices = (Vertice[12*3]){
				VERT(2,1,1), VERT(3,2,1), VERT(4,3,1),
				VERT(8,1,2), VERT(7,4,2), VERT(6,5,2),
				VERT(5,6,3), VERT(6,7,3), VERT(2,8,3),
				VERT(6,8,4), VERT(7,5,4), VERT(3,4,4),
				VERT(3,9,5), VERT(7,10,5), VERT(8,11,5),
				VERT(1,12,6), VERT(4,13,6), VERT(8,11,6),
				VERT(1,4,1), VERT(2,1,1), VERT(4,3,1),
				VERT(5,14,2), VERT(8,1,2), VERT(6,5,2),
				VERT(1,12,3), VERT(5,6,3), VERT(2,8,3),
				VERT(2,12,4), VERT(6,8,4), VERT(3,4,4),
				VERT(4,13,5), VERT(3,9,5), VERT(8,11,5),
				VERT(5,6,6), VERT(1,12,6), VERT(8,11,6)
			};

		/////////////////////////////////////////////////////////// CPP TEST \/

		//verts.vertices = (Vertice*)calloc(12 * 3, sizeof(Vertice));
		//Vertice vertst[12 * 3] = {
		//	VERT(2,1,1), VERT(3,2,1), VERT(4,3,1),
		//	VERT(8,1,2), VERT(7,4,2), VERT(6,5,2),
		//	VERT(5,6,3), VERT(6,7,3), VERT(2,8,3),
		//	VERT(6,8,4), VERT(7,5,4), VERT(3,4,4),
		//	VERT(3,9,5), VERT(7,10,5), VERT(8,11,5),
		//	VERT(1,12,6), VERT(4,13,6), VERT(8,11,6),
		//	VERT(1,4,1), VERT(2,1,1), VERT(4,3,1),
		//	VERT(5,14,2), VERT(8,1,2), VERT(6,5,2),
		//	VERT(1,12,3), VERT(5,6,3), VERT(2,8,3),
		//	VERT(2,12,4), VERT(6,8,4), VERT(3,4,4),
		//	VERT(4,13,5), VERT(3,9,5), VERT(8,11,5),
		//	VERT(5,6,6), VERT(1,12,6), VERT(8,11,6)
		//};
		//for (int i = 0; i < 12 * 3; i++) {
		//	verts.vertices[i] = vertst[i];
		//}

		/////////////////////////////////////////////////////////// CPP TEST /\

		draw3DShape(&win, aggg, verts);
		renderWindow(win);
	}

	deleteWindow(&win);
	closeGrey();
}