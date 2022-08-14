#include "mrey/mrey.h"

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
void floatVecPushBack12(floatVec* vec, float num[12]) {
    vec->size += 12;
    floatVecCheckSize(vec);
    for (int i = 0; i < 12; i++) {
        vec->data[vec->size - i - 1] = num[11 - i];
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
void floatVecPushBack36(floatVec* vec, float num[36]) {
    vec->size += 36;
    floatVecCheckSize(vec);
    for (int i = 0; i < 36; i++) {
        vec->data[vec->size - i - 1] = num[35 - i];
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



#include <math.h>

// 3d math lib

#define PI 3.1415926535897932384626433

float toRadians(float degrees) {
    return degrees * (PI / 180);
}

float toDegrees(float radians) {
    return radians * 180.0f / PI;
}

Quat Quat_new(float x, float y, float z, float w) {
    Quat q;
    q.x = x;
    q.y = y;
    q.z = z;
    q.w = w;
    return q;
}
Quat Quat_create() {
    return Quat_new(0.0f, 0.0f, 0.0f, 0.0f);
}
float Quat_length(Quat a) {
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
}
Quat Quat_normalize(Quat a) {
    float length = Quat_length(a);
    return Quat_new(a.x / length, a.y / length, a.z / length, a.w / length);
}
Quat Quat_conjugate(Quat a) {
    return Quat_new(-a.x, -a.y, -a.z, a.w);
}
Quat Quat_mulQ(Quat a, Quat b) {
    float w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
    float x = a.x * b.w + a.w * b.x + a.y * b.z - a.z * b.y;
    float y = a.y * b.w + a.w * b.y + a.z * b.x - a.x * b.z;
    float z = a.z * b.w + a.w * b.z + a.x * b.y - a.y * b.x;
    return Quat_new(x, y, z, w);
}
Quat Quat_mulV(Quat a, Vec3 b) {
    float w = -a.x * b.x - a.y * b.y - a.z * b.z;
    float x =  a.w * b.x + a.y * b.z - a.z * b.y;
    float y =  a.w * b.y + a.z * b.x - a.x * b.z;
    float z =  a.w * b.z + a.x * b.y - a.y * b.x;
    return Quat_new(x, y, z, w);
}

Vec3 Vec3_new(float x, float y, float z) {
    Vec3 ret;
    ret.x = x;
    ret.y = y;
    ret.z = z;
    return ret;
}
Vec3 Vec3_toVec(float a[3]) {
    Vec3 v;
    v.x = a[0];
    v.y = a[1];
    v.z = a[2];
    return v;
}
float* Vec3_fromVec(Vec3 a) {
    float v[3] = { a.x, a.y, a.z };
    return v;

}
Vec3 Vec3_create() {
    return Vec3_new(0.0f, 0.0f, 0.0f);
}
float Vec3_length(Vec3 a) {
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}
float Vec3_dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.x * b.z;
}
Vec3 Vec3_cross(Vec3 a, Vec3 b) {
    float x = a.y * b.z - a.z * b.y;
    float y = a.z * b.x - a.x * b.z;
    float z = a.x * b.y - a.y * b.x;
    return Vec3_new(x, y, z);
}
Vec3 Vec3_sub(Vec3 a, Vec3 b) {
    return Vec3_new(a.x - b.x, a.y - b.y, a.z - b.z);
}
Vec3 Vec3_normalize(Vec3 a) {
    float length = Vec3_length(a);
    if (length == 0.0f) {
        return Vec3_new(0.0f, 0.0f, 0.0f);
    }
    return Vec3_new(a.x / length, a.y / length, a.z / length);
}
Vec3 Vec3_rotate(Vec3 point, float angle, Vec3 axis) {
    float sha = sin(toRadians(angle / 2));
    float cha = cos(toRadians(angle / 2));

    float rX = axis.x * sha;
    float rY = axis.y * sha;
    float rZ = axis.z * sha;
    float rW = cha;

    Quat rotation = Quat_new(rX, rY, rZ, rW);
    Quat conjugate = Quat_conjugate(rotation);

    Quat w = Quat_mulQ(Quat_mulV(rotation, point), conjugate);

    return Vec3_new(w.x, w.y, w.z);
}
Vec3 Vec3_addF(Vec3 a, float b) {
    return Vec3_new(a.x + b, a.y + b, a.z + b);
}
Vec3 Vec3_addV(Vec3 a, Vec3 b) {
    return Vec3_new(a.x + b.x, a.y + b.y, a.z + b.z);
}
Vec3 Vec3_mulF(Vec3 a, float b) {
    return Vec3_new(a.x * b, a.y * b, a.z * b);
}

Camera Camera_new(Vec3 pos, Vec3 forward, Vec3 up) {
    Camera c;
    c.pos = pos;
    c.forward = forward;
    c.up = up;
    c.yAxis = Vec3_new(0, 1, 0);
    return c;
}
Camera Camera_create() {
    return Camera_new(Vec3_new(0, 0, 0), Vec3_new(0, 0, 1), Vec3_new(0, 1, 0));
}
Camera Camera_move(Camera cam, Vec3 dir, float amt) {
    cam.pos = Vec3_addV(cam.pos, Vec3_mulF(dir, amt));
    return cam;
}
Camera Camera_rotateY(Camera cam, float angle) {
    Vec3 Haxis = Vec3_normalize(Vec3_cross(cam.yAxis, cam.forward));
    cam.forward = Vec3_normalize(Vec3_rotate(cam.forward, angle, cam.yAxis));
    cam.up = Vec3_normalize(Vec3_cross(cam.forward, Haxis));
    return cam;
}
Camera Camera_rotateX(Camera cam, float angle) {
    Vec3 Haxis = Vec3_normalize(Vec3_cross(cam.yAxis, cam.forward));
    cam.forward = Vec3_normalize(Vec3_rotate(cam.forward, angle, Haxis));
    cam.up = Vec3_normalize(Vec3_cross(cam.forward, Haxis));
    return cam;
}
Vec3 Camera_left(Camera cam) {
    return Vec3_normalize(Vec3_cross(cam.forward, cam.up));
}
Vec3 Camera_right(Camera cam) {
    return Vec3_normalize(Vec3_cross(cam.up, cam.forward));
}

Mat4 Mat4_initIdentity() {
    Mat4 m;
    m.m[0][0] = 1; m.m[0][1] = 0; m.m[0][2] = 0; m.m[0][3] = 0;
    m.m[1][0] = 0; m.m[1][1] = 1; m.m[1][2] = 0; m.m[1][3] = 0;
    m.m[2][0] = 0; m.m[2][1] = 0; m.m[2][2] = 1; m.m[2][3] = 0;
    m.m[3][0] = 0; m.m[3][1] = 0; m.m[3][2] = 0; m.m[3][3] = 1;
    return m;
}
Mat4 Mat4_mul(Mat4 a, Mat4 b) {
    Mat4 m;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m.m[i][j] = a.m[i][0] * b.m[0][j] +
                a.m[i][1] * b.m[1][j] +
                a.m[i][2] * b.m[2][j] +
                a.m[i][3] * b.m[3][j];
        }
    }
    return m;
}
Mat4 Mat4_initTranslation(float x, float y, float z) {
    Mat4 m;
    m.m[0][0] = 1; m.m[0][1] = 0; m.m[0][2] = 0; m.m[0][3] = x;
    m.m[1][0] = 0; m.m[1][1] = 1; m.m[1][2] = 0; m.m[1][3] = y;
    m.m[2][0] = 0; m.m[2][1] = 0; m.m[2][2] = 1; m.m[2][3] = z;
    m.m[3][0] = 0; m.m[3][1] = 0; m.m[3][2] = 0; m.m[3][3] = 1;
    return m;
}
Mat4 Mat4_initRotation(float _x, float _y, float _z) {
    Mat4 rx;
    Mat4 ry;
    Mat4 rz;

    float x = toRadians(_x);
    float y = toRadians(_y);
    float z = toRadians(_z);

    rx.m[0][0] = 1; rx.m[0][1] = 0; rx.m[0][2] = 0; rx.m[0][3] = 0;
    rx.m[1][0] = 0; rx.m[1][1] = cos(x); rx.m[1][2] = -sin(x); rx.m[1][3] = 0;
    rx.m[2][0] = 0; rx.m[2][1] = sin(x); rx.m[2][2] = cos(x); rx.m[2][3] = 0;
    rx.m[3][0] = 0; rx.m[3][1] = 0; rx.m[3][2] = 0; rx.m[3][3] = 1;

    ry.m[0][0] = cos(y); ry.m[0][1] = 0; ry.m[0][2] = -sin(y); ry.m[0][3] = 0;
    ry.m[1][0] = 0; ry.m[1][1] = 1; ry.m[1][2] = 0; ry.m[1][3] = 0;
    ry.m[2][0] = sin(y); ry.m[2][1] = 0; ry.m[2][2] = cos(y); ry.m[2][3] = 0;
    ry.m[3][0] = 0; ry.m[3][1] = 0; ry.m[3][2] = 0; ry.m[3][3] = 1;

    rz.m[0][0] = cos(z); rz.m[0][1] = -sin(z); rz.m[0][2] = 0; rz.m[0][3] = 0;
    rz.m[1][0] = sin(z); rz.m[1][1] = cos(z); rz.m[1][2] = 0; rz.m[1][3] = 0;
    rz.m[2][0] = 0; rz.m[2][1] = 0; rz.m[2][2] = 1; rz.m[2][3] = 0;
    rz.m[3][0] = 0; rz.m[3][1] = 0; rz.m[3][2] = 0; rz.m[3][3] = 1;
    return Mat4_mul(rz, Mat4_mul(ry, rx));
}
Mat4 Mat4_initScale(float x, float y, float z) {
    Mat4 m;
    m.m[0][0] = x; m.m[0][1] = 0; m.m[0][2] = 0; m.m[0][3] = 0;
    m.m[1][0] = 0; m.m[1][1] = y; m.m[1][2] = 0; m.m[1][3] = 0;
    m.m[2][0] = 0; m.m[2][1] = 0; m.m[2][2] = z; m.m[2][3] = 0;
    m.m[3][0] = 0; m.m[3][1] = 0; m.m[3][2] = 0; m.m[3][3] = 1;
    return m;
}
Mat4 Mat4_initProjection(float fov, float width, float height, float zNear, float zFar) {
    float ar = width / height;
    float thFOV = tan(toRadians(fov / 2));
    float zRange = zNear - zFar;

    Mat4 m;
    m.m[0][0] = 1.0f / (thFOV * ar); m.m[0][1] = 0; m.m[0][2] = 0; m.m[0][3] = 0;
    m.m[1][0] = 0; m.m[1][1] = 1.0f / thFOV; m.m[1][2] = 0; m.m[1][3] = 0;
    m.m[2][0] = 0; m.m[2][1] = 0; m.m[2][2] = (-zNear - zFar) / zRange; m.m[2][3] = 2 * zFar * zNear / zRange;
    m.m[3][0] = 0; m.m[3][1] = 0; m.m[3][2] = 1; m.m[3][3] = 0; // ???
    return m;
}
Mat4 Mat4_initCamera(Vec3 forward, Vec3 up) {
    Vec3 f = Vec3_normalize(forward);
    Vec3 r = Vec3_normalize(up);
    r = Vec3_cross(r, f);

    Vec3 u = Vec3_cross(f, r);
    Mat4 m;
    m.m[0][0] = r.x; m.m[0][1] = r.y; m.m[0][2] = r.z; m.m[0][3] = 0;
    m.m[1][0] = u.x; m.m[1][1] = u.y; m.m[1][2] = u.z; m.m[1][3] = 0;
    m.m[2][0] = f.x; m.m[2][1] = f.y; m.m[2][2] = f.z; m.m[2][3] = 0;
    m.m[3][0] = 0; m.m[3][1] = 0; m.m[3][2] = 0; m.m[3][3] = 1;
    return m;
}

Transform Transform_create(float zNear, float zFar, float width, float height, float fov) {
    Transform t;
    t.translation = Vec3_new(0, 0, 0);
    t.rotation = Vec3_new(0, 0, 0);
    t.scale = Vec3_new(1, 1, 1);
    t.zNear = zNear;
    t.zFar = zFar;
    t.width = width;
    t.height = height;
    t.fov = fov;
    return t;
}
Mat4 Transform_getTranformation(Transform t) {
    Mat4 translationMatrix = Mat4_initTranslation(t.translation.x, t.translation.y, t.translation.z);
    Mat4 rotationMatrix = Mat4_initRotation(t.rotation.x, t.rotation.y, t.rotation.z);
    Mat4 scaleMatrix = Mat4_initScale(t.scale.x, t.scale.y, t.scale.z);
    return  Mat4_mul(translationMatrix, Mat4_mul(rotationMatrix, scaleMatrix));
}
Mat4 Transform_getProjectedTranformation(Transform t) {
    Mat4 transformationMatrix = Transform_getTranformation(t);
    Mat4 projectionMatrix = Mat4_initProjection(t.fov, t.width, t.height, t.zNear, t.zFar);
    Mat4 cameraRotation = Mat4_initCamera(t.camera.forward, t.camera.up);
    Mat4 cameraTranslation = Mat4_initTranslation(-t.camera.pos.x, -t.camera.pos.y, -t.camera.pos.z);
    return Mat4_mul(projectionMatrix, Mat4_mul(cameraRotation, Mat4_mul(cameraTranslation, transformationMatrix)));
}

Vec2 Vec2_new(double x, double y) {
    Vec2 v;
    v.x = x;
    v.y = y;
    return v;
}
Vec2 Vec2_toVec(double a[2]) {
    Vec2 v;
    v.x = a[0];
    v.y = a[1];
    return v;
}
double* Vec2_fromVec(Vec2 a) {
    double f[2] = {
        a.x, a.y
    };
    return f;
}
Vec2 Vec2_create() {
    return Vec2_new(0.0f, 0.0f);
}
double Vec2_length(Vec2 v) {
    return sqrt(v.x * v.x + v.y * v.y);
}
double Vec2_dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}
Vec2 Vec2_normalize(Vec2 v) {
    double length = Vec2_length(v);
    return Vec2_new(v.x / length, v.y / length);
}
Vec2 Vec2_rotate(Vec2 v, double a) {
    double r = toRadians(a);
    double c = cos(r);
    double s = sin(r);

    return Vec2_new(v.x * c - v.y * s, v.x * s + v.y * c);
}
Vec2 Vec2_mulf(Vec2 v, double f) {
    return Vec2_new(v.x * f, v.y * f);
}

Vec2 Vec2_subv(Vec2 a, Vec2 b) {
    return Vec2_new(a.x - b.x, a.y - b.y);
}
Vec2 Vec2_addv(Vec2 a, Vec2 b) {
    return Vec2_new(a.x + b.x, a.y + b.y);
}
Vec2 Vec2_addf(Vec2 a, double f) {
    return Vec2_new(a.x + f, a.y + f);
}
Vec2 Vec2_mulv(Vec2 a, Vec2 b) {
    return Vec2_new(a.x * b.x, a.y * b.y);
}

Vec4 Vec4_new(double x, double y, double z, double w) {
    Vec4 v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}
Vec4 Vec4_create() {
    return Vec4_new(0.0f, 0.0f, 0.0f, 1.0f);
}