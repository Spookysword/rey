#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "mrey/mrey.h"
#include "grey/grey/window_flags.h"

struct Batch3D {
		GLuint VAO, VBO, textureID;
		floatVec triangles;
		int verticeCount, stack;
		intVec shapeVertices;
	};
	typedef struct Batch3D Batch3D;

	void add3DVertice(Batch3D* batch, float verts[12]);
	void add3DTriangle(Batch3D* batch, float verts[36]);
	void end3DShape(Batch3D* batch);
	void draw3DBatch(Batch3D batch, GLenum type);
	Batch3D create3DBatch(const char* filePath, int filter);
	Batch3D createBlank3DBatch();
	void bind3DBatch(Batch3D batch);
	void flush3DBatch(Batch3D* batch);
	void delete3DBatch(Batch3D* batch);