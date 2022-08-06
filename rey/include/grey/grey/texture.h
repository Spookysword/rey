#pragma once
#include "grey/grey/texture_batch.h"
#include "grey/grey/batch_3d.h"

// The index of a texture.
typedef unsigned int Texture;

	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. A texture vector, handling the batch rendering of textures.
	struct textureVec {
		TextureBatch* data;
		int size;
		int limit;
	};
	typedef struct textureVec textureVec;

	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. A 3D texture vector, handling the batch rendering of 3D textures.
	struct texture3DVec {
		Batch3D* data;
		int size;
		int limit;
	};
	typedef struct texture3DVec texture3DVec;

	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Creates a texture vector.
	textureVec textureVecCreate();
	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Pushes back a new texture to the texture vector.
	void textureVecPushBack(textureVec* vec, TextureBatch num);
	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Clears the entire texture vector specificed.
	void textureVecClear(textureVec* vec);
	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Deletes the texture vector specified from memory entirely.
	void textureVecDelete(textureVec* vec);

	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Creates a 3D texture vector.
	texture3DVec texture3DVecCreate();
	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Pushes back a new 3D texture to the 3D texture vector.
	void texture3DVecPushBack(texture3DVec* vec, Batch3D num);
	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Clears the entire 3D texture vector specified.
	void texture3DVecClear(texture3DVec* vec);
	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Deletes the 3D texture vector specified from memory entirely.
	void texture3DVecDelete(texture3DVec* vec);