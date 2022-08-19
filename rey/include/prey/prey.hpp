#ifndef PREY_H
#define PREY_H

#include <mrey/mrey.h>
#include <chipmunk/chipmunk.h>
#include <stdio.h>
#include <grey/grey.h>
#include <vector>
#include <chipmunk/chipmunk_structs.h>

using std::vector;


Vec2 cp2v2(cpVect a);

cpVect v22cp(Vec2 a);

enum PhysicsType {
	DYNAMIC = 0,
	STATIC = 1
};

class PhysicsObject {
public:
	cpBody* body;
	cpShape* shape;
	virtual void render(Window* win) = 0;
	Color color;
	PhysicsType type;

	float getX() { return cpBodyGetPosition(body).x; }
	float getY() { return cpBodyGetPosition(body).y; }
	void setVelocity(float x, float y) { cpBodySetVelocity(body, cpv(x, y)); }
	void setForce(float x, float y) { cpBodySetForce(body, cpv(x, y)); }
	Vec2 getVelocity() { return cp2v2(cpBodyGetVelocity(body)); }
	Vec2 getForce() { return cp2v2(cpBodyGetForce(body)); }
	void addVelocity(float x, float y) { setVelocity(getVelocity().x + x, getVelocity().y + y); }
	void addForce(float x, float y) { setForce(getForce().x + x, getForce().y + y); }

	float getMass() { return cpShapeGetMass(shape); }
	float getAngle() { return cpBodyGetAngle(body); }

	void setAngularVelocity(float v) { cpBodySetAngularVelocity(body, v); }
	float getAngularVelocity() { return cpBodyGetAngularVelocity(body); }

	void addAngularVelocity(float v) { setAngularVelocity(getAngularVelocity()+v);  }

	void setFriction(float f) { cpShapeSetFriction(shape, f); }
	void setElasticity(float f) { cpShapeSetElasticity(shape, f); }

	bool intersectsPoint(float x, float y) {
		cpBB bb = cpShapeGetBB(shape);
		return (x > bb.l && x < bb.r&& y < bb.t&& y > bb.b);
	}

};

class CircleObject : public PhysicsObject {
public:
	float r;
	CircleObject(cpSpace* space, float x, float y, float r, Color color, PhysicsType type, float mass) {
		this->r = r;
		this->type = type;
		setColor(&this->color, color);
		if (type == STATIC) {
			//body = cpSpaceGetStaticBody(space);
			body = cpBodyNew(INFINITY, cpMomentForCircle(INFINITY, 0, r, cpvzero));
			cpBodySetPosition(body, cpv(x, y));
		}
		else if (type == DYNAMIC) {
			body = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForCircle(mass, 0, r, cpvzero)));
			cpBodySetPosition(body, cpv(x, y));
		}
		shape = cpSpaceAddShape(space, cpCircleShapeNew(body, r, cpvzero));
	}
	void render(Window* win) {
		drawCircle(win, getX(), getY(), r, color);
	}
};

class SegmentObject : public PhysicsObject {
public:
	float x1, y1, x2, y2, thickness;
	SegmentObject(cpSpace* space, float x1, float y1, float x2, float y2, float thickness, Color color, PhysicsType type, float mass) {
		setColor(&this->color, color);
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
		this->type = type;
		this->thickness = thickness;
		if (type == STATIC) {
			//body = cpSpaceGetStaticBody(space);
			body = cpBodyNew(INFINITY, cpMomentForSegment(INFINITY, cpv(x1, y1), cpv(x2, y2), thickness / 2));
		}
		else if (type == DYNAMIC) {
			body = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForSegment(mass, cpv(x1, y1), cpv(x2, y2), thickness/2)));
		}
		shape = cpSpaceAddShape(space, cpSegmentShapeNew(body, cpv(x1, y1), cpv(x2, y2), thickness/2));
	}
	void render(Window* win) {
		drawLine(win, x1+getX(), y1 + getY(), x2 + getX(), y2 + getY(), thickness, color);
	}
};

class BoxObject : public PhysicsObject {
public:
	float w, h, firstx, firsty;
	BoxObject(cpSpace* space, float x, float y, float w, float h, Color color, PhysicsType type, float mass) {
		setColor(&this->color, color);
		firstx = x;
		firsty = y;
		this->w = w;
		this->h = h;
		this->type = type;
		if (type == STATIC) {
			//body = cpSpaceGetStaticBody(space);
			body = cpBodyNew(INFINITY, cpMomentForBox(INFINITY, w, h));
			cpBodySetPosition(body, cpv(x, y));
		}
		else if (type == DYNAMIC) {
			body = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForBox(mass, w, h)));
			cpBodySetPosition(body, cpv(x, y));
		}
		shape = cpSpaceAddShape(space, cpBoxShapeNew(body, w, h, 1));
	}
	void render(Window* win) {
		if (type == DYNAMIC) {
			drawRectangle(win, getX() - w / 2, getY() - w / 2, w, h, toDegrees(getAngle()), color);
		}
		if (type == STATIC) {
			drawRectangle(win, firstx - w / 2, firsty - h / 2, w, h, toDegrees(getAngle()), color);
		}
	}
};


class PhysicsWorld {
public:
	Vec2 gravity;
	vector<PhysicsObject*> objects;
	cpSpace* space = cpSpaceNew();
	PhysicsWorld(float x, float y) {
		gravity = Vec2_new(x, y);
		cpSpaceSetCollisionSlop(space, 1);
		cpSpaceSetCollisionBias(space, 0.01);
		cpSpaceSetGravity(space, cpv(x, y));
	}

	void addCollisionFunc(cpCollisionBeginFunc func) {
		cpCollisionHandler* handler = cpSpaceAddCollisionHandler(space, NULL, NULL);
		handler->beginFunc = func;
	}

	CircleObject* createCircle(float x, float y, float r, Color color, PhysicsType type, float mass=1) {
		CircleObject* obj = new CircleObject(space, x, y, r, color, type, mass);
		obj->setFriction(0.9f);
		objects.push_back(obj);
		return obj;
	}
	SegmentObject* createSegment(float x1, float y1, float x2, float y2, float thickness, Color color, PhysicsType type, float mass=1) {
		SegmentObject* obj = new SegmentObject(space, x1, y1, x2, y2, thickness, color, type, mass);
		obj->setFriction(0.9f);
		objects.push_back(obj);
		return obj;
	}

	BoxObject* createBox(float x, float y, float w, float h, Color color, PhysicsType type, float mass = 1) {
		BoxObject* obj = new BoxObject(space, x, y, w, h, color, type, mass);
		obj->setFriction(0.9f);
		objects.push_back(obj);
		return obj;
	}

	void update(Window win) {
		cpSpaceStep(space, win.deltaTime);
	}

	void render(Window* win, bool drawVelocity=false) {
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->render(win);
			if (drawVelocity && objects[i]->type == DYNAMIC) {
				Vec2 v = objects[i]->getVelocity();
				v.x = v.x /10;
				v.y = v.y /10;
				drawLine(win, objects[i]->getX(), objects[i]->getY(), objects[i]->getX() + v.x, objects[i]->getY() + v.y, 2, COLOR_GREEN);
			
				if (dynamic_cast<CircleObject*>(objects[i]) != nullptr) {
					CircleObject* obj = (CircleObject*)objects[i];
					float angle = obj->getAngle();
					float xp = cos(angle);
					float yp = sin(angle);
					drawLine(win, obj->getX(), obj->getY(), obj->getX() + obj->r * xp, obj->getY() + obj->r * yp, 2, COLOR_RED);
				}
				if (dynamic_cast<BoxObject*>(objects[i]) != nullptr) {
					BoxObject* obj = (BoxObject*)objects[i];
					float angle = obj->getAngle();
					float xp = cos(angle);
					float yp = sin(angle);
					drawLine(win, obj->getX(), obj->getY(), obj->getX() + obj->w / 2 * xp, obj->getY() + obj->h / 2 * yp, 2, COLOR_RED);
				}
			}
		}
	}

};

#endif