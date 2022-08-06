#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "mrey/mrey.h"

struct Batch {
		GLuint VAO, VBO;
		floatVec triangles;
		int verticeCount, stack;
		intVec shapeVertices;
	};
	typedef struct Batch Batch;


void addVertice(Batch* batch, float verts[7]);
void addTriangle(Batch* batch, float verts[21]);
void endShape(Batch* batch);
void draw(Batch batch, GLenum type);
Batch createBatch();
void bindBatch(Batch batch);
void flushBatch(Batch* batch);
void deleteBatch(Batch* batch);