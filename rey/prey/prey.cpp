#include "prey.h"

Vec2 cp2v2(cpVect a) {
	return Vec2_new(a.x, a.y);
}

cpVect v22cp(Vec2 a) {
	return cpv(a.x, a.y);
}

