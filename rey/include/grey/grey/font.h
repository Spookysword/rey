#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

#include "grey/grey/texture_batch.h"

#ifdef __cplusplus
namespace grey {
#endif
// The index of a font.
typedef unsigned int FontID;

	extern FT_Library FT;

	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. The data of a single font's character.
	struct Character {
		unsigned int ID;
		char character;
		float sizeX, sizeY;
		float bearingX, bearingY;
		unsigned int advance;
		TextureBatch batch;
	};
	typedef struct Character Character;

	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. The data of an entire font.
	struct Font {
		FT_Face face;
		Character characters[128];
		float scale;
	};
	typedef struct Font Font;

	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. A vector of fonts.
	struct fontVec {
		Font* data;
		int size;
		int limit;
	};
	typedef struct fontVec fontVec;

	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Creates and returns a valid font vector.
	fontVec fontVecCreate();
	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Checks to see if the size of the font vector is overflowing and adjusts appropriately.
	void fontVecCheckSize(fontVec* vec);
	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Pushes back a font into the font vector.
	void fontVecPushBack(fontVec* vec, Font num);
	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Clears all of the fonts inside the font vector.
	void fontVecClear(fontVec* vec);
	// SHOULDN'T BE USED UNLESS YOU'RE MODIFYING GREY CODE DIRECTLY. Deletes all of the fonts and memory the font vector is using.
	void fontVecDelete(fontVec* vec);
#ifdef __cplusplus
}
#endif
