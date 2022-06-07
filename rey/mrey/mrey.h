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

#include <math.h>

struct Vector3f {
    float x, y, z;
}; typedef struct Vector3f Vector3f;
Vector3f Vector3f_init(float x, float y, float z);
Vector3f Vector3f_create();
Vector3f Vector3f_cross(Vector3f a, Vector3f b);
Vector3f Vector3f_add(Vector3f a, Vector3f b);
Vector3f Vector3f_dot(Vector3f a, Vector3f b);
float Vector3f_length(Vector3f a);
Vector3f Vector3f_normalized(Vector3f a);
Vector3f Vector3f_rotate(Vector3f point, float angle, Vector3f axis);
struct Matrix4f {
    float m[4][4];
}; typedef struct Matrix4f Matrix4f;
Matrix4f Matrix4f_createIdentity();
Matrix4f Matrix4f_createTranslation(float x, float y, float z);
Matrix4f Matrix4f_createRotation(float x, float y, float z);
Matrix4f Matrix4f_createScale(float x, float y, float z);
Matrix4f Matrix4f_createProjection(float fov, float width, float height, float zNear, float zFar);
Matrix4f Matrix4f_createCamera(Vector3f forward, Vector3f up);
Matrix4f Matrix4f_mul(Matrix4f a, Matrix4f b);
float* Matrix4f_createFloatArray(Matrix4f a);

struct Camera {
    Vector3f yAxis;
    Vector3f pos, forward, up;
};
typedef struct Camera Camera;
Camera Camera_init(Vector3f pos, Vector3f forward, Vector3f up);
Camera Camera_create();
void Camera_move(Camera* cam, Vector3f dir, float amt);
void Camera_rotateY(Camera* cam, float angle);

void Camera_rotateX(Camera* cam, float angle);

struct Transform {
    Camera camera;
    float zNear;
    float zFar;
    float width;
    float height;
    float fov;

    Vector3f translation;
    Vector3f rotation;
    Vector3f scale;
}; typedef struct Transform Transform;

Transform Transform_create(float fov, float width, float height, float zNear, float zFar);
Matrix4f Transform_getTransformation(Transform a);
Matrix4f Transform_getProjectedTransformation(Transform a);

#ifdef __cplusplus
}
#endif
#endif