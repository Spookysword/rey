#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "mrey/mrey.h"
#include <stb_image.h>


struct TextureBatch {
    GLuint VAO, VBO, textureID;
    floatVec triangles;
    int verticeCount, stack;
    intVec shapeVertices;
};
typedef struct TextureBatch TextureBatch;

void addTextureVertice(TextureBatch* batch, float verts[9]);
void addTextureTriangle(TextureBatch* batch, float verts[27]);
void endTextureShape(TextureBatch* batch);
void drawTextureBatch(TextureBatch batch, GLenum type);
TextureBatch createTextureBatch(const char* filePath, int filter);
void bindTextureBatch(TextureBatch batch);
void flushTextureBatch(TextureBatch* batch);
void deleteTextureBatch(TextureBatch* batch);