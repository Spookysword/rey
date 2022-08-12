#include "grey/grey/font.h"
#ifdef __cplusplus
namespace grey {
#endif
FT_Library FT;

fontVec fontVecCreate() {
	fontVec vec;
	vec.data = (Font*)calloc(0, sizeof(Font));
	vec.size = 0;
	vec.limit = 0;
	return vec;
}
void fontVecCheckSize(fontVec* vec) {
	if (vec->size + 1 > vec->limit) {
		Font* temp;
		vec->limit = vec->size * 2;
		temp = (Font*)realloc(vec->data, vec->limit * sizeof(Font));
		if (temp) { vec->data = temp; }
	}
}
void fontVecPushBack(fontVec* vec, Font num) {
	vec->size += 1;
	fontVecCheckSize(vec);
	vec->data[vec->size - 1] = num;
}
void fontVecClear(fontVec* vec) {
	free(vec->data);
	vec->limit /= 2;
	vec->data = (Font*)calloc(vec->limit, sizeof(Font));
	vec->size = 0;
}
// This function kinda maybe doesn't exist yet possibly perhaps
void fontVecDelete(fontVec* vec) {
	for (int i = 0; i < vec->size; i++) {

	}
}
#ifdef __cplusplus
}
#endif