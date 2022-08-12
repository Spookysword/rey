#include "grey/grey/texture.h"
#ifdef __cplusplus
namespace grey {
#endif
textureVec textureVecCreate() {
	textureVec vec;
	vec.data = (TextureBatch*)calloc(0, sizeof(TextureBatch));
	vec.size = 0;
	vec.limit = 0;
	return vec;
}
void textureVecCheckSize(textureVec* vec) {
	if (vec->size + 1 > vec->limit) {
		TextureBatch* temp;
		vec->limit = vec->size * 2;
		temp = (TextureBatch*)realloc(vec->data, vec->limit * sizeof(TextureBatch));
		if (temp) { vec->data = temp; }
	}
}
void textureVecPushBack(textureVec* vec, TextureBatch num) {
	vec->size += 1;
	textureVecCheckSize(vec);
	vec->data[vec->size - 1] = num;
}
void textureVecClear(textureVec* vec) {
	free(vec->data);
	vec->limit /= 2;
	vec->data = (TextureBatch*)calloc(vec->limit, sizeof(TextureBatch));
	vec->size = 0;
}
void textureVecDelete(textureVec* vec) {
	for (int i = 0; i < vec->size; i++) {
		deleteTextureBatch(&vec->data[i - 1]);
		glDeleteTextures(1, &vec->data[i - 1].textureID);
	}
	free(vec->data);
	vec->size = 0;
	vec->limit = 0;
}

texture3DVec texture3DVecCreate() {
	texture3DVec vec;
	vec.data = (Batch3D*)calloc(0, sizeof(Batch3D));
	vec.size = 0;
	vec.limit = 0;
	return vec;
}
void texture3DVecCheckSize(texture3DVec* vec) {
	if (vec->size + 1 > vec->limit) {
		Batch3D* temp;
		vec->limit = vec->size * 2;
		temp = (Batch3D*)realloc(vec->data, vec->limit * sizeof(Batch3D));
		if (temp) { vec->data = temp; }
	}
}
void texture3DVecPushBack(texture3DVec* vec, Batch3D num) {
	vec->size += 1;
	texture3DVecCheckSize(vec);
	vec->data[vec->size - 1] = num;
}
void texture3DVecClear(texture3DVec* vec) {
	free(vec->data);
	vec->limit /= 2;
	vec->data = (Batch3D*)calloc(vec->limit, sizeof(Batch3D));
	vec->size = 0;
}
void texture3DVecDelete(texture3DVec* vec) {
	for (int i = 0; i < vec->size; i++) {
		delete3DBatch(&vec->data[i - 1]);
		glDeleteTextures(1, &vec->data[i - 1].textureID);
	}
	free(vec->data);
	vec->size = 0;
	vec->limit = 0;
}
#ifdef __cplusplus
}
#endif