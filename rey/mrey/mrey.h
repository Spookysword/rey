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

    float toRadians(float degrees);
    float toDegrees(float radians);

    typedef struct Quat {
        float x, y, z, w;
    } Quat;

    typedef struct Vec3 {
        float x, y, z;
    } Vec3;
    Vec3 Vec3_new(float x, float y, float z);
    Vec3 Vec3_toVec(float a[3]);
    float* Vec3_fromVec(Vec3 a);
    Vec3 Vec3_create();

    typedef struct Camera {
        Vec3 pos, forward, up, yAxis;
    } Camera;
    Camera Camera_new(Vec3 pos, Vec3 forward, Vec3 up);
    Camera Camera_create();
    Camera Camera_move(Camera cam, Vec3 dir, float amt);
    Camera Camera_rotateY(Camera cam, float angle);
    Camera Camera_rotateX(Camera cam, float angle);
    Vec3 Camera_left(Camera cam);
    Vec3 Camera_right(Camera cam);

    typedef struct Mat4 {
        float m[4][4];
    } Mat4;
    Mat4 Mat4_initCamera(Vec3 forward, Vec3 up);
    Mat4 Mat4_initProjection(float fov, float width, float height, float zNear, float zFar);
    
    typedef struct Transform {
        Camera camera;
        float zNear, zFar, width, height, fov;
        Vec3 translation, rotation, scale;
    } Transform;
    Transform Transform_create(float zNear, float zFar, float width, float height, float fov);
    Mat4 Transform_getTranformation(Transform t);
    Mat4 Transform_getProjectedTranformation(Transform t);
    float* createFloatBuffer(Mat4 m);
#define createFloatBuffer(a) {a.m[0][0],a.m[0][1],a.m[0][2],a.m[0][3],a.m[1][0],a.m[1][1],a.m[1][2],a.m[1][3],a.m[2][0],a.m[2][1],a.m[2][2],a.m[2][3],a.m[3][0],a.m[3][1],a.m[3][2],a.m[3][3]}

#define printMat4(a) for (int i = 0; i < 4; i++) {printf("%f %f %f %f\n", a.m[i][0], a.m[i][1], a.m[i][2], a.m[i][3]);} printf("\n");


#ifdef __cplusplus
}
#endif
#endif