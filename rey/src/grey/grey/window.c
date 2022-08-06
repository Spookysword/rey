#include "grey/grey/window.h"
FontID loadFont(Window* win, const char* filePath, float size) {
	Font thisFont;
	if (FT_New_Face(FT, filePath, 0, &thisFont.face)) {
		printf("Could load font at path '%s'!\n", filePath);
		return -1;
	}
	FT_Set_Pixel_Sizes(thisFont.face, 0, size);
	thisFont.scale = size;
	if (FT_Load_Char(thisFont.face, 'A', FT_LOAD_RENDER)) {
		printf("Couldn't load glyph A!\n");
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // This line may cause problems
	for (unsigned char c = 0; c < 128; c++) {
		if (FT_Load_Char(thisFont.face, c, FT_LOAD_RENDER)) {
			printf("Failed to load glyph %c!\n", c);
		}
		TextureBatch testBatch;
		Character character;
		glGenVertexArrays(1, &testBatch.VAO);
		glGenBuffers(1, &testBatch.VBO);
		glBindVertexArray(testBatch.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, testBatch.VBO);
		testBatch.stack = 0;
		testBatch.verticeCount = 0;
		testBatch.triangles = floatVecCreate();
		testBatch.shapeVertices = intVecCreate();

		// Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// Color
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// Texture coords
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glGenTextures(1, &testBatch.textureID);
		glBindTexture(GL_TEXTURE_2D, testBatch.textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, thisFont.face->glyph->bitmap.width, thisFont.face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, thisFont.face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		character.ID = testBatch.textureID;
		character.character = c;
		character.sizeX = thisFont.face->glyph->bitmap.width;
		character.sizeY = thisFont.face->glyph->bitmap.rows;
		character.bearingX = thisFont.face->glyph->bitmap_left;
		character.bearingY = thisFont.face->glyph->bitmap_top;
		character.advance = thisFont.face->glyph->advance.x;
		character.batch = testBatch;
		thisFont.characters[c] = character;
	}
	FT_Done_Face(thisFont.face);
	//fontVecPushBack(&win->shaders.data[win->currentShader].fonts, thisFont);
	for (int i = 0; i < win->shaders.size; i++) {
		fontVecPushBack(&win->shaders.data[i].fonts, thisFont);
	}
	return win->shaders.data[win->currentShader].fonts.size - 1;
}
void deleteFont(Window* win, FontID font) {
	if (font == -1) { return; }
	/*for (int i = 0; i < 128; i++) {
		deleteTextureBatch(&win->shaders.data[win->currentShader].fonts.data[font].characters[i].batch);
		glDeleteTextures(1, &win->shaders.data[win->currentShader].fonts.data[font].characters[i].ID);
	}*/
	for (int i = 0; i < win->shaders.size; i++) {
		for (int z = 0; z < 128; z++) {
			deleteTextureBatch(&win->shaders.data[i].fonts.data[font].characters[z].batch);
		}
	}
	for (int i = 0; i < 128; i++) {
		glDeleteTextures(1, &win->shaders.data[win->currentShader].fonts.data[font].characters[i].ID);
	}
}