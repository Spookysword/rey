#include "mrey.h"

floatVec floatVecCreate() {
	floatVec vec;
	vec.data = (float*)calloc(0, sizeof(float));
	vec.size = 0;
	vec.limit = 0;
	return vec;
}

void floatVecCheckSize(floatVec* vec) {
	if (vec->size+1 > vec->limit) {
		float* temp;
		vec->limit = vec->size * 2;
		temp = (float*)realloc(vec->data, vec->limit * sizeof(float));
		if (temp) { vec->data = temp; }
	}
}

void floatVecPushBack(floatVec* vec, float num) {
	vec->size += 1;
	floatVecCheckSize(vec);
	vec->data[vec->size-1] = num;
}
void floatVecPushBack7(floatVec* vec, float num[7]) {
	vec->size += 7;
	floatVecCheckSize(vec);
	for (int i = 0; i < 7; i++) {
		vec->data[vec->size-i-1] = num[6-i];
	}
}
void floatVecPushBack9(floatVec* vec, float num[9]) {
	vec->size += 9;
	floatVecCheckSize(vec);
	for (int i = 0; i < 9; i++) {
		vec->data[vec->size-i-1] = num[8-i];
	}
}
void floatVecPushBack21(floatVec* vec, float num[21]) {
	vec->size += 21;
	floatVecCheckSize(vec);
	for (int i = 0; i < 21; i++) {
		vec->data[vec->size-i-1] = num[20-i];
	}
}
void floatVecPushBack27(floatVec* vec, float num[27]) {
	vec->size += 27;
	floatVecCheckSize(vec);
	for (int i = 0; i < 27; i++) {
		vec->data[vec->size-i-1] = num[26-i];
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
	vec->data[vec->size-1] = num;
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

Vector3f Vector3f_init(float x, float y, float z)
{
    Vector3f v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}
Vector3f Vector3f_create() {
    Vector3f v;
    v.x = 0;
    v.y = 0;
    v.z = 0;
    return v;
}
Vector3f Vector3f_cross(Vector3f a, Vector3f b) {
    Vector3f result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}
Vector3f Vector3f_add(Vector3f a, Vector3f b) {
    Vector3f result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}
Vector3f Vector3f_dot(Vector3f a, Vector3f b) {
    Vector3f result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    result.z = a.z * b.z;
    return result;
}
float Vector3f_length(Vector3f a) {
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}
Vector3f Vector3f_normalized(Vector3f a) {
    Vector3f result;
    float length = Vector3f_length(a);
    result.x = a.x / length;
    result.y = a.y / length;
    result.z = a.z / length;
    return result;
}
Vector3f Vector3f_rotate(Vector3f point, float angle, Vector3f axis) {
    Vector3f result;
    float c = cos(angle);
    float s = sin(angle);
    float omc = 1.0f - c;
    float x = point.x;
    float y = point.y;
    float z = point.z;
    float ax = axis.x;
    float ay = axis.y;
    float az = axis.z;
    result.x = x * (omc * ax * ax + c) + y * (omc * ax * ay - s * az) + z * (omc * ax * az + s * ay);
    result.y = x * (omc * ax * ay + s * az) + y * (omc * ay * ay + c) + z * (omc * ay * az - s * ax);
    result.z = x * (omc * ax * az - s * ay) + y * (omc * ay * az + s * ax) + z * (omc * az * az + c);
    return result;
}

Matrix4f Matrix4f_createIdentity() {
    Matrix4f mat;
    mat.m[0][0] = 1.0f; mat.m[0][1] = 0.0f; mat.m[0][2] = 0.0f; mat.m[0][3] = 0.0f;
    mat.m[1][0] = 0.0f; mat.m[1][1] = 1.0f; mat.m[1][2] = 0.0f; mat.m[1][3] = 0.0f;
    mat.m[2][0] = 0.0f; mat.m[2][1] = 0.0f; mat.m[2][2] = 1.0f; mat.m[2][3] = 0.0f;
    mat.m[3][0] = 0.0f; mat.m[3][1] = 0.0f; mat.m[3][2] = 0.0f; mat.m[3][3] = 1.0f;
    return mat;
}
Matrix4f Matrix4f_createTranslation(float x, float y, float z)
{
    Matrix4f mat = Matrix4f_createIdentity();
    mat.m[3][0] = x;
    mat.m[3][1] = y;
    mat.m[3][2] = z;
    return mat;
}
Matrix4f Matrix4f_createRotation(float x, float y, float z)
{
    Matrix4f mat = Matrix4f_createIdentity();
    float sx = sinf(x);
    float cx = cosf(x);
    float sy = sinf(y);
    float cy = cosf(y);
    float sz = sinf(z);
    float cz = cosf(z);
    mat.m[0][0] = cy * cz;
    mat.m[0][1] = cy * sz;
    mat.m[0][2] = -sy;
    mat.m[1][0] = sx * sy * cz - cx * sz;
    mat.m[1][1] = sx * sy * sz + cx * cz;
    mat.m[1][2] = sx * cy;
    mat.m[2][0] = cx * sy * cz + sx * sz;
    mat.m[2][1] = cx * sy * sz - sx * cz;
    mat.m[2][2] = cx * cy;
    return mat;
}
Matrix4f Matrix4f_createScale(float x, float y, float z)
{
    Matrix4f mat = Matrix4f_createIdentity();
    mat.m[0][0] = x;
    mat.m[1][1] = y;
    mat.m[2][2] = z;
    return mat;
}
Matrix4f Matrix4f_createProjection(float fov, float width, float height, float zNear, float zFar)
{
    Matrix4f mat = Matrix4f_createIdentity();
    float ar = width / height;
    float tanHalfFOV = tanf(fov / 2.0f);
    mat.m[0][0] = 1.0f / (tanHalfFOV * ar);
    mat.m[1][1] = 1.0f / tanHalfFOV;
    mat.m[2][2] = -(zFar + zNear) / (zFar - zNear);
    mat.m[2][3] = -1.0f;
    mat.m[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
    return mat;
}
Matrix4f Matrix4f_createCamera(Vector3f forward, Vector3f up)
{
    Matrix4f mat = Matrix4f_createIdentity();
    Vector3f f = forward;
    Vector3f r = Vector3f_cross(up, f);
    Vector3f u = Vector3f_cross(f, r);
    mat.m[0][0] = r.x;
    mat.m[1][0] = r.y;
    mat.m[2][0] = r.z;
    mat.m[0][1] = u.x;
    mat.m[1][1] = u.y;
    mat.m[2][1] = u.z;
    mat.m[0][2] = f.x;
    mat.m[1][2] = f.y;
    mat.m[2][2] = f.z;
    return mat;
}
Matrix4f Matrix4f_mul(Matrix4f a, Matrix4f b)
{
    Matrix4f mat = Matrix4f_createIdentity();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat.m[i][j] = 0.0f;
            for (int k = 0; k < 4; k++) {
                mat.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return mat;
}
float* Matrix4f_createFloatArray(Matrix4f a) {
    float buffer[4 * 4] = { 0.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f, 0.0f };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            buffer[i * 4 + j] = a.m[i][j];
        }
    }
}

Camera Camera_init(Vector3f pos, Vector3f forward, Vector3f up) {
    Camera camera;
    camera.yAxis = Vector3f_init(0, 1, 0);
    camera.pos = pos;
    camera.forward = forward;
    camera.up = up;
    return camera;
}
Camera Camera_create() {
    Camera_init(Vector3f_init(0, 0, 0), Vector3f_init(0, 0, 1), Vector3f_init(0, 1, 0));
}
void Camera_move(Camera* cam, Vector3f dir, float amt) {
    cam->pos = Vector3f_add(cam->pos, Vector3f_init(dir.x * amt, dir.y * amt, dir.z * amt));
}
void Camera_rotateY(Camera* cam, float angle) {
    Vector3f hAxis = Vector3f_normalized(Vector3f_cross(cam->yAxis, cam->forward));

    cam->forward = Vector3f_normalized(Vector3f_rotate(cam->forward, angle, cam->yAxis));

    cam->up = Vector3f_normalized(Vector3f_cross(cam->forward, hAxis));
}

void Camera_rotateX(Camera* cam, float angle) {
    Vector3f hAxis = Vector3f_normalized(Vector3f_cross(cam->yAxis, cam->forward));

    cam->forward = Vector3f_normalized(Vector3f_rotate(cam->forward, angle, hAxis));

    cam->up = Vector3f_normalized(Vector3f_cross(cam->forward, hAxis));
}

Transform Transform_create() {
    Transform transform;
    transform.translation = Vector3f_init(0, 0, 0);
    transform.rotation = Vector3f_init(0, 0, 0);
    transform.scale = Vector3f_init(1, 1, 1);
    return transform;
}
Matrix4f Transform_getTransformation(Transform a) {
    Matrix4f translation = Matrix4f_createTranslation(a.translation.x, a.translation.y, a.translation.z);
    Matrix4f rotation = Matrix4f_createRotation(a.rotation.x, a.rotation.y, a.rotation.z);
    Matrix4f scale = Matrix4f_createScale(a.scale.x, a.scale.y, a.scale.z);
    return Matrix4f_mul(translation, Matrix4f_mul(rotation, scale));
}
Matrix4f Transform_getProjectedTransformation(Transform a) {
    Matrix4f tranformation = Transform_getTransformation(a);
    Matrix4f projection = Matrix4f_createProjection(a.fov, a.width, a.height, a.zNear, a.zFar);
    Matrix4f cameraRotation = Matrix4f_createCamera(a.camera.forward, a.camera.up);
    Matrix4f cameraTranslation = Matrix4f_createTranslation(-a.camera.pos.x, -a.camera.pos.y, -a.camera.pos.z);
    return Matrix4f_mul(Matrix4f_mul(Matrix4f_mul(projection, cameraRotation), cameraTranslation), tranformation);
}