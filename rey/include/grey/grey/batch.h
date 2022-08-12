#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "mrey/mrey.h"

#ifdef __cplusplus
namespace grey {
#endif

// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. A batch of vertice data used to draw shapes.
struct Batch {
		GLuint VAO, VBO;
		floatVec triangles;
		int verticeCount, stack;
		intVec shapeVertices;
	};
	typedef struct Batch Batch;

// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Adds a vertice to a batch.
void addVertice(Batch* batch, float verts[7]);
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Adds 3 verticies at once to a batch.
void addTriangle(Batch* batch, float verts[21]);
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Finishes whatever shape you're drawing with the batch.
void endShape(Batch* batch);
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Draws all of the data inside of the batch.
void draw(Batch batch, GLenum type);
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Returns a valid batch struct.
Batch createBatch();
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Binds the batch.
void bindBatch(Batch batch);
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Flushes all current vertice data within the batch.
void flushBatch(Batch* batch);
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Deletes the whole batch and all of the memory it's taking up.
void deleteBatch(Batch* batch);

#ifdef __cplusplus
}
#endif