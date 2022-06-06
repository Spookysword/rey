#include "grey.h"
#include <stdlib.h>
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const char* colorVertexShader = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 aColor;\n"
"out vec4 color;\n"
"uniform vec2 viewport;\n"
"uniform vec3 offset;\n"
"void main() {\n"
"   gl_Position = vec4((aPos.x - viewport.x) / viewport.x - (offset.x / viewport.x), (aPos.y + viewport.y) / viewport.y + (offset.y / viewport.y), aPos.z, 1.0);\n"
"	color = aColor;\n"
"}\0";
const char* colorFragmentShader = "#version 330 core\n"
//"out vec4 FragColor;\n"
"in vec4 color;\n"
"void main() {\n"
"	gl_FragColor = color;\n"
"}\0";
const char* textureVertexShader = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec4 color;\n"
"out vec2 TexCoord;\n"
"uniform vec2 viewport;\n"
"uniform vec3 offset;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4((aPos.x - viewport.x) / viewport.x - (offset.x / viewport.x), (aPos.y + viewport.y) / viewport.y + (offset.y / viewport.y), aPos.z, 1.0);\n"
"	color = aColor;\n"
"	TexCoord = aTexCoord;\n"
"}\0";
const char* textureFragmentShader = "#version 330 core\n"
"in vec4 color;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D currentTexture;\n"
"void main()\n"
"{\n"
"	gl_FragColor = texture(currentTexture, TexCoord) * color;\n"
"}\0";
const char* fontVertexShader = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec4 color;\n"
"out vec2 TexCoord;\n"
"uniform vec2 viewport;\n"
"uniform vec3 offset;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4((aPos.x - viewport.x) / viewport.x - (offset.x / viewport.x), (aPos.y + viewport.y) / viewport.y + (offset.y / viewport.y), aPos.z, 1.0);\n"
"	color = aColor;\n"
"	TexCoord = aTexCoord;\n"
"}\0";
const char* fontFragmentShader = "#version 330 core\n"
"in vec4 color;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D currentTexture;\n"
"void main()\n"
"{\n"
"	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(currentTexture, TexCoord).r);\n"
"	gl_FragColor = color * sampled;\n"
"}\0";

Batch createBatch() {
	Batch batch;
	glGenVertexArrays(1, &batch.VAO);
	glGenBuffers(1, &batch.VBO);
	glBindVertexArray(batch.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, batch.VBO);
	batch.stack = 0;
	batch.verticeCount = 0;
	batch.triangles = floatVecCreate();
	batch.shapeVertices = intVecCreate();
	//glBufferData(GL_ARRAY_BUFFER, batch.triangles.size * sizeof(float), batch.triangles.data, GL_DYNAMIC_DRAW);
	
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return batch;
}
void addVertice(Batch* batch, float verts[7]) {
	floatVecPushBack7(&batch->triangles, verts);
	batch->verticeCount++;
	batch->stack++;
}
void addTriangle(Batch* batch, float verts[21]) {
	floatVecPushBack21(&batch->triangles, verts);
	batch->verticeCount += 3;
	batch->stack += 3;
}
void endShape(Batch* batch) {
	intVecPushBack(&batch->shapeVertices, batch->stack);
	batch->stack = 0;
}
void draw(Batch batch, GLenum type) {
	// This could be optimized by not using a vector here
	glBindVertexArray(batch.VAO);
	intVec first = intVecCreate();
	int tempInt = 0;
	for (int i = 0; i < batch.shapeVertices.size; i++) {
		intVecPushBack(&first, tempInt);
		tempInt += batch.shapeVertices.data[i];
	}
	glMultiDrawArrays(type, first.data, batch.shapeVertices.data, batch.shapeVertices.size);
	intVecDelete(&first);
}
void bindBatch(Batch batch) {
	glBindBuffer(GL_ARRAY_BUFFER, batch.VBO);
	glBufferData(GL_ARRAY_BUFFER, batch.triangles.size * sizeof(float), batch.triangles.data, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void flushBatch(Batch* batch) {
	floatVecClear(&batch->triangles);
	batch->verticeCount = 0;
	batch->stack = 0;
	intVecClear(&batch->shapeVertices);
}
void deleteBatch(Batch* batch) {
	floatVecDelete(&batch->triangles);
	intVecDelete(&batch->shapeVertices);
}

void addTextureVertice(TextureBatch* batch, float verts[9]) {
	floatVecPushBack9(&batch->triangles, verts);
	batch->verticeCount++;
	batch->stack++;
}
void addTextureTriangle(TextureBatch* batch, float verts[27]) {
	floatVecPushBack27(&batch->triangles, verts);
	batch->verticeCount+= 3;
	batch->stack+= 3;
}
void endTextureShape(TextureBatch* batch) {
	intVecPushBack(&batch->shapeVertices, batch->stack);
	batch->stack = 0;
}
void drawTextureBatch(TextureBatch batch, GLenum type) {
	glBindVertexArray(batch.VAO);
	intVec first = intVecCreate();
	int tempInt = 0;
	for (int i = 0; i < batch.shapeVertices.size; i++) {
		intVecPushBack(&first, tempInt);
		tempInt += batch.shapeVertices.data[i];
	}
	glMultiDrawArrays(type, first.data, batch.shapeVertices.data, batch.shapeVertices.size);
	intVecDelete(&first);
}
TextureBatch createTextureBatch(const char* filePath, int filter) {
	TextureBatch batch;
	glGenVertexArrays(1, &batch.VAO);
	glGenBuffers(1, &batch.VBO);
	glBindVertexArray(batch.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, batch.VBO);
	batch.stack = 0;
	batch.verticeCount = 0;
	batch.triangles = floatVecCreate();
	batch.shapeVertices = intVecCreate();

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

	glGenTextures(1, &batch.textureID);
	glBindTexture(GL_TEXTURE_2D, batch.textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

	int width, height, nrChannels;
	// No clue what "desired_channels" does here
	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 4);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		printf("Error generating texture located at '%s'\n", filePath);
	}
	stbi_image_free(data);

	return batch;
}
void bindTextureBatch(TextureBatch batch) {
	glBindBuffer(GL_ARRAY_BUFFER, batch.VBO);
	glBufferData(GL_ARRAY_BUFFER, batch.triangles.size * sizeof(float), batch.triangles.data, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void flushTextureBatch(TextureBatch* batch) {
	floatVecClear(&batch->triangles);
	batch->verticeCount = 0;
	batch->stack = 0;
	intVecClear(&batch->shapeVertices);
}
void deleteTextureBatch(TextureBatch* batch) {
	floatVecDelete(&batch->triangles);
	intVecDelete(&batch->shapeVertices);
}

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

textureVec textureVecCreate() {
	textureVec vec;
	vec.data = (TextureBatch*)calloc(0, sizeof(TextureBatch));
	vec.size = 0;
	vec.limit = 0;
	return vec;
}
void textureVecCheckSize(textureVec* vec) {
	if (vec->size + 1 > vec->limit) {
		TextureBatch* temp;
		vec->limit = vec->size * 2;
		temp = (TextureBatch*)realloc(vec->data, vec->limit * sizeof(TextureBatch));
		if (temp) { vec->data = temp; }
	}
}
void textureVecPushBack(textureVec* vec, TextureBatch num) {
	vec->size += 1;
	textureVecCheckSize(vec);
	vec->data[vec->size-1] = num;
}
void textureVecClear(textureVec* vec) {
	free(vec->data);
	vec->limit /= 2;
	vec->data = (TextureBatch*)calloc(vec->limit, sizeof(TextureBatch));
	vec->size = 0;
}
void textureVecDelete(textureVec* vec) {
	for (int i = 0; i < vec->size; i++) {
		deleteTextureBatch(&vec->data[i-1]);
	}
	free(vec->data);
	vec->size = 0;
	vec->limit = 0;
}


colorVec colorVecCreate() {
	colorVec vec;
	vec.data = (Color*)calloc(0, sizeof(Color));
	vec.size = 0;
	vec.limit = 0;
	return vec;
}
void colorVecCheckSize(colorVec* vec) {
	if (vec->size + 1 > vec->limit) {
		Color* temp;
		vec->limit = vec->size * 2;
		temp = (Color*)realloc(vec->data, vec->limit * sizeof(Color));
		if (temp) { vec->data = temp; }
	}
}
void colorVecPushBack(colorVec* vec, Color num) {
	vec->size += 1;
	colorVecCheckSize(vec);
	vec->data[vec->size - 1][0] = num[0];
	vec->data[vec->size - 1][1] = num[1];
	vec->data[vec->size - 1][2] = num[2];
	vec->data[vec->size - 1][3] = num[3];
}
void colorVecClear(colorVec* vec) {
	free(vec->data);
	vec->limit /= 2;
	vec->data = (Color*)calloc(vec->limit, sizeof(Color));
	vec->size = 0;
}
// This function kinda maybe doesn't exist yet possibly perhaps
void colorVecDelete(colorVec* vec) {
	for (int i = 0; i < vec->size; i++) {

	}
}


GLFWmonitor* getWindowMonitor(GLFWwindow* win) {
	int count;
	GLFWmonitor** monitors = glfwGetMonitors(&count);
	floatVec widths = floatVecCreate();
	for (int i = 0; i < count; i++) {
		if (i == 0) { floatVecPushBack(&widths, 0.0f); }
		else {
			const GLFWvidmode* modee = glfwGetVideoMode(monitors[i]);
			floatVecPushBack(&widths, modee->width + widths.data[widths.size - 1]);
		}
	}
	int x = 0, y = 0;
	glfwGetWindowPos(win, &x, &y);
	GLFWmonitor* returnMon = monitors[widths.size-1];
	for (int i = 0; i < widths.size; i++) {
		if (widths.size && x > widths.data[i] && x < widths.data[i+1]) {
			returnMon = monitors[i];
		}
	}
	floatVecDelete(&widths);
	return returnMon;
}

// Init/deinit funcs
void initGrey(unsigned int sampleRate) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, sampleRate);
	if (FT_Init_FreeType(&FT)) {
		printf("Failed to initialize FreeType!\n");
}
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
#ifdef _WIN32
	typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC)(int interval);
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if (wglSwapIntervalEXT) { wglSwapIntervalEXT(1); }
#else
	glfwSwapInterval(1);
#endif
}
void closeGrey() {
	FT_Done_FreeType(FT);
	glfwTerminate();
}

// Window funcs
void framebufferCallback(GLFWwindow * win, int width, int height) {
	glfwMakeContextCurrent(win);
	glViewport(0, 0, width, height);
}
Window createWindow(int width, int height, const char* title) {
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	Window win;
	win.windowHandle = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwSetWindowPos(win.windowHandle, (mode->width / 2) - (width / 2), (mode->height / 2) - (height / 2));
	glfwMakeContextCurrent(win.windowHandle);
	glfwSetFramebufferSizeCallback(win.windowHandle, framebufferCallback);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	win.title = title;
	win.shapeBatch = createBatch();
	win.deltaTime = 0.001f;
	win.width = width;
	win.height = height;
	win.fullscreen = FALSE;
	win.priorFullscreen = FALSE;
	win.prevWidth = width;
	win.prevHeight = height;
	win.textures = textureVecCreate();
	win.zmod = 0.0f;
	win.camera.x = 0.0f, win.camera.y = 0.0f, win.camera.z = 0.0f;
	win.framesPerSecond = 0.0f;
	win.fonts = fontVecCreate();

	/*if (FT_New_Face(FT, "resources/arial.ttf", 0, &win.arial.face)) {
		printf("Could load font!\n");
	}
	FT_Set_Pixel_Sizes(win.arial.face, 0, 45);
	win.arial.scale = 45;
	if (FT_Load_Char(win.arial.face, 'A', FT_LOAD_RENDER)) {
		printf("Couldn't load glyph!\n");
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // This line may cause problems
	for (unsigned char c = 0; c < 128; c++) {
		if (FT_Load_Char(win.arial.face, c, FT_LOAD_RENDER)) {
			printf("Failed to load particular glyph!\n");
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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, win.arial.face->glyph->bitmap.width, win.arial.face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, win.arial.face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		character.ID = testBatch.textureID;
		character.character = c;
		character.sizeX = win.arial.face->glyph->bitmap.width;
		character.sizeY = win.arial.face->glyph->bitmap.rows;
		character.bearingX = win.arial.face->glyph->bitmap_left;
		character.bearingY = win.arial.face->glyph->bitmap_top;
		character.advance = win.arial.face->glyph->advance.x;
		character.batch = testBatch;
		win.arial.characters[c] = character;
	}
	FT_Done_Face(win.arial.face);
	FT_Done_FreeType(FT);*/

	unsigned int w_colorVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(w_colorVertexShader, 1, &colorVertexShader, NULL);
	glCompileShader(w_colorVertexShader);
	unsigned int w_colorFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(w_colorFragmentShader, 1, &colorFragmentShader, NULL);
	glCompileShader(w_colorFragmentShader);
	win.colorShader = glCreateProgram();
	glAttachShader(win.colorShader, w_colorVertexShader);
	glAttachShader(win.colorShader, w_colorFragmentShader);
	glLinkProgram(win.colorShader);
	glDeleteShader(w_colorVertexShader);
	glDeleteShader(w_colorFragmentShader);

	// Prob should make this a function
	unsigned int w_textureVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(w_textureVertexShader, 1, &textureVertexShader, NULL);
	glCompileShader(w_textureVertexShader);
	unsigned int w_textureFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(w_textureFragmentShader, 1, &textureFragmentShader, NULL);
	glCompileShader(w_textureFragmentShader);
	win.textureShader = glCreateProgram();
	glAttachShader(win.textureShader, w_textureVertexShader);
	glAttachShader(win.textureShader, w_textureFragmentShader);
	glLinkProgram(win.textureShader);
	glDeleteShader(w_textureVertexShader);
	glDeleteShader(w_textureFragmentShader);

	// Def should make this a function
	unsigned int w_fontVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(w_fontVertexShader, 1, &fontVertexShader, NULL);
	glCompileShader(w_fontVertexShader);
	unsigned int w_fontFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(w_fontFragmentShader, 1, &fontFragmentShader, NULL);
	glCompileShader(w_fontFragmentShader);
	win.fontShader = glCreateProgram();
	glAttachShader(win.fontShader, w_fontVertexShader);
	glAttachShader(win.fontShader, w_fontFragmentShader);
	glLinkProgram(win.fontShader);
	glDeleteShader(w_fontVertexShader);
	glDeleteShader(w_fontFragmentShader);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return win;
}
void deleteWindow(Window* win) {
	deleteBatch(&win->shapeBatch);
	textureVecClear(&win->textures);
	textureVecDelete(&win->textures);
}
boolean shouldWindowClose(Window win) {
	return glfwWindowShouldClose(win.windowHandle);
}
Texture newTexture(Window* win, const char* path, int filter) {
	TextureBatch text = createTextureBatch(path, filter);
	textureVecPushBack(&win->textures, text);
	return win->textures.size-1;
}
FontID loadFont(Window* win, const char* filePath, float size) {
	/*
	if (FT_New_Face(FT, "resources/arial.ttf", 0, &win.arial.face)) {
		printf("Could load font!\n");
	}
	FT_Set_Pixel_Sizes(win.arial.face, 0, 45);
	win.arial.scale = 45;
	if (FT_Load_Char(win.arial.face, 'A', FT_LOAD_RENDER)) {
		printf("Couldn't load glyph!\n");
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // This line may cause problems
	for (unsigned char c = 0; c < 128; c++) {
		if (FT_Load_Char(win.arial.face, c, FT_LOAD_RENDER)) {
			printf("Failed to load particular glyph!\n");
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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, win.arial.face->glyph->bitmap.width, win.arial.face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, win.arial.face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		character.ID = testBatch.textureID;
		character.character = c;
		character.sizeX = win.arial.face->glyph->bitmap.width;
		character.sizeY = win.arial.face->glyph->bitmap.rows;
		character.bearingX = win.arial.face->glyph->bitmap_left;
		character.bearingY = win.arial.face->glyph->bitmap_top;
		character.advance = win.arial.face->glyph->advance.x;
		character.batch = testBatch;
		win.arial.characters[c] = character;
	}
	FT_Done_Face(win.arial.face);
	FT_Done_FreeType(FT);
	*/
	Font thisFont;
	if (FT_New_Face(FT, filePath, 0, &thisFont.face)) {
		printf("Could load font!\n");
	}
	FT_Set_Pixel_Sizes(thisFont.face, 0, size);
	thisFont.scale = size;
	if (FT_Load_Char(thisFont.face, 'A', FT_LOAD_RENDER)) {
		printf("Couldn't load glyph!\n");
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // This line may cause problems
	for (unsigned char c = 0; c < 128; c++) {
		if (FT_Load_Char(thisFont.face, c, FT_LOAD_RENDER)) {
			printf("Failed to load particular glyph!\n");
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
	fontVecPushBack(&win->fonts, thisFont);
	return win->fonts.size - 1;
}
void deleteFont(Window* win, FontID font) {
	for (int i = 0; i < 128; i++) {
		deleteTextureBatch(&win->fonts.data[font].characters[i].batch);
	}
}
void deleteTexture(Window* win, Texture texture) {
	deleteTextureBatch(&win->textures.data[texture]);
}
void updateWindow(Window* win) {
	flushBatch(&win->shapeBatch);
	for (int i = 0; i < win->textures.size; i++) {
		flushTextureBatch(&win->textures.data[i]);
	}
	for (int i = 0; i < win->fonts.size; i++) {
		for (int z = 0; z < 128; z++) {
			flushTextureBatch(&win->fonts.data[i].characters[z].batch);
		}
	}
	win->framesPerSecond = 1.0f / (glfwGetTime() - win->currentFrame);
	win->currentFrame = (float)glfwGetTime();
	win->deltaTime = win->currentFrame - win->lastFrame;
	win->lastFrame = win->currentFrame;
	win->zmod = 0.0f;
	if (win->deltaTime > 0.05f) { win->deltaTime = 0.05f; }
	glfwSetWindowTitle(win->windowHandle, win->title);
	glfwPollEvents();

	if (win->fullscreen != win->priorFullscreen) {
		win->priorFullscreen = win->fullscreen;
		if (win->fullscreen == TRUE) {
			glfwGetWindowPos(win->windowHandle, &win->prevX, &win->prevY);
			glfwGetWindowSize(win->windowHandle, &win->prevWidth, &win->prevHeight);
			GLFWmonitor* currentMonitor = getWindowMonitor(win->windowHandle);
			const GLFWvidmode* mode = glfwGetVideoMode(currentMonitor);
			glfwSetWindowMonitor(win->windowHandle, currentMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		}
		else {
			const GLFWvidmode* mode = glfwGetVideoMode(getWindowMonitor(win->windowHandle));
			glfwSetWindowMonitor(win->windowHandle, NULL, win->prevX, win->prevY, win->prevWidth, win->prevHeight, mode->refreshRate);
		}
	}
	
	glfwGetWindowSize(win->windowHandle, &win->width, &win->height);
	for (int i = 0; i < sizeof(win->keys) / sizeof(win->keys[0]); i++) {
		win->keys[i] = glfwGetKey(win->windowHandle, i);
		if (win->keys[i] == GLFW_PRESS && win->tempKeys[i] == GLFW_PRESS) {
			win->tempKeys[i] = GLFW_RELEASE;
			win->tempKeysCheck[i] = 1;
		}
		else if (win->keys[i] == GLFW_RELEASE) {
			win->tempKeys[i] = GLFW_RELEASE;
			win->tempKeysCheck[i] = 0;
		}
		else if (win->tempKeysCheck[i] == 0) {
			win->tempKeys[i] = win->keys[i];
		}
	}
}
void renderWindow(Window win) {
	glfwMakeContextCurrent(win.windowHandle);
	glfwSetWindowSize(win.windowHandle, win.width, win.height);
	
	bindBatch(win.shapeBatch);
	glUseProgram(win.colorShader);
	glUniform2f(glGetUniformLocation(win.colorShader, "viewport"), (GLfloat)win.width/2, (GLfloat)win.height/2);
	glUniform3f(glGetUniformLocation(win.colorShader, "offset"), win.camera.x, win.camera.y, win.camera.z);
	
	draw(win.shapeBatch, GL_TRIANGLE_FAN);
	
	glUseProgram(win.textureShader);
	glUniform2f(glGetUniformLocation(win.textureShader, "viewport"), (GLfloat)win.width / 2, (GLfloat)win.height / 2);
	glUniform3f(glGetUniformLocation(win.textureShader, "offset"), win.camera.x, win.camera.y, win.camera.z);
	for (int i = 0; i < win.textures.size; i++) {
		bindTextureBatch(win.textures.data[i]);
		glBindTexture(GL_TEXTURE_2D, win.textures.data[i].textureID);
		glBindVertexArray(win.textures.data[i].VAO);
		drawTextureBatch(win.textures.data[i], GL_TRIANGLE_FAN);
	}

	/*glUseProgram(win.fontShader);
	glUniform2f(glGetUniformLocation(win.fontShader, "viewport"), (GLfloat)win.width / 2, (GLfloat)win.height / 2);
	glUniform3f(glGetUniformLocation(win.fontShader, "offset"), win.camera.x, win.camera.y, win.camera.z);
	for (int i = 0; i < 128; i++) {
		bindTextureBatch(win.arial.characters[i].batch);
		glBindTexture(GL_TEXTURE_2D, win.arial.characters[i].batch.textureID);
		glBindVertexArray(win.arial.characters[i].batch.VAO);
		drawTextureBatch(win.arial.characters[i].batch, GL_TRIANGLE_FAN);
	}*/
	glUseProgram(win.fontShader);
	glUniform2f(glGetUniformLocation(win.fontShader, "viewport"), (GLfloat)win.width / 2, (GLfloat)win.height / 2);
	glUniform3f(glGetUniformLocation(win.fontShader, "offset"), win.camera.x, win.camera.y, win.camera.z);
	for (int i = 0; i < win.fonts.size; i++) {
		for (int z = 0; z < 128; z++) {
			bindTextureBatch(win.fonts.data[i].characters[z].batch);
			glBindTexture(GL_TEXTURE_2D, win.fonts.data[i].characters[z].batch.textureID);
			glBindVertexArray(win.fonts.data[i].characters[z].batch.VAO);
			drawTextureBatch(win.fonts.data[i].characters[z].batch, GL_TRIANGLE_FAN);
		}
	}

	glfwSwapBuffers(win.windowHandle);
}
void closeWindow(Window win) {
	glfwSetWindowShouldClose(win.windowHandle, GLFW_TRUE);
}
void setWindowFlag(Window win, uint32_t flag, boolean state) {
	glfwSetWindowAttrib(win.windowHandle, flag, state);
}

// Key input
boolean isKeyDown(Window win, int key) {
	if (key < sizeof(win.keys) / sizeof(win.keys[0])) {
		return win.keys[key];
	}
	return 0;
}
boolean isKeyPressed(Window win, int key) {
	if (key < sizeof(win.tempKeys) / sizeof(win.tempKeys[0])) {
		return win.tempKeys[key];
	}
	return 0;
}

// Draw funcs
void clearWindowBackground(Window win, Color color) {
	glfwMakeContextCurrent(win.windowHandle);
	glClearColor((float)color[0] / 255, (float)color[1] / 255, (float)color[2] / 255, (float)color[3] / 255);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void setWireframeMode(Window win, boolean state) {
	glfwMakeContextCurrent(win.windowHandle);
	if (state) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
void drawTriangle(Window* win, float x1, float y1, float x2, float y2, float x3, float y3, Color color) {
	float passIn1[21] = {
		x1, -y1, win->zmod, (float)color[0]/255, (float)color[1]/255, (float)color[2]/255, (float)color[3]/255,
		x2, -y2, win->zmod, (float)color[0]/255, (float)color[1]/255, (float)color[2]/255, (float)color[3]/255,
		x3, -y3, win->zmod, (float)color[0]/255, (float)color[1]/255, (float)color[2]/255, (float)color[3]/255
	};
	addTriangle(&win->shapeBatch, passIn1);
	endShape(&win->shapeBatch);
	win->zmod -= 0.000001f;
}
void drawRectangle(Window* win, float x, float y, float width, float height, float rotation, Color color) {
	float r = (float)color[0] / 255, g = (float)color[1] / 255, b = (float)color[2] / 255, a = (float)color[3] / 255;
	y = -y;
	if (rotation == 0.0f || (int)rotation % 360 == 0) {
		float passIn1[21] = {
			x, y, win->zmod, r, g, b, a,
			x, y - height, win->zmod, r, g, b, a,
			x + width, y - height, win->zmod, r, g, b, a
		};
		float passIn2[7] = {
			x + width, y, win->zmod, r, g, b, a
		};
		addTriangle(&win->shapeBatch, passIn1);
		addVertice(&win->shapeBatch, passIn2);
		endShape(&win->shapeBatch);
	}
	else {
		rotation = -rotation * (PI / 180);
		float a1 = sqrt(pow((width / 2), 2) + pow((height / 2), 2));
		float r0 = asin(((height / 2) * (sin(PI / 2))) / a1), r1 = r0 + rotation, r2 = -r0 + rotation, r3 = r1 - PI, r4 = r2 - PI;
		float c1 = x + width / 2, c2 = y - height / 2;
		float passIn1[21] = {
			a1 * cos(r1) + c1, a1 * sin(r1) + c2, win->zmod, r, g, b, a,
			a1 * cos(r2) + c1, a1 * sin(r2) + c2, win->zmod, r, g, b, a,
			a1 * cos(r3) + c1, a1 * sin(r3) + c2, win->zmod, r, g, b, a
		};
		float passIn2[7] = {
			a1 * cos(r4) + c1, a1 * sin(r4) + c2, win->zmod, r, g, b, a
		};
		addTriangle(&win->shapeBatch, passIn1);
		addVertice(&win->shapeBatch, passIn2);
		endShape(&win->shapeBatch);
	}
	win->zmod -= 0.000001f;
}
void drawTexture(Window* win, Texture texture, float x, float y, float width, float height, float rotation, Color color) {
	float r = (float)color[0] / 255, g = (float)color[1] / 255, b = (float)color[2] / 255, a = (float)color[3] / 255;
	y = -y;
	if (rotation == 0.0f || (int)rotation % 360 == 0) {
		float passIn1[27] = {
			x, y, win->zmod, r, g, b, a, 0.0f, 1.0f,
			x, y - height, win->zmod, r, g, b, a, 0.0f, 0.0f,
			x + width, y - height, win->zmod, r, g, b, a, 1.0f, 0.0f
		};
		float passIn2[9] = {
			x + width, y, win->zmod, r, g, b, a, 1.0f, 1.0f
		};
		addTextureTriangle(&win->textures.data[texture], passIn1);
		addTextureVertice(&win->textures.data[texture], passIn2);
		endTextureShape(&win->textures.data[texture]);
	}
	else {
		float pi = 3.1415926535897932384626433;
		rotation = -rotation * (pi / 180);
		float a1 = sqrt(pow((width / 2), 2) + pow((height / 2), 2));
		float r0 = asin(((height / 2) * (sin(pi / 2))) / a1), r1 = r0 + rotation, r2 = -r0 + rotation, r3 = r1 - pi, r4 = r2 - pi;
		float c1 = x + width / 2, c2 = y - height / 2;
		float passIn1[27] = {
			a1 * cos(r1) + c1, a1 * sin(r1) + c2, win->zmod, r, g, b, a, 0.0f, 1.0f,
			a1 * cos(r2) + c1, a1 * sin(r2) + c2, win->zmod, r, g, b, a, 0.0f, 0.0f,
			a1 * cos(r3) + c1, a1 * sin(r3) + c2, win->zmod, r, g, b, a, 1.0f, 0.0f
		};
		float passIn2[9] = {
			a1 * cos(r4) + c1, a1 * sin(r4) + c2, win->zmod, r, g, b, a, 1.0f, 1.0f
		};
		addTextureTriangle(&win->textures.data[texture], passIn1);
		addTextureVertice(&win->textures.data[texture], passIn2);
		endTextureShape(&win->textures.data[texture]);
	}
	win->zmod -= 0.000001f;
}

void drawCircle(Window* win, float x, float y, float radius, Color color) {
	float cR, cG, cB, cA; cR = (float)(color[0]) / 255; cG = (float)(color[1]) / 255; cB = (float)(color[2]) / 255; cA = (float)(color[3]) / 255;
	y = -y;
	float pi2 = 2 * PI;
	int amount = CIRCLE_ACCURACY;
	float passIn[7] = { x, y, win->zmod, cR, cG, cB, cA };
	addVertice(&win->shapeBatch, passIn);
	for (int i = 0; i <= amount; i++) {
		float passIn2[7] = { x + (radius * cos(i * pi2 / amount)), y + (radius * sin(i * pi2 / amount)), win->zmod, cR, cG, cB, cA };
		addVertice(&win->shapeBatch, passIn2);
	}
	endShape(&win->shapeBatch);

	win->zmod -= 0.000001f;
}

void drawRoundedRect(Window* win, float x, float y, float width, float height, float radius, float rotation, Color color) {
	float cR, cG, cB, cA; cR = (float)(color[0]) / 255; cG = (float)(color[1]) / 255; cB = (float)(color[2]) / 255; cA = (float)(color[3]) / 255;
	float x1 = x;
	float y1 = y;
	y1 += height;
	y1 -= y1 * 2;
	float rot = rotation * (PI / 180);
	float c1 = x1 + width / 2;
	float c2 = y1 + height / 2;

	float a = x1 + radius;
	float b = y1;
	float c = x1 + width - radius;
	float d = y1 + height;
	float passIn0[21] = { rotateX(a,b,c1,c2,rot),rotateY(a,b,c1,c2,rot),win->zmod,cR,cG,cB,cA, rotateX(a,d,c1,c2,rot),rotateY(a,d,c1,c2,rot),win->zmod,cR,cG,cB,cA, rotateX(c,d,c1,c2,rot),rotateY(c,d,c1,c2,rot),win->zmod,cR,cG,cB,cA };
	float passIn1[7] = { rotateX(c,b,c1,c2,rot),rotateY(c,b,c1,c2,rot),win->zmod,cR,cG,cB,cA };
	addTriangle(&win->shapeBatch, passIn0);
	addVertice(&win->shapeBatch, passIn1);
	endShape(&win->shapeBatch);

	a = x1;
	b = y1 + radius;
	c = x1 + width;
	d = y1 + height - radius;
	float passIn2[21] = { rotateX(a,b,c1,c2,rot),rotateY(a,b,c1,c2,rot),win->zmod,cR,cG,cB,cA, rotateX(a,d,c1,c2,rot),rotateY(a,d,c1,c2,rot),win->zmod,cR,cG,cB,cA, rotateX(c,d,c1,c2,rot),rotateY(c,d,c1,c2,rot),win->zmod,cR,cG,cB,cA };
	float passIn3[7] = { rotateX(c,b,c1,c2,rot),rotateY(c,b,c1,c2,rot),win->zmod,cR,cG,cB,cA };
	addTriangle(&win->shapeBatch, passIn2);
	addVertice(&win->shapeBatch, passIn3);
	endShape(&win->shapeBatch);


	float xii = x1 + radius;
	float yii = y1 + radius;
	float xi = rotateX(xii, yii,c1,c2,rot);
	float yi = rotateY(xii, yii,c1,c2,rot);
	float pi2 = 2 * PI;
	int amount = CIRCLE_ACCURACY;
	float passIn4[7] = { xi, yi, win->zmod, cR, cG, cB, cA };
	addVertice(&win->shapeBatch, passIn4);
	for (int i = 0; i <= amount; i++) {
		float passIn5[7] = { xi + (radius * cos(i * pi2 / amount)), yi + (radius * sin(i * pi2 / amount)), win->zmod, cR, cG, cB, cA };
		addVertice(&win->shapeBatch, passIn5);
	}
	endShape(&win->shapeBatch);

	xii = x1 + width - radius;
	yii = y1 + radius;
	xi = rotateX(xii, yii, c1, c2, rot);
	yi = rotateY(xii, yii, c1, c2, rot);
	float passIn6[7] = { xi, yi, win->zmod, cR, cG, cB, cA };
	addVertice(&win->shapeBatch, passIn6);
	for (int i = 0; i <= amount; i++) {
		float passIn7[7] = { xi + (radius * cos(i * pi2 / amount)), yi + (radius * sin(i * pi2 / amount)), win->zmod, cR, cG, cB, cA };
		addVertice(&win->shapeBatch, passIn7);
	}
	endShape(&win->shapeBatch);

	xii = x1 + width - radius;
	yii = y1 + height - radius;
	xi = rotateX(xii, yii, c1, c2, rot);
	yi = rotateY(xii, yii, c1, c2, rot);
	float passIn8[7] = { xi, yi, win->zmod, cR, cG, cB, cA };
	addVertice(&win->shapeBatch, passIn8);
	for (int i = 0; i <= amount; i++) {
		float passIn9[7] = { xi + (radius * cos(i * pi2 / amount)), yi + (radius * sin(i * pi2 / amount)), win->zmod, cR, cG, cB, cA };
		addVertice(&win->shapeBatch, passIn9);
	}
	endShape(&win->shapeBatch);

	xii = x1 + radius;
	yii = y1 + height - radius;
	xi = rotateX(xii, yii, c1, c2, rot);
	yi = rotateY(xii, yii, c1, c2, rot);
	float passIn10[7] = { xi, yi, win->zmod, cR, cG, cB, cA };
	addVertice(&win->shapeBatch, passIn10);
	for (int i = 0; i <= amount; i++) {
		float passIn11[7] = { xi + (radius * cos(i * pi2 / amount)), yi + (radius * sin(i * pi2 / amount)), win->zmod, cR, cG, cB, cA };
		addVertice(&win->shapeBatch, passIn11);
	}
	endShape(&win->shapeBatch);

	win->zmod -= 0.000001f;
}
void drawText(Window* win, const char* text, FontID font, float x, float y, float scale, Color color) {
	float r = (float)color[0] / 255, g = (float)color[1] / 255, b = (float)color[2] / 255, a = (float)color[3] / 255;
	for (int i = 0; text[i] != '\0'; i++) {
		Character c = win->fonts.data[font].characters[text[i]];
		float xpos = x + c.bearingX * scale;
		float ypos = y + (c.sizeY - c.bearingY) * scale;
		float w = c.sizeX * scale, h = c.sizeY * scale;
		float passIn1[27] = {
			xpos, -(ypos), win->zmod, r, g, b, a, 0.0f, 1.0f,
			xpos, -(ypos - h), win->zmod, r, g, b, a, 0.0f, 0.0f,
			xpos + w, -(ypos - h), win->zmod, r, g, b, a, 1.0f, 0.0f
		};
		float passIn2[9] = {
			xpos + w, -(ypos), win->zmod, r, g, b, a, 1.0f, 1.0f
		};
		addTextureTriangle(&win->fonts.data[font].characters[text[i]].batch, passIn1);
		addTextureVertice(&win->fonts.data[font].characters[text[i]].batch, passIn2);
		endTextureShape(&win->fonts.data[font].characters[text[i]].batch);
		x += (c.advance >> 6) * scale;
		win->zmod -= 0.000001f;
	}
}
void drawPolygon(Window* win, float* xs, float* ys, int points, Color color) {
	float r = (float)color[0] / 255, g = (float)color[1] / 255, b = (float)color[2] / 255, a = (float)color[3] / 255;
	for (int i = 0; i < points; i++) {
		float passIn[7] = { xs[i], -ys[i], win->zmod, r, g, b, a };
		addVertice(&win->shapeBatch, passIn);
	}
	endShape(&win->shapeBatch);
}
void drawAdvancedRect(Window* win, float x, float y, float width, float height, float rotation, Color color1, Color color2, Color color3, Color color4) {
	float cr1 = (float)color1[0] / 255, cg1 = (float)color1[1] / 255, cb1 = (float)color1[2] / 255, ca1 = (float)color1[3] / 255;
	float cr2 = (float)color2[0] / 255, cg2 = (float)color2[1] / 255, cb2 = (float)color2[2] / 255, ca2 = (float)color2[3] / 255;
	float cr3 = (float)color3[0] / 255, cg3 = (float)color3[1] / 255, cb3 = (float)color3[2] / 255, ca3 = (float)color3[3] / 255;
	float cr4 = (float)color4[0] / 255, cg4 = (float)color4[1] / 255, cb4 = (float)color4[2] / 255, ca4 = (float)color4[3] / 255;
	y = -y;

	rotation = -rotation * (PI / 180);
	float a1 = sqrt(pow((width / 2), 2) + pow((height / 2), 2));
	float r0 = asin(((height / 2) * (sin(PI / 2))) / a1), r1 = r0 + rotation, r2 = -r0 + rotation, r3 = r1 - PI, r4 = r2 - PI;
	float c1 = x + width / 2, c2 = y - height / 2;
	float passIn1[21] = {
		a1 * cos(r1) + c1, a1 * sin(r1) + c2, win->zmod, cr1, cg1, cb1, ca1,
		a1 * cos(r2) + c1, a1 * sin(r2) + c2, win->zmod, cr2, cg2, cb2, ca2,
		a1 * cos(r3) + c1, a1 * sin(r3) + c2, win->zmod, cr3, cg3, cb3, ca3
	};
	float passIn2[7] = {
		a1 * cos(r4) + c1, a1 * sin(r4) + c2, win->zmod, cr4, cg4, cb4, ca4
	};
	addTriangle(&win->shapeBatch, passIn1);
	addVertice(&win->shapeBatch, passIn2);
	endShape(&win->shapeBatch);

	win->zmod -= 0.000001f;
}
void drawAdvancedTriangle(Window* win, float x1, float y1, float x2, float y2, float x3, float y3, Color color1, Color color2, Color color3) {
	float passIn1[21] = {
		x1, -y1, win->zmod, (float)color1[0] / 255, (float)color1[1] / 255, (float)color1[2] / 255, (float)color1[3] / 255,
		x2, -y2, win->zmod, (float)color2[0] / 255, (float)color2[1] / 255, (float)color2[2] / 255, (float)color2[3] / 255,
		x3, -y3, win->zmod, (float)color3[0] / 255, (float)color3[1] / 255, (float)color3[2] / 255, (float)color3[3] / 255
	};
	addTriangle(&win->shapeBatch, passIn1);
	endShape(&win->shapeBatch);
	win->zmod -= 0.000001f;
}