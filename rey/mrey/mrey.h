#ifndef MREY_H
#define MREY_H
#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>

struct C_floatVec {
	float* data;
	int size;
};
typedef struct C_floatVec C_floatVec;

C_floatVec C_floatVecCreate();
void C_floatVecPushBack(C_floatVec* vec, float num);
void C_floatVecClear(C_floatVec* vec);
void C_floatVecDelete(C_floatVec* vec);


struct C_intVec {
	int* data;
	int size;
};
typedef struct C_intVec C_intVec;

C_intVec C_intVecCreate();
void C_intVecPushBack(C_intVec* vec, float num);
void C_intVecClear(C_intVec* vec);
void C_intVecDelete(C_intVec* vec);

#ifdef __cplusplus
}
#endif
#endif