#include "prey.h"
#include <stdlib.h>

_Bool preyInit = 0;
int rectLimit = 1000;

int C_AABB(C_Rectangles a, C_Rectangles b) {
	float x1 = a.x, x2 = b.x;
	float y1 = a.y, y2 = b.y;
	int w1 = a.w, w2 = b.w;
	int h1 = a.h, h2 = b.h;

	if (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2) return 1;
	return 0;
}

////////////////////////////
//// Physics Rectangles ////
////////////////////////////

C_PhysicsRect C_createPhysicsRect(const char* type, float x, float y, float w, float h, float density, float rotation) {
	if (type == NULL) {
		type = "static";
	}
	C_PhysicsRect a;
	a.type = type;
	a.rect.x = x;
	a.rect.y = y;
	a.rect.w = (int)w;
	a.rect.h = (int)h;
	a.density = density;
	a.rotation = rotation;
	a.velocityX = 0.0f;
	a.velocityY = 0.0f;
	return a;
}
int C_isRectCollidingWithRect(C_PhysicsRect a, C_PhysicsRect b) {
	return C_AABB(a.rect, b.rect);
}
void C_applyForce(C_PhysicsRect *a, float forceX, float forceY) {
	a->velocityX += forceX;
	a->velocityY += forceY;
}

///////////////////////
//// Physics World ////
///////////////////////

C_PhysicsWorld C_createPhysicsWorld() {
	C_PhysicsWorld world;
	world.gravityX = 0.0f;
	world.gravityY = 9.81f;
	world.doCollisionResponse = 1;
	world.i = 0;
	world.rects = (C_PhysicsRect*)malloc(sizeof(C_PhysicsRect) * rectLimit);
	return world;
	
}
C_PhysicsRectID C_newRect(C_PhysicsWorld* world, const char* type, float x, float y, float w, float h, float density, float rotation) {
	world->rects[world->i] = C_createPhysicsRect(type, x, y, w, h, density, rotation);
	world->i += 1;
	return world->i - 1;
}

void C_updatePhysicsWorld(C_PhysicsWorld* world, float deltaTime) {
	for (int i = 0; i < world->i; i++) {
		world->rects[i].velocityX += (world->gravityX * deltaTime) * world->rects[i].density;
		world->rects[i].rect.x += world->rects[i].velocityX;
		world->rects[i].velocityY += (world->gravityY * deltaTime) * world->rects[i].density;
		world->rects[i].rect.y += world->rects[i].velocityY;

		if (world->doCollisionResponse && i > 0) {
			if (C_isRectCollidingWithRect(world->rects[i], world->rects[i - 1])) {
				float x1 = world->rects[i].rect.x, y1 = world->rects[i].rect.y;
				float x2 = world->rects[i - 1].rect.x, y2 = world->rects[i - 1].rect.y;
				int w1 = world->rects[i].rect.w, h1 = world->rects[i].rect.h;
				int w2 = world->rects[i - 1].rect.w, h2 = world->rects[i - 1].rect.h;
				float d1 = world->rects[i].density, d2 = world->rects[i - 1].density;

				float ax1 = x1, ax2 = x2, ay1 = y1, ay2 = y2;

				if (y1 < y2 && y1 + h1 > y2 && !(x1 > x2+w2) && !(x1 + w1 < x2) ) {
					// When they collide, the top and bottom should bounce back, the amount that they both bounce back is equal to (y1+h1)-y2
					// Depending on the density, the top or bottom might bounce more than the other, but they still need to bounce the same amount
					float ratio = d1 + d2;
					float m1 = d1 / ratio;
					float m2 = d2 / ratio;


					ay1 -= ((y1 + h1) - y2) * m1;
					ay2 += ((y1 + h1) - y2) * m2;
				}

				if (y2 < y1 && y2 + h2 > y1 && !(x2 > x1 + w1) && !(x2 + w2 < x1)) {
					float ratio = d1 + d2;
					float m1 = d1 / ratio;
					float m2 = d2 / ratio;

					ay2 -= ((y2 + h2) - y1) *m1;
					ay1 += ((y2 + h2) - y1) *m2;
				}
				world->rects[i].rect.x = ax1;
				world->rects[i].rect.y = ay1;
				world->rects[i - 1].rect.x = ax2;
				world->rects[i - 1].rect.y = ay2;



			}
		}
	}
}
void C_deletePhysicsWorld(C_PhysicsWorld* world) {
	free(world->rects);
}

void C_initPrey(int _rectLimit) {
	preyInit = 1;
	rectLimit = _rectLimit;
	if (_rectLimit == 0) rectLimit = 1000;
}
void C_closePrey() { preyInit = 0; }