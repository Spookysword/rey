#include "mrey.h"

floatVec floatVecCreate() {
    floatVec vec;
    vec.data = (float*)calloc(0, sizeof(float));
    vec.size = 0;
    vec.limit = 0;
    return vec;
}

void floatVecCheckSize(floatVec* vec) {
    if (vec->size + 1 > vec->limit) {
        float* temp;
        vec->limit = vec->size * 2;
        temp = (float*)realloc(vec->data, vec->limit * sizeof(float));
        if (temp) { vec->data = temp; }
    }
}

void floatVecPushBack(floatVec* vec, float num) {
    vec->size += 1;
    floatVecCheckSize(vec);
    vec->data[vec->size - 1] = num;
}
void floatVecPushBack7(floatVec* vec, float num[7]) {
    vec->size += 7;
    floatVecCheckSize(vec);
    for (int i = 0; i < 7; i++) {
        vec->data[vec->size - i - 1] = num[6 - i];
    }
}
void floatVecPushBack9(floatVec* vec, float num[9]) {
    vec->size += 9;
    floatVecCheckSize(vec);
    for (int i = 0; i < 9; i++) {
        vec->data[vec->size - i - 1] = num[8 - i];
    }
}
void floatVecPushBack21(floatVec* vec, float num[21]) {
    vec->size += 21;
    floatVecCheckSize(vec);
    for (int i = 0; i < 21; i++) {
        vec->data[vec->size - i - 1] = num[20 - i];
    }
}
void floatVecPushBack27(floatVec* vec, float num[27]) {
    vec->size += 27;
    floatVecCheckSize(vec);
    for (int i = 0; i < 27; i++) {
        vec->data[vec->size - i - 1] = num[26 - i];
    }
}
void floatVecClear(floatVec* vec) {
    free(vec->data);
    vec->limit /= 2;
    vec->data = (float*)calloc(vec->limit, sizeof(float));
    vec->size = 0;
}
void floatVecDelete(floatVec* vec) {
    free(vec->data);
    vec->size = 0;
    vec->limit = 0;
}

intVec intVecCreate() {
    intVec vec;
    vec.data = (int*)calloc(0, sizeof(int));
    vec.size = 0;
    vec.limit = 0;
    return vec;
}

void intVecCheckSize(intVec* vec) {
    if (vec->size + 1 > vec->limit) {
        int* temp;
        vec->limit = vec->size * 2;
        temp = (int*)realloc(vec->data, vec->limit * sizeof(int));
        if (temp) { vec->data = temp; }
    }
}

void intVecPushBack(intVec* vec, float num) {
    vec->size += 1;
    intVecCheckSize(vec);
    vec->data[vec->size - 1] = num;
}
void intVecClear(intVec* vec) {
    free(vec->data);
    vec->limit /= 2;
    vec->data = (int*)calloc(vec->limit, sizeof(int));
    vec->size = 0;
}
void intVecDelete(intVec* vec) {
    free(vec->data);
    vec->size = 0;
}

float rotateX(float x, float y, float c1, float c2, float rotation) {
    float pi = 3.1415926535897932384626433;

    float cor = cos(rotation);
    float sir = sin(rotation);

    return cos(rotation) * (x - c1) + (y - c2) * sin(rotation) + c1;
}

float rotateY(float x, float y, float c1, float c2, float rotation) {
    float pi = 3.1415926535897932384626433;

    float cor = cos(rotation);
    float sir = sin(rotation);

    return -sin(rotation) * (x - c1) + cos(rotation) * (y - c2) + c2;
}

Vec3 Vec3_init(float x, float y, float z) {
    Vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}
Vec3 Vec3_create() {
    return Vec3_init(0, 0, 0);
}