#ifndef PREY_H
#define PREY_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>
#include <xkeycheck.h>
#include <memory.h>

// An easier way to define structs.
#define STRUCT(a) ; typedef struct a a

// A refrence to a Physics Rectangle (WORLD.rects[ID] returns the actual physics rectangle).
typedef unsigned int C_PhysicsRectID;

// A rectangle struct to hold x, y, w, h.
struct C_Rectangles {
	int w;
	int h;
	float x;
	float y;
} STRUCT(C_Rectangles);

// Holds all of the physical data about a rectangle.
struct C_PhysicsRect {
	const char* type;
	C_Rectangles rect;
	float density, rotation;
	float velocityX, velocityY;
} STRUCT(C_PhysicsRect);

// Holds all of the physics retangles, and applies physics to them.
struct C_PhysicsWorld {
	float gravityX, gravityY;
	C_PhysicsRect *rects;
	unsigned int doCollisionResponse;
	int i;
} STRUCT(C_PhysicsWorld);

// A function to calculate AABB collision on 2 Rectangles.
int C_AABB(C_Rectangles a, C_Rectangles b);
// A function to create a physics rectangle.
C_PhysicsRect C_createPhysicsRect(const char* type, float x, float y, float w, float h, float density, float rotation);
// To check if 2 physics rects are colliding.
int C_isRectCollidingWithRect(C_PhysicsRect a, C_PhysicsRect b);
// Applies force to a physics rectangle.
void C_applyForce(C_PhysicsRect *a, float forceX, float forceY);
// Creates a physics world.
C_PhysicsWorld C_createPhysicsWorld();
// Adds a new rectangle to the world.
C_PhysicsRectID C_newRect(C_PhysicsWorld* world, const char* type, float x, float y, float w, float h, float density, float rotation);
// Will perform physical calcualtions of all of the rectangles in the physics world.
void C_updatePhysicsWorld(C_PhysicsWorld* world, float deltaTime);
// Initializes the prey module
void C_initPrey(int _rectLimit);
// De-initializes the prey module
void C_closePrey();
void C_deletePhysicsWorld(C_PhysicsWorld* world);

#ifndef IMPLEMENT_PREY_H
#define PhysicsRectID C_PhysicsRectID
#define Rectangles C_Rectangles
#define PhysicsRect C_PhysicsRect
#define PhysicsWorld C_PhysicsWorld
#define AABB C_AABB
#define createPhysicsRect C_createPhysicsRect
#define isRectCollidingWithRect C_isRectCollidingWithRect
#define applyForce C_applyForce
#define createPhysicsWorld C_createPhysicsWorld
#define newRect C_newRect
#define updatePhysicsWorld C_updatePhysicsWorld
#define initPrey C_initPrey
#define closePrey C_closePrey
#define deletePhysicsWorld C_deletePhysicsWorld

#endif
#ifdef __cplusplus
}
#endif
#endif