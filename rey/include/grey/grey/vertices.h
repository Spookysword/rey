#pragma once
#include "grey/grey/color.h"
#include "mrey/mrey.h"
#ifdef _WIN32
#include <Windows.h>
#else
#define boolean unsigned int
#define TRUE 1
#define FALSE 0
#endif

#ifdef __cplusplus
namespace grey {
#endif

// A vertice struct.
typedef struct Vertice {
    float x, y, z;
    float r, g, b, a;
    float u, v;
    float nx, ny, nz;
} Vertice;

// A struct of verticies.
typedef struct Vertices {
    Vertice* vertices;
    int size;
} Vertices;

// Returns a valid vertice struct with the data passed in.
Vertice Vertice_new(float x, float y, float z, Color color, float u, float v);
// Returns a valid vertice struct with the data passed in part 2: Electric Boogaloo.
Vertice Vertice_create(Vec3 pos, Color color, Vec2 uv, Vec3 normal);

Vertices calcNormals(Vertices v);

boolean vertEqToVec(Vertice a, Vec3 b);

#ifdef __cplusplus
}
#endif