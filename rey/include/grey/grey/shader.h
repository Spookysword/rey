#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "grey/grey/batch.h"
#include "grey/grey/texture.h"
#include "grey/grey/font.h"

struct Shader {
    GLuint vertexID, fragmentID, shaderID;
};
typedef struct Shader Shader;
Shader createShader(const char* vertexShader, const char* fragmentShader);

struct CustomShader {
    Shader colorShader, textureShader, fontShader, texture3DShader;
    Batch shapeBatch;
    Batch lineBatch;
    textureVec textures;
    texture3DVec textures3D;
    fontVec fonts;
};
typedef struct CustomShader CustomShader;

struct CustomShaderVec {
    CustomShader* data;
    int size;
    int limit;
};
typedef struct CustomShaderVec CustomShaderVec;
CustomShaderVec CustomShaderVecCreate();
void CustomShaderVecCheckSize(CustomShaderVec* vec);
void CustomShaderVecPushBack(CustomShaderVec* vec, CustomShader num);
void CustomShaderVecClear(CustomShaderVec* vec);
void CustomShaderVecDelete(CustomShaderVec* vec);