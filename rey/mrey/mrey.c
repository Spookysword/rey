#include "mrey.h"

C_floatVec C_floatVecCreate() {
	C_floatVec vec;
	vec.data = (float*)calloc(0, sizeof(float));
	vec.size = 0;
	vec.limit = 0;
	return vec;
}

void C_floatVecCheckSize(C_floatVec* vec) {
	if (vec->size+1 > vec->limit) {
		float* temp;
		vec->limit = vec->size * 2;
		temp = (float*)realloc(vec->data, vec->limit * sizeof(float));
		if (temp) { vec->data = temp; }
	}
}

void C_floatVecPushBack(C_floatVec* vec, float num) {
	vec->size += 1;
	C_floatVecCheckSize(vec);
	vec->data[vec->size-1] = num;
}
void C_floatVecPushBack7(C_floatVec* vec, float num[7]) {
	vec->size += 7;
	C_floatVecCheckSize(vec);
	for (int i = 0; i < 7; i++) {
		vec->data[vec->size-i-1] = num[6-i];
	}
}
void C_floatVecPushBack9(C_floatVec* vec, float num[9]) {
	vec->size += 9;
	C_floatVecCheckSize(vec);
	for (int i = 0; i < 9; i++) {
		vec->data[vec->size-i-1] = num[8-i];
	}
}
void C_floatVecPushBack21(C_floatVec* vec, float num[21]) {
	vec->size += 21;
	C_floatVecCheckSize(vec);
	for (int i = 0; i < 21; i++) {
		vec->data[vec->size-i-1] = num[20-i];
	}
}
void C_floatVecPushBack27(C_floatVec* vec, float num[27]) {
	vec->size += 27;
	C_floatVecCheckSize(vec);
	for (int i = 0; i < 27; i++) {
		vec->data[vec->size-i-1] = num[26-i];
	}
}
void C_floatVecClear(C_floatVec* vec) {
	free(vec->data);
	vec->limit /= 2;
	vec->data = (float*)calloc(vec->limit, sizeof(float));
	vec->size = 0;
}
void C_floatVecDelete(C_floatVec* vec) {
	free(vec->data);
	vec->size = 0;
	vec->limit = 0;
}

C_intVec C_intVecCreate() {
	C_intVec vec;
	vec.data = (int*)calloc(0, sizeof(int));
	vec.size = 0;
	vec.limit = 0;
	return vec;
}

void C_intVecCheckSize(C_intVec* vec) {
	if (vec->size + 1 > vec->limit) {
		int* temp;
		vec->limit = vec->size * 2;
		temp = (int*)realloc(vec->data, vec->limit * sizeof(int));
		if (temp) { vec->data = temp; }
	}
}

void C_intVecPushBack(C_intVec* vec, float num) {
	vec->size += 1;
	C_intVecCheckSize(vec);
	vec->data[vec->size-1] = num;
}
void C_intVecClear(C_intVec* vec) {
	free(vec->data);
	vec->limit /= 2;
	vec->data = (int*)calloc(vec->limit, sizeof(int));
	vec->size = 0;
}
void C_intVecDelete(C_intVec* vec) {
	free(vec->data);
	vec->size = 0;
}