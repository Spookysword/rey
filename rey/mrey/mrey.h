#ifndef MREY_H
#define MREY_H
#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <memory.h>
#include <stdlib.h>

#define PI 3.1415926535897932384626433

    struct floatVec {
        float* data;
        int size;
        int limit;
    };
    typedef struct floatVec floatVec;

    floatVec floatVecCreate();
    void floatVecPushBack(floatVec* vec, float num);
    void floatVecPushBack7(floatVec* vec, float num[7]);
    void floatVecPushBack9(floatVec* vec, float num[9]);
    void floatVecPushBack21(floatVec* vec, float num[21]);
    void floatVecPushBack27(floatVec* vec, float num[27]);
    void floatVecClear(floatVec* vec);
    void floatVecDelete(floatVec* vec);

    struct intVec {
        int* data;
        int size;
        int limit;
    };
    typedef struct intVec intVec;

    intVec intVecCreate();
    void intVecPushBack(intVec* vec, float num);
    void intVecClear(intVec* vec);
    void intVecDelete(intVec* vec);

    float rotateX(float x, float y, float c1, float c2, float rotation);
    float rotateY(float x, float y, float c1, float c2, float rotation);

    typedef struct Vec3 {
        float x, y, z;
    } Vec3;
    Vec3 Vec3_init(float x, float y, float z);
    Vec3 Vec3_create();

#ifdef __cplusplus
}
#endif
#endif