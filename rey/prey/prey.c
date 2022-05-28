#include "prey"

_Bool preyInit = 0;
int rectLimit = 1000;

int AABB(Rectangles a, Rectangles b) {
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

PhysicsRect createPhysicsRect(const char* type, float x, float y, float w, float h, float density, float rotation) {
	if (type == NULL) {
		type = "static";
	}
	PhysicsRect a;
	a.type = type;
	a.rect.x = x;
	a.rect.y = y;
	a.rect.w = w;
	a.rect.h = h;
	a.density = density;
	a.rotation = rotation;
	a.velocityX = 0.0f;
	a.velocityY = 0.0f;
	return a;
}
int isRectCollidingWithRect(PhysicsRect a, PhysicsRect b) {
	return AABB(a.rect, b.rect);
}
void applyForce(PhysicsRect *a, float forceX, float forceY) {
	a->velocityX += forceX;
	a->velocityY += forceY;
}

///////////////////////
//// Physics World ////
///////////////////////

PhysicsWorld createPhysicsWorld() {
	PhysicsWorld world;
	world.gravityX = 0.0f;
	world.gravityY = 9.81f;

	world.i = 0;
	world.rects = (PhysicsRect*)malloc(sizeof(PhysicsRect) * rectLimit);
	return world;
	
}
PhysicsRectID newRect(PhysicsWorld* world, const char* type, float x, float y, float w, float h, float density, float rotation) {
	world->rects[world->i] = createPhysicsRect(type, x, y, w, h, density, rotation);
	world->i += 1;
	return world->i - 1;
}

void updatePhysicsWorld(PhysicsWorld* world, float deltaTime) {
	for (int i = 0; i < world->i; i++) {
		world->rects[i].velocityX += (world->gravityX * deltaTime) * world->rects[i].density;
		world->rects[i].rect.x += world->rects[i].velocityX;
		world->rects[i].velocityY += (world->gravityY * deltaTime) * world->rects[i].density;
		world->rects[i].rect.y += world->rects[i].velocityY;
	}
}


void initPrey(int _rectLimit) { 
	preyInit = 1;
	rectLimit = _rectLimit;
	if (_rectLimit == NULL) rectLimit = 1000;
}
void closePrey() { preyInit = 0; }
