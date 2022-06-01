#ifndef MREY_H
#define MREY_H
#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <memory.h>
#include <stdlib.h>

struct C_floatVec {
	float* data;
	int size;
	int limit;
};
typedef struct C_floatVec C_floatVec;

C_floatVec C_floatVecCreate();
void C_floatVecPushBack(C_floatVec* vec, float num);
void C_floatVecPushBack7(C_floatVec* vec, float num[7]);
void C_floatVecPushBack21(C_floatVec* vec, float num[21]);
void C_floatVecClear(C_floatVec* vec);
void C_floatVecDelete(C_floatVec* vec);

struct C_intVec {
	int* data;
	int size;
	int limit;
};
typedef struct C_intVec C_intVec;

C_intVec C_intVecCreate();
void C_intVecPushBack(C_intVec* vec, float num);
void C_intVecClear(C_intVec* vec);
void C_intVecDelete(C_intVec* vec);

#ifndef IMPLEMENT_MREY_H
#define floatVec C_floatVec
#define floatVecCreate C_floatVecCreate
#define floatVecPushBack C_floatVecPushBack
#define floatVecClear C_floatVecClear
#define floatVecDelete C_floatVecDelete

#define floatVec C_intVec
#define intVecCreate C_intVecCreate
#define intVecPushBack C_intVecPushBack
#define intVecClear C_intVecClear
#define intVecDelete C_intVecDelete
#endif

#ifdef __cplusplus
}
#endif
#endif