#include "grey/grey/vertices.h"

Vertice Vertice_new(float x, float y, float z, Color color, float u, float v) {
	Vertice o;
	o.x = x;
	o.y = -y;
	o.z = z;
	o.r = (float)color[0] / 255.0f;
	o.g = (float)color[1] / 255.0f;
	o.b = (float)color[2] / 255.0f;
	o.a = (float)color[3] / 255.0f;
	o.u = u;
	o.v = v;
	o.nx = 0;
	o.ny = 0;
	o.nz = 0;
	return o;
}

Vertice Vertice_create(Vec3 pos, Color color, Vec2 uv, Vec3 normal) {
	Vertice o;
	o.x = pos.x;
	o.y = pos.y;
	o.z = pos.z;
	o.r = (float)color[0] / 255.0f;
	o.g = (float)color[1] / 255.0f;
	o.b = (float)color[2] / 255.0f;
	o.a = (float)color[3] / 255.0f;
	o.u = uv.x;
	o.v = uv.y;
	o.nx = normal.x;
	o.ny = normal.y;
	o.nz = normal.z;
	return o;
}

boolean vertEqToVec(Vertice a, Vec3 b) {
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

Vertices calcNormals(Vertices v) {
	Vertices o;
	o.size = v.size;
	o.vertices = (Vertice*)calloc(v.size, sizeof(Vertice));
	for (int i = 0; i < v.size; i++) {
		o.vertices[i] = v.vertices[i];
	}

	for (int i = 0; i < o.size; i += 3) {
		Vertice va = o.vertices[i];
		Vertice vb = o.vertices[i + 1];
		Vertice vc = o.vertices[i + 2];
		Vec3 a = Vec3_new(va.x, va.y, va.z);
		Vec3 b = Vec3_new(vb.x, vb.y, vb.z);
		Vec3 c = Vec3_new(vc.x, vc.y, vc.z);

		Vec3 p = Vec3_cross(Vec3_sub(b, a), Vec3_sub(c, a));

		for (int j = 0; j < o.size; j++) {
			if (vertEqToVec(o.vertices[j], a) || vertEqToVec(o.vertices[j], b) || vertEqToVec(o.vertices[j], c)) {
				o.vertices[j].nx += p.x;
				o.vertices[j].ny += p.y;
				o.vertices[j].nz += p.z;
			}
		}
	}

	for (int j = 0; j < o.size; j++) {
		Vec3 normal = Vec3_normalize(Vec3_new(o.vertices[j].nx, o.vertices[j].ny, o.vertices[j].nz));
		o.vertices[j].nx = normal.x;
		o.vertices[j].ny = normal.y;
		o.vertices[j].nz = normal.z;
	}

	return o;
}