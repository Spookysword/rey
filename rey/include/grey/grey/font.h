#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

#include "grey/grey/texture_batch.h"

typedef unsigned int FontID;

	extern FT_Library FT;

	struct Character {
		unsigned int ID;
		char character;
		float sizeX, sizeY;
		float bearingX, bearingY;
		unsigned int advance;
		TextureBatch batch;
	};
	typedef struct Character Character;
	struct Font {
		FT_Face face;
		Character characters[128];
		float scale;
	};
	typedef struct Font Font;
	struct fontVec {
		Font* data;
		int size;
		int limit;
	};
	typedef struct fontVec fontVec;
	fontVec fontVecCreate();
	void fontVecCheckSize(fontVec* vec);
	void fontVecPushBack(fontVec* vec, Font num);
	void fontVecClear(fontVec* vec);
	void fontVecDelete(fontVec* vec);