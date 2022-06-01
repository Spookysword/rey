#include "mrey.h"

C_floatVec C_floatVecCreate() {
	C_floatVec vec;
	vec.data = (float*)calloc(0, sizeof(float));
	vec.size = 0;
	return vec;
}
void C_floatVecPushBack(C_floatVec* vec, float num) {
	int a = vec->size;
	float* before = (float*)calloc(vec->size, sizeof(float));
	if (!before) { return; }
	for (int i = 0; i < vec->size; i++) {
		before[i] = vec->data[i];
	}
	vec->size += 1;
	free(vec->data);
	vec->data = (float*)calloc(vec->size, sizeof(float));
	if (!vec->data) { return; }
	for (int i = 0; i < a; i++) {
		// Nvm I love you C
		vec->data[i] = before[i];
	}
	vec->data[vec->size - 1] = num;
	free(before);
}
void C_floatVecClear(C_floatVec* vec) {
	free(vec->data);
	vec->data = (float*)calloc(0, sizeof(float));
	vec->size = 0;
}
void C_floatVecDelete(C_floatVec* vec) {
	free(vec->data);
	vec->size = 0;
}

C_intVec C_intVecCreate() {
	C_intVec vec;
	vec.data = (int*)calloc(0, sizeof(int));
	vec.size = 0;
	return vec;
}
void C_intVecPushBack(C_intVec* vec, float num) {
	int a = vec->size;
	int* before = (int*)calloc(vec->size, sizeof(int));
	if (!before) { return; }
	for (int i = 0; i < vec->size; i++) {
		before[i] = vec->data[i];
	}
	vec->size += 1;
	free(vec->data);
	vec->data = (int*)calloc(vec->size, sizeof(int));
	if (!vec->data) { return; }
	for (int i = 0; i < a; i++) {
		// Nvm I love you C
		vec->data[i] = before[i];
	}
	vec->data[vec->size - 1] = num;
	free(before);
}
void C_intVecClear(C_intVec* vec) {
	free(vec->data);
	vec->data = (int*)calloc(0, sizeof(int));
	vec->size = 0;
}
void C_intVecDelete(C_intVec* vec) {
	free(vec->data);
	vec->size = 0;
}