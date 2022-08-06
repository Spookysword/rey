#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "grey/grey/batch.h"
#include "grey/grey/texture.h"
#include "grey/grey/font.h"

// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. A shader struct.
struct Shader {
    GLuint vertexID, fragmentID, shaderID;
};
typedef struct Shader Shader;
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Returns a valid shader struct.
Shader createShader(const char* vertexShader, const char* fragmentShader);

// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. A custom shader with its own batches.
struct CustomShader {
    Shader colorShader, textureShader, fontShader, texture3DShader;
    Batch shapeBatch;
    Batch lineBatch;
    textureVec textures;
    texture3DVec textures3D;
    fontVec fonts;
};
typedef struct CustomShader CustomShader;

// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. A vector of custom shaders.
struct CustomShaderVec {
    CustomShader* data;
    int size;
    int limit;
};
typedef struct CustomShaderVec CustomShaderVec;
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Returns a valid custom shader vector.
CustomShaderVec CustomShaderVecCreate();
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Checks if the size of the custom shader vector is overflowing and acts accordingly.
void CustomShaderVecCheckSize(CustomShaderVec* vec);
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Pushesback a custom shader into the custom shader vector.
void CustomShaderVecPushBack(CustomShaderVec* vec, CustomShader num);
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Clears all custom shaders in the custom shader vector.
void CustomShaderVecClear(CustomShaderVec* vec);
// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Frees up all the memory the custom shader vector is using.
void CustomShaderVecDelete(CustomShaderVec* vec);