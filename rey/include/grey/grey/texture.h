#pragma once
#include "grey/grey/texture_batch.h"
#include "grey/grey/batch_3d.h"

typedef unsigned int Texture;

	struct textureVec {
		TextureBatch* data;
		int size;
		int limit;
	};
	typedef struct textureVec textureVec;

	struct texture3DVec {
		Batch3D* data;
		int size;
		int limit;
	};
	typedef struct texture3DVec texture3DVec;

	textureVec textureVecCreate();
	void textureVecPushBack(textureVec* vec, TextureBatch num);
	void textureVecClear(textureVec* vec);
	void textureVecDelete(textureVec* vec);

	texture3DVec texture3DVecCreate();
	void texture3DVecPushBack(texture3DVec* vec, Batch3D num);
	void texture3DVecClear(texture3DVec* vec);
	void texture3DVecDelete(texture3DVec* vec);