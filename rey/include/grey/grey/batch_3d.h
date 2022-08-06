#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "mrey/mrey.h"
#include "grey/grey/window_flags.h"

// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. A 3D batch of vertice data used to draw 3D shapes.
struct Batch3D {
		GLuint VAO, VBO, textureID;
		floatVec triangles;
		int verticeCount, stack;
		intVec shapeVertices;
	};
	typedef struct Batch3D Batch3D;

	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Adds a 3D vertice to a 3D batch.
	void add3DVertice(Batch3D* batch, float verts[12]);
	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Adds 3 3Dverticies at once to a 3D batch.
	void add3DTriangle(Batch3D* batch, float verts[36]);
	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Finishes whatever 3D shape you're drawing with the 3D batch.
	void end3DShape(Batch3D* batch);
	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Draws all of the 3D data inside of the 3D batch.
	void draw3DBatch(Batch3D batch, GLenum type);
	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Returns a valid 3D batch struct with the file specified.
	Batch3D create3DBatch(const char* filePath, int filter);
	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Returns a valid and empty 3D batch struct.
	Batch3D createBlank3DBatch();
	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Binds the 3D batch.
	void bind3DBatch(Batch3D batch);
	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Flushes all current 3D vertice data within the 3D batch.
	void flush3DBatch(Batch3D* batch);
	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Deletes the whole 3D batch and all of the memory it's taking up.
	void delete3DBatch(Batch3D* batch);