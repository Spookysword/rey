#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "mrey/mrey.h"
#include <stb_image.h>
#ifdef __cplusplus
namespace grey {
#endif
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. A struct that handles the batch rendering of a particular texture.
struct TextureBatch {
    GLuint VAO, VBO, textureID;
    floatVec triangles;
    int verticeCount, stack;
    intVec shapeVertices;
};
typedef struct TextureBatch TextureBatch;

// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Adds a vertice to a texture batch.
void addTextureVertice(TextureBatch* batch, float verts[9]);
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Adds 3 vertices simultaneously to a texture batch.
void addTextureTriangle(TextureBatch* batch, float verts[27]);
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Finishes whatever shape you're drawing with this texture batch.
void endTextureShape(TextureBatch* batch);
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Renders the entire texture batch as is.
void drawTextureBatch(TextureBatch batch, GLenum type);
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Returns a valid texture batch struct.
TextureBatch createTextureBatch(const char* filePath, int filter);
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Binds the specified texture batch.
void bindTextureBatch(TextureBatch batch);
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Flushes all texture batch data, specifically verticies.
void flushTextureBatch(TextureBatch* batch);
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Deletes all memory this texture batch is taking up.
void deleteTextureBatch(TextureBatch* batch);
#ifdef __cplusplus
}
#endif