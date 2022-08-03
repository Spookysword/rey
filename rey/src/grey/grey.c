#include "grey/grey.h"
#include <stdlib.h>
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

FT_Library FT;

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
"	if (texture(currentTexture, TexCoord).a < 0.5) discard;\n"
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

const char* texture3DVertexShader = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"layout (location = 3) in vec3 aNormal;\n"
"out vec4 color;\n"
"out vec2 TexCoord;\n"
"out vec3 normal;\n"
"out vec3 worldPos;\n"
"uniform vec3 offset;\n"
"uniform mat4 transformProj;\n"
"uniform mat4 transform;\n"
"void main() {\n"
"   gl_Position = transformProj*vec4(aPos.x - offset.x, aPos.y + offset.y, aPos.z, 1.0);\n"
"	color = aColor;\n"
"	TexCoord = aTexCoord;\n"
"	normal = (transform * vec4(aNormal, 0.0)).xyz;\n"
"	worldPos = (transform * vec4(aPos, 1.0)).xyz;\n"
"}\0";
const char* texture3DFragmentShader = "#version 330 core\n"
//"out vec4 FragColor;\n"
"in vec4 color;\n"
"in vec2 TexCoord;\n"
"in vec3 normal;\n"
"in vec3 worldPos;\n"
"uniform sampler2D currentTexture;\n"
"void main() {\n"
"	vec3 viewPos = vec3(0.);\n"
"	vec3 lightPos = vec3(2., 4., -5.);\n"
"	vec3 lightColor = vec3(1.0, 1.0, 0.9);\n"
"	float ambientStrength = 0.13;\n"
"	vec3 ambient = ambientStrength * lightColor;\n"
"	vec3 norm = normalize(normal);\n"
"	vec3 lightDir = normalize(lightPos - worldPos);\n" // worldPos might be gl_FragPosition
"	float diff = max(dot(norm, lightDir), -0.03);\n"
"	vec3 diffuse = diff * lightColor;\n"
"	float specularStrength = 1.5;\n"
"	vec3 viewDir = normalize(viewPos - worldPos);\n" // Same Here
"	vec3 reflectDir = reflect(-lightDir, norm);\n"
"	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);\n"
"	vec3 specular = specularStrength * spec * lightColor;\n"
"	\n"
"	\n"
"	gl_FragColor = vec4((specular+ambient+diffuse)*(color*texture(currentTexture, TexCoord)).xyz, 1.0f);\n"
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
	batch->verticeCount += 3;
	batch->stack += 3;
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
// https://stackoverflow.com/a/57643613
// void stbi_kyon_horizontal_flip(void *image, int w, int h, int bytes_per_pixel)
// {
//   size_t line_bytes = (size_t)w * bytes_per_pixel;
//   stbi_uc* temp = calloc(line_bytes, sizeof(stbi_uc));
//   stbi_uc *bytes = (stbi_uc *)image;
//   int lpos, rpos;
//   for (int col = 0; col < h; col++) {
//     stbi_uc *line = bytes + col * line_bytes;
//     memcpy(&temp, line, line_bytes);
//     for (int row = 0; row < w; row++) {
//       lpos = row * bytes_per_pixel;
//       rpos = line_bytes - row * bytes_per_pixel - 1;
//       line[lpos] = temp[rpos - 3];
//       line[lpos + 1] = temp[rpos - 2];
//       line[lpos + 2] = temp[rpos - 1];
//       line[lpos + 3] = temp[rpos];
//     }
//   }
// }

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
	//stbi_kyon_horizontal_flip(data, width, height, 4);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
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


void add3DVertice(Batch3D* batch, float verts[12]) {
	floatVecPushBack12(&batch->triangles, verts);
	batch->verticeCount++;
	batch->stack++;
}
void add3DTriangle(Batch3D* batch, float verts[36]) {
	floatVecPushBack36(&batch->triangles, verts);
	batch->verticeCount += 3;
	batch->stack += 3;
}
void end3DShape(Batch3D* batch) {
	intVecPushBack(&batch->shapeVertices, batch->stack);
	batch->stack = 0;
}

void draw3DBatch(Batch3D batch, GLenum type) {
	glBindVertexArray(batch.VAO);
	intVec first = intVecCreate();
	int tempInt = 0;
	for (int i = 0; i < batch.shapeVertices.size; i++) {
		intVecPushBack(&first, tempInt);
		tempInt += batch.shapeVertices.data[i];
	}
	//for (int i = 0; i < batch.triangles.size; i += 12) {
	//	printf("pos: %f %f %f, color: %f %f %f %f, tex: %f %f, normal: %f %f %f\n",
	//		batch.triangles.data[i], batch.triangles.data[i + 1], batch.triangles.data[i + 2],
	//		batch.triangles.data[i + 3], batch.triangles.data[i + 4], batch.triangles.data[i + 5], batch.triangles.data[i + 6],
	//		batch.triangles.data[i + 7], batch.triangles.data[i + 8],
	//		batch.triangles.data[i + 9], batch.triangles.data[i + 10], batch.triangles.data[i + 11]);
	//}
	//printf("\n\n");
	glMultiDrawArrays(type, first.data, batch.shapeVertices.data, batch.shapeVertices.size);
	intVecDelete(&first);
}
Batch3D create3DBatch(const char* filePath, int filter) {
	Batch3D batch;
	glGenVertexArrays(1, &batch.VAO);
	glGenBuffers(1, &batch.VBO);

	glBindVertexArray(batch.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, batch.VBO);
	batch.stack = 0;
	batch.verticeCount = 0;
	batch.triangles = floatVecCreate();
	batch.shapeVertices = intVecCreate();

	// Position x y z
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color r g b a
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Texture coords u v
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// Normal nx ny nz
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);

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
	}
	else {
		printf("Error generating texture located at '%s'\n", filePath);
	}
	//stbi_image_free(data);

	return batch;
}
Batch3D createBlank3DBatch() {
	Batch3D batch;
	glGenVertexArrays(1, &batch.VAO);
	glGenBuffers(1, &batch.VBO);

	glBindVertexArray(batch.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, batch.VBO);
	batch.stack = 0;
	batch.verticeCount = 0;
	batch.triangles = floatVecCreate();
	batch.shapeVertices = intVecCreate();

	// Position x y z
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color r g b a
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Texture coords u v
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// Normal nx ny nz
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenTextures(1, &batch.textureID);
	glBindTexture(GL_TEXTURE_2D, batch.textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FILTER_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FILTER_LINEAR);
	
	int width, height, nrChannels;
	// No clue what "desired_channels" does here
	unsigned char* data = "\xff\xff\xff\xff";
	if (data) {

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		printf("Ruh roh!\n");
	}
	return batch;
}
void bind3DBatch(Batch3D batch) {
	glBindBuffer(GL_ARRAY_BUFFER, batch.VBO);
	glBufferData(GL_ARRAY_BUFFER, batch.triangles.size * sizeof(float), batch.triangles.data, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void flush3DBatch(Batch3D* batch) {
	floatVecClear(&batch->triangles);
	batch->verticeCount = 0;
	batch->stack = 0;
	intVecClear(&batch->shapeVertices);
}
void delete3DBatch(Batch3D* batch) {
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
CustomShaderVec CustomShaderVecCreate() {
	CustomShaderVec vec;
	vec.data = (CustomShader*)calloc(0, sizeof(CustomShader));
	vec.size = 0;
	vec.limit = 0;
	return vec;
}
void CustomShaderVecCheckSize(CustomShaderVec* vec) {
	if (vec->size + 1 > vec->limit) {
		CustomShader* temp;
		vec->limit = vec->size * 2;
		temp = (CustomShader*)realloc(vec->data, vec->limit * sizeof(CustomShader));
		if (temp) { vec->data = temp; }
	}
}
void CustomShaderVecPushBack(CustomShaderVec* vec, CustomShader num) {
	vec->size += 1;
	CustomShaderVecCheckSize(vec);
	vec->data[vec->size - 1] = num;
}
void CustomShaderVecClear(CustomShaderVec* vec) {
	free(vec->data);
	vec->limit /= 2;
	vec->data = (CustomShader*)calloc(vec->limit, sizeof(CustomShader));
	vec->size = 0;
}
// This dont do anything rn
void CustomShaderVecDelete(CustomShaderVec* vec) {

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
	vec->data[vec->size - 1] = num;
}
void textureVecClear(textureVec* vec) {
	free(vec->data);
	vec->limit /= 2;
	vec->data = (TextureBatch*)calloc(vec->limit, sizeof(TextureBatch));
	vec->size = 0;
}
void textureVecDelete(textureVec* vec) {
	for (int i = 0; i < vec->size; i++) {
		deleteTextureBatch(&vec->data[i - 1]);
		glDeleteTextures(1, &vec->data[i - 1].textureID);
	}
	free(vec->data);
	vec->size = 0;
	vec->limit = 0;
}

texture3DVec texture3DVecCreate() {
	texture3DVec vec;
	vec.data = (Batch3D*)calloc(0, sizeof(Batch3D));
	vec.size = 0;
	vec.limit = 0;
	return vec;
}
void texture3DVecCheckSize(texture3DVec* vec) {
	if (vec->size + 1 > vec->limit) {
		Batch3D* temp;
		vec->limit = vec->size * 2;
		temp = (Batch3D*)realloc(vec->data, vec->limit * sizeof(Batch3D));
		if (temp) { vec->data = temp; }
	}
}
void texture3DVecPushBack(texture3DVec* vec, Batch3D num) {
	vec->size += 1;
	textureVecCheckSize(vec);
	vec->data[vec->size - 1] = num;
}
void texture3DVecClear(texture3DVec* vec) {
	free(vec->data);
	vec->limit /= 2;
	vec->data = (Batch3D*)calloc(vec->limit, sizeof(Batch3D));
	vec->size = 0;
}
void texture3DVecDelete(texture3DVec* vec) {
	for (int i = 0; i < vec->size; i++) {
		delete3DBatch(&vec->data[i - 1]);
		glDeleteTextures(1, &vec->data[i - 1].textureID);
	}
	free(vec->data);
	vec->size = 0;
	vec->limit = 0;
}

Shader createShader(const char* vertexShader, const char* fragmentShader) {
	Shader returnShader;
	returnShader.vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(returnShader.vertexID, 1, &vertexShader, NULL);
	glCompileShader(returnShader.vertexID);


	GLint isCompiledv = 0;
	glGetShaderiv(returnShader.vertexID, GL_COMPILE_STATUS, &isCompiledv);
	if (isCompiledv == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(returnShader.vertexID, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar* errorLog = calloc(maxLength, sizeof(GLchar));
		glGetShaderInfoLog(returnShader.vertexID, maxLength, &maxLength, &errorLog[0]);

		printf("Vertex Shader Failed (What have you done...):\n%s", errorLog);
	}

	returnShader.fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(returnShader.fragmentID, 1, &fragmentShader, NULL);
	glCompileShader(returnShader.fragmentID);


	GLint isCompiledf = 0;
	glGetShaderiv(returnShader.fragmentID, GL_COMPILE_STATUS, &isCompiledf);
	if (isCompiledf == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(returnShader.fragmentID, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar* errorLog = calloc(maxLength, sizeof(GLchar));
		glGetShaderInfoLog(returnShader.fragmentID, maxLength, &maxLength, &errorLog[0]);

		printf("Fragment Shader Failed (What have you done...):\n%s", errorLog);
	}


	returnShader.shaderID = glCreateProgram();
	glAttachShader(returnShader.shaderID, returnShader.vertexID);
	glAttachShader(returnShader.shaderID, returnShader.fragmentID);
	glLinkProgram(returnShader.shaderID);
	glDeleteShader(returnShader.vertexID);
	glDeleteShader(returnShader.fragmentID);
	return returnShader;
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
	GLFWmonitor* returnMon = monitors[widths.size - 1];
	for (int i = 0; i < widths.size; i++) {
		if (widths.size && x > widths.data[i] && x < widths.data[i + 1]) {
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
	stbi_set_flip_vertically_on_load(TRUE);
}
void closeGrey() {
	FT_Done_FreeType(FT);
	glfwTerminate();
}
void setColor(Color* oldColor, Color newColor) {
	oldColor[0][0] = newColor[0];
	oldColor[0][1] = newColor[1];
	oldColor[0][2] = newColor[2];
	oldColor[0][3] = newColor[3];
}

// Window funcs
void framebufferCallback(GLFWwindow* win, int width, int height) {
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
	win.currentShader = 0;
	win.title = title;
	win.shaders = CustomShaderVecCreate();
	win.mouseLocked = FALSE;
	CustomShader s;
	s.shapeBatch = createBatch();
	s.lineBatch = createBatch();
	win.deltaTime = 0.001f;
	win.width = width;
	win.height = height;
	win.fullscreen = FALSE;
	win.priorFullscreen = FALSE;
	win.prevWidth = width;
	win.prevHeight = height;
	s.textures = textureVecCreate();
	s.textures3D = texture3DVecCreate();
	win.zmod = 0.0f;
	win.framesPerSecond = 0.0f;
	s.fonts = fontVecCreate();
	win.startTime = glfwGetTime();
	win.time = 0.0f;
	win.backgroundColor[0] = 0; win.backgroundColor[1] = 0; win.backgroundColor[2] = 0; win.backgroundColor[3] = 255;
	win.offset = Vec3_create();
	win.camera = Camera_create();
	win.transform = Transform_create(0.1f, 1000.0f, win.width, win.height, 70.0f);
	s.texture3DShader = createShader(texture3DVertexShader, texture3DFragmentShader);
	s.colorShader = createShader(colorVertexShader, colorFragmentShader);
	s.textureShader = createShader(textureVertexShader, textureFragmentShader);
	s.fontShader = createShader(fontVertexShader, fontFragmentShader);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	CustomShaderVecPushBack(&win.shaders, s);
	return win;
}
void deleteWindow(Window* win) {
	/*deleteBatch(&win->shaders.data[win->currentShader].shapeBatch);
	textureVecClear(&win->shaders.data[win->currentShader].textures);
	textureVecDelete(&win->shaders.data[win->currentShader].textures);
	glDeleteProgram(win->shaders.data[win->currentShader].colorShader.shaderID);
	glDeleteProgram(win->shaders.data[win->currentShader].textureShader.shaderID);
	glDeleteProgram(win->shaders.data[win->currentShader].fontShader.shaderID);*/
	for (int i = 0; i < win->shaders.size; i++) {
		deleteBatch(&win->shaders.data[i].shapeBatch);
		deleteBatch(&win->shaders.data[i].lineBatch);
		textureVecClear(&win->shaders.data[i].textures);
		textureVecDelete(&win->shaders.data[i].textures);
		textureVecClear(&win->shaders.data[i].textures3D);
		textureVecDelete(&win->shaders.data[i].textures3D);
		glDeleteProgram(win->shaders.data[i].colorShader.shaderID);
		glDeleteProgram(win->shaders.data[i].textureShader.shaderID);
		glDeleteProgram(win->shaders.data[i].fontShader.shaderID);
		glDeleteProgram(win->shaders.data[i].texture3DShader.shaderID);
	}
}
boolean shouldWindowClose(Window win) {
	return glfwWindowShouldClose(win.windowHandle);
}
Texture newTexture(Window* win, const char* path, int filter) {
	TextureBatch text = createTextureBatch(path, filter);
	//textureVecPushBack(&win->shaders.data[win->currentShader].textures, text);
	for (int i = 0; i < win->shaders.size; i++) {
		textureVecPushBack(&win->shaders.data[i].textures, text);
	}
	return win->shaders.data[win->currentShader].textures.size - 1;
}
Texture new3DTexture(Window* win, const char* path, int filter) {
	Batch3D text = create3DBatch(path, filter);
	//textureVecPushBack(&win->shaders.data[win->currentShader].textures, text);
	for (int i = 0; i < win->shaders.size; i++) {
		texture3DVecPushBack(&win->shaders.data[i].textures3D, text);
	}
	return win->shaders.data[win->currentShader].textures3D.size - 1;
}
Texture blank3DTexture(Window* win) {
	Batch3D text = createBlank3DBatch();
	//textureVecPushBack(&win->shaders.data[win->currentShader].textures, text);
	for (int i = 0; i < win->shaders.size; i++) {
		texture3DVecPushBack(&win->shaders.data[i].textures3D, text);
	}
	return win->shaders.data[win->currentShader].textures3D.size - 1;
}
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
void deleteTexture(Window* win, Texture texture) {
	//deleteTextureBatch(&win->shaders.data[win->currentShader].textures.data[texture]);
	for (int i = 0; i < win->shaders.size; i++) {
		deleteTextureBatch(&win->shaders.data[i].textures.data[texture]);
	}
	glDeleteTextures(1, &win->shaders.data[win->currentShader].textures.data[texture].textureID);
}
void delete3DTexture(Window* win, Texture texture) {
	//deleteTextureBatch(&win->shaders.data[win->currentShader].textures.data[texture]);
	for (int i = 0; i < win->shaders.size; i++) {
		delete3DBatch(&win->shaders.data[i].textures.data[texture]);
	}
	glDeleteTextures(1, &win->shaders.data[win->currentShader].textures.data[texture].textureID);
}
void updateWindow(Window* win) {
	win->transform.camera = win->camera;
	/*flushBatch(&win->shaders.data[win->currentShader].shapeBatch);
	for (int i = 0; i < win->shaders.data[win->currentShader].textures.size; i++) {
		flushTextureBatch(&win->shaders.data[win->currentShader].textures.data[i]);
	}
	for (int i = 0; i < win->shaders.data[win->currentShader].fonts.size; i++) {
		for (int z = 0; z < 128; z++) {
			flushTextureBatch(&win->shaders.data[win->currentShader].fonts.data[i].characters[z].batch);
		}
	}*/
	for (int i = 0; i < win->shaders.size; i++) {
		flushBatch(&win->shaders.data[i].shapeBatch);
		flushBatch(&win->shaders.data[i].lineBatch);
		for (int z = 0; z < win->shaders.data[i].textures.size; z++) {
			flushTextureBatch(&win->shaders.data[i].textures.data[z]);
		}
		for (int z = 0; z < win->shaders.data[i].textures3D.size; z++) {
			flushTextureBatch(&win->shaders.data[i].textures3D.data[z]);
		}
		for (int z = 0; z < win->shaders.data[i].fonts.size; z++) {
			for (int y = 0; y < 128; y++) {
				flushTextureBatch(&win->shaders.data[i].fonts.data[z].characters[y].batch);
			}
		}
	}
	win->framesPerSecond = 1.0f / (glfwGetTime() - win->currentFrame);
	win->currentFrame = (float)glfwGetTime();
	win->deltaTime = win->currentFrame - win->lastFrame;
	win->lastFrame = win->currentFrame;
	win->zmod = 0.0f;
	win->time = glfwGetTime() - win->startTime;
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
	int windowX, windowY;
	glfwGetWindowPos(win->windowHandle, &windowX, &windowY);
	glfwGetCursorPos(&win->windowHandle, &win->mouse.x, &win->mouse.y);
	win->mouse.x -= windowX;
	win->mouse.y -= windowY;
	int state = glfwGetMouseButton(win->windowHandle, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS) {
		if (win->mouse.isPrimaryDown == FALSE) {
			win->mouse.isPrimaryPressed = TRUE;
		}
		else {
			win->mouse.isPrimaryPressed = FALSE;
		}
		win->mouse.isPrimaryDown = TRUE;
	}
	else {
		win->mouse.isPrimaryDown = FALSE;
		win->mouse.isPrimaryPressed = FALSE;
	}
	state = glfwGetMouseButton(win->windowHandle, GLFW_MOUSE_BUTTON_RIGHT);
	if (state == GLFW_PRESS) {
		if (win->mouse.isSecondaryDown == FALSE) {
			win->mouse.isSecondaryPressed = TRUE;
		}
		else {
			win->mouse.isSecondaryPressed = FALSE;
		}
		win->mouse.isSecondaryDown = TRUE;
	}
	else {
		win->mouse.isSecondaryDown = FALSE;
		win->mouse.isSecondaryPressed = FALSE;
	}
	state = glfwGetMouseButton(win->windowHandle, GLFW_MOUSE_BUTTON_MIDDLE);
	if (state == GLFW_PRESS) {
		if (win->mouse.isMiddleDown == FALSE) {
			win->mouse.isMiddlePressed = TRUE;
		}
		else {
			win->mouse.isMiddlePressed = FALSE;
		}
		win->mouse.isMiddleDown = TRUE;
	}
	else {
		win->mouse.isMiddleDown = FALSE;
		win->mouse.isMiddlePressed = FALSE;
	}
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
	win.transform.camera = win.camera;
	glfwMakeContextCurrent(win.windowHandle);
	glfwSetWindowSize(win.windowHandle, win.width, win.height);
	glClearColor((float)win.backgroundColor[0] / 255, (float)win.backgroundColor[1] / 255, (float)win.backgroundColor[2] / 255, (float)win.backgroundColor[3] / 255);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < win.shaders.size; i++) {

		glUseProgram(win.shaders.data[i].texture3DShader.shaderID);
		//glUniform2f(glGetUniformLocation(win.shaders.data[i].texture3DShader.shaderID, "viewport"), (GLfloat)win.width / 2, (GLfloat)win.height / 2);
		glUniform3f(glGetUniformLocation(win.shaders.data[i].texture3DShader.shaderID, "offset"), (GLfloat)win.offset.x, (GLfloat)win.offset.y, (GLfloat)win.offset.z);
		glUniformMatrix4fv(glGetUniformLocation(win.shaders.data[i].texture3DShader.shaderID, "transform"), 1, GL_TRUE, (float[16])createFloatBuffer(Transform_getTranformation(win.transform)));
		glUniformMatrix4fv(glGetUniformLocation(win.shaders.data[i].texture3DShader.shaderID, "transformProj"), 1, GL_TRUE, (float[16])createFloatBuffer(Transform_getProjectedTranformation(win.transform)));

		for (int z = 0; z < win.shaders.data[i].textures3D.size; z++) {
			bind3DBatch(win.shaders.data[i].textures3D.data[z]);
			glBindTexture(GL_TEXTURE_2D, win.shaders.data[i].textures3D.data[z].textureID);
			glBindVertexArray(win.shaders.data[i].textures3D.data[z].VAO);
			draw3DBatch(win.shaders.data[i].textures3D.data[z], GL_TRIANGLES);
		}




		bindBatch(win.shaders.data[i].shapeBatch);
		glUseProgram(win.shaders.data[i].colorShader.shaderID);
		glUniform2f(glGetUniformLocation(win.shaders.data[i].colorShader.shaderID, "viewport"), (GLfloat)win.width / 2, (GLfloat)win.height / 2);
		glUniform3f(glGetUniformLocation(win.shaders.data[i].colorShader.shaderID, "offset"), (GLfloat)win.offset.x, (GLfloat)win.offset.y, (GLfloat)win.offset.z);

		draw(win.shaders.data[i].shapeBatch, GL_TRIANGLE_FAN);

		bindBatch(win.shaders.data[i].lineBatch);
		draw(win.shaders.data[i].lineBatch, GL_LINE_STRIP);

		glUseProgram(win.shaders.data[i].textureShader.shaderID);
		glUniform2f(glGetUniformLocation(win.shaders.data[i].textureShader.shaderID, "viewport"), (GLfloat)win.width / 2, (GLfloat)win.height / 2);
		glUniform3f(glGetUniformLocation(win.shaders.data[i].textureShader.shaderID, "offset"), (GLfloat)win.offset.x, (GLfloat)win.offset.y, (GLfloat)win.offset.z);

		for (int z = 0; z < win.shaders.data[i].textures.size; z++) {
			bindTextureBatch(win.shaders.data[i].textures.data[z]);
			glBindTexture(GL_TEXTURE_2D, win.shaders.data[i].textures.data[z].textureID);
			glBindVertexArray(win.shaders.data[i].textures.data[z].VAO);
			drawTextureBatch(win.shaders.data[i].textures.data[z], GL_TRIANGLE_FAN);
		}

		glUseProgram(win.shaders.data[i].fontShader.shaderID);
		glUniform2f(glGetUniformLocation(win.shaders.data[i].fontShader.shaderID, "viewport"), (GLfloat)win.width / 2, (GLfloat)win.height / 2);
		glUniform3f(glGetUniformLocation(win.shaders.data[i].fontShader.shaderID, "offset"), (GLfloat)win.offset.x, (GLfloat)win.offset.y, (GLfloat)win.offset.z);

		for (int z = 0; z < win.shaders.data[i].fonts.size; z++) {
			for (int y = 0; y < 128; y++) {
				bindTextureBatch(win.shaders.data[i].fonts.data[z].characters[y].batch);
				glBindTexture(GL_TEXTURE_2D, win.shaders.data[i].fonts.data[z].characters[y].batch.textureID);
				glBindVertexArray(win.shaders.data[i].fonts.data[z].characters[y].batch.VAO);
				drawTextureBatch(win.shaders.data[i].fonts.data[z].characters[y].batch, GL_TRIANGLE_FAN);
			}
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
void clearWindowBackground(Window* win, Color color) {
	// I really wish there was a better way of doing this
	win->backgroundColor[0] = color[0];
	win->backgroundColor[1] = color[1];
	win->backgroundColor[2] = color[2];
	win->backgroundColor[3] = color[3];
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
		x1, -y1, win->zmod, (float)color[0] / 255, (float)color[1] / 255, (float)color[2] / 255, (float)color[3] / 255,
		x2, -y2, win->zmod, (float)color[0] / 255, (float)color[1] / 255, (float)color[2] / 255, (float)color[3] / 255,
		x3, -y3, win->zmod, (float)color[0] / 255, (float)color[1] / 255, (float)color[2] / 255, (float)color[3] / 255
	};
	addTriangle(&win->shaders.data[win->currentShader].shapeBatch, passIn1);
	endShape(&win->shaders.data[win->currentShader].shapeBatch);
	win->zmod -= 0.000001f;
}
void drawRectangle(Window* win, float x, float y, float width, float height, float rotation, Color color) {
	float r = (float)color[0] / 255, g = (float)color[1] / 255, b = (float)color[2] / 255, a = (float)color[3] / 255;
	y = -y;
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
	addTriangle(&win->shaders.data[win->currentShader].shapeBatch, passIn1);
	addVertice(&win->shaders.data[win->currentShader].shapeBatch, passIn2);
	endShape(&win->shaders.data[win->currentShader].shapeBatch);
	win->zmod -= 0.000001f;
}
void drawTexture(Window* win, Texture texture, float x, float y, float width, float height, float rotation, Color color) {
	float r = (float)color[0] / 255, g = (float)color[1] / 255, b = (float)color[2] / 255, a = (float)color[3] / 255;
	y = -y;
	float pi = 3.1415926535897932384626433;
	rotation = -rotation * (pi / 180);
	float a1 = sqrt(pow((width / 2), 2) + pow((height / 2), 2));
	float r0 = asin(((height / 2) * (sin(pi / 2))) / a1), r1 = r0 + rotation, r2 = -r0 + rotation, r3 = r1 - pi, r4 = r2 - pi;
	float c1 = x + width / 2, c2 = y - height / 2;
	float passIn1[27] = {
		a1 * cos(r1) + c1, a1 * sin(r1) + c2, win->zmod, r, g, b, a, 1.0f, 1.0f,
		a1 * cos(r2) + c1, a1 * sin(r2) + c2, win->zmod, r, g, b, a, 1.0f, 0.0f,
		a1 * cos(r3) + c1, a1 * sin(r3) + c2, win->zmod, r, g, b, a, 0.0f, 0.0f
	};
	float passIn2[9] = {
		a1 * cos(r4) + c1, a1 * sin(r4) + c2, win->zmod, r, g, b, a, 0.0f, 1.0f
	};
	addTextureTriangle(&win->shaders.data[win->currentShader].textures.data[texture], passIn1);
	addTextureVertice(&win->shaders.data[win->currentShader].textures.data[texture], passIn2);
	endTextureShape(&win->shaders.data[win->currentShader].textures.data[texture]);
	win->zmod -= 0.000001f;
}

void drawCircle(Window* win, float x, float y, float radius, Color color) {
	float cR, cG, cB, cA; cR = (float)(color[0]) / 255; cG = (float)(color[1]) / 255; cB = (float)(color[2]) / 255; cA = (float)(color[3]) / 255;
	y = -y;
	float pi2 = 2 * PI;
	int amount = CIRCLE_ACCURACY;
	float passIn[7] = { x, y, win->zmod, cR, cG, cB, cA };
	addVertice(&win->shaders.data[win->currentShader].shapeBatch, passIn);
	for (int i = 0; i <= amount; i++) {
		float passIn2[7] = { x + (radius * cos(i * pi2 / amount)), y + (radius * sin(i * pi2 / amount)), win->zmod, cR, cG, cB, cA };
		addVertice(&win->shaders.data[win->currentShader].shapeBatch, passIn2);
	}
	endShape(&win->shaders.data[win->currentShader].shapeBatch);

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
	addTriangle(&win->shaders.data[win->currentShader].shapeBatch, passIn0);
	addVertice(&win->shaders.data[win->currentShader].shapeBatch, passIn1);
	endShape(&win->shaders.data[win->currentShader].shapeBatch);

	a = x1;
	b = y1 + radius;
	c = x1 + width;
	d = y1 + height - radius;
	float passIn2[21] = { rotateX(a,b,c1,c2,rot),rotateY(a,b,c1,c2,rot),win->zmod,cR,cG,cB,cA, rotateX(a,d,c1,c2,rot),rotateY(a,d,c1,c2,rot),win->zmod,cR,cG,cB,cA, rotateX(c,d,c1,c2,rot),rotateY(c,d,c1,c2,rot),win->zmod,cR,cG,cB,cA };
	float passIn3[7] = { rotateX(c,b,c1,c2,rot),rotateY(c,b,c1,c2,rot),win->zmod,cR,cG,cB,cA };
	addTriangle(&win->shaders.data[win->currentShader].shapeBatch, passIn2);
	addVertice(&win->shaders.data[win->currentShader].shapeBatch, passIn3);
	endShape(&win->shaders.data[win->currentShader].shapeBatch);


	float xii = x1 + radius;
	float yii = y1 + radius;
	float xi = rotateX(xii, yii, c1, c2, rot);
	float yi = rotateY(xii, yii, c1, c2, rot);
	float pi2 = 2 * PI;
	int amount = CIRCLE_ACCURACY;
	float passIn4[7] = { xi, yi, win->zmod, cR, cG, cB, cA };
	addVertice(&win->shaders.data[win->currentShader].shapeBatch, passIn4);
	for (int i = 0; i <= amount; i++) {
		float passIn5[7] = { xi + (radius * cos(i * pi2 / amount)), yi + (radius * sin(i * pi2 / amount)), win->zmod, cR, cG, cB, cA };
		addVertice(&win->shaders.data[win->currentShader].shapeBatch, passIn5);
	}
	endShape(&win->shaders.data[win->currentShader].shapeBatch);

	xii = x1 + width - radius;
	yii = y1 + radius;
	xi = rotateX(xii, yii, c1, c2, rot);
	yi = rotateY(xii, yii, c1, c2, rot);
	float passIn6[7] = { xi, yi, win->zmod, cR, cG, cB, cA };
	addVertice(&win->shaders.data[win->currentShader].shapeBatch, passIn6);
	for (int i = 0; i <= amount; i++) {
		float passIn7[7] = { xi + (radius * cos(i * pi2 / amount)), yi + (radius * sin(i * pi2 / amount)), win->zmod, cR, cG, cB, cA };
		addVertice(&win->shaders.data[win->currentShader].shapeBatch, passIn7);
	}
	endShape(&win->shaders.data[win->currentShader].shapeBatch);

	xii = x1 + width - radius;
	yii = y1 + height - radius;
	xi = rotateX(xii, yii, c1, c2, rot);
	yi = rotateY(xii, yii, c1, c2, rot);
	float passIn8[7] = { xi, yi, win->zmod, cR, cG, cB, cA };
	addVertice(&win->shaders.data[win->currentShader].shapeBatch, passIn8);
	for (int i = 0; i <= amount; i++) {
		float passIn9[7] = { xi + (radius * cos(i * pi2 / amount)), yi + (radius * sin(i * pi2 / amount)), win->zmod, cR, cG, cB, cA };
		addVertice(&win->shaders.data[win->currentShader].shapeBatch, passIn9);
	}
	endShape(&win->shaders.data[win->currentShader].shapeBatch);

	xii = x1 + radius;
	yii = y1 + height - radius;
	xi = rotateX(xii, yii, c1, c2, rot);
	yi = rotateY(xii, yii, c1, c2, rot);
	float passIn10[7] = { xi, yi, win->zmod, cR, cG, cB, cA };
	addVertice(&win->shaders.data[win->currentShader].shapeBatch, passIn10);
	for (int i = 0; i <= amount; i++) {
		float passIn11[7] = { xi + (radius * cos(i * pi2 / amount)), yi + (radius * sin(i * pi2 / amount)), win->zmod, cR, cG, cB, cA };
		addVertice(&win->shaders.data[win->currentShader].shapeBatch, passIn11);
	}
	endShape(&win->shaders.data[win->currentShader].shapeBatch);

	win->zmod -= 0.000001f;
}
void drawText(Window* win, const char* text, FontID font, float x, float y, float scale, Color color) {
	if (font == -1) { return; }
	y += scale;
	scale = scale / win->shaders.data[win->currentShader].fonts.data[font].scale;
	float r = (float)color[0] / 255, g = (float)color[1] / 255, b = (float)color[2] / 255, a = (float)color[3] / 255;
	for (int i = 0; text[i] != '\0'; i++) {
		Character c = win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]];
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
		addTextureTriangle(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn1);
		addTextureVertice(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn2);
		endTextureShape(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch);
		x += (c.advance >> 6) * scale;
		win->zmod -= 0.000001f;
	}
}
void drawBorderedText(Window* win, const char* text, FontID font, float x, float y, float scale, float borderSize, Color color, Color borderColor) {
	if (font == -1) { return; }
	y += scale;
	scale = scale / win->shaders.data[win->currentShader].fonts.data[font].scale;
	float r = (float)color[0] / 255, g = (float)color[1] / 255, b = (float)color[2] / 255, a = (float)color[3] / 255;
	float br = (float)borderColor[0] / 255, bg = (float)borderColor[1] / 255, bb = (float)borderColor[2] / 255, ba = (float)borderColor[3] / 255;
	float borderSize2 = borderSize * 2;
	// This process is not only kinda slow, but it can be probably done with a different shader...
	for (int i = 0; text[i] != '\0'; i++) {
		Character c = win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]];
		float xpos = x + c.bearingX * scale;
		float ypos = y + (c.sizeY - c.bearingY) * scale;
		float w = c.sizeX * scale, h = c.sizeY * scale;
		// U
		float passIn1[27] = {
			xpos, -(ypos), win->zmod, br, bg, bb, ba, 0.0f, 1.0f,
			xpos, -(ypos - h - borderSize2), win->zmod, br, bg, bb, ba, 0.0f, 0.0f,
			xpos + w, -(ypos - h - borderSize2), win->zmod, br, bg, bb, ba, 1.0f, 0.0f
		};
		float passIn2[9] = {
			xpos + w, -(ypos), win->zmod, br, bg, bb, ba, 1.0f, 1.0f
		};
		addTextureTriangle(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn1);
		addTextureVertice(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn2);
		endTextureShape(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch);
		win->zmod -= 0.000001f;
		// D
		float passIn3[27] = {
			xpos, -(ypos + borderSize2), win->zmod, br, bg, bb, ba, 0.0f, 1.0f,
			xpos, -(ypos - h), win->zmod, br, bg, bb, ba, 0.0f, 0.0f,
			xpos + w, -(ypos - h), win->zmod, br, bg, bb, ba, 1.0f, 0.0f
		};
		float passIn4[9] = {
			xpos + w, -(ypos + borderSize2), win->zmod, br, bg, bb, ba, 1.0f, 1.0f
		};
		addTextureTriangle(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn3);
		addTextureVertice(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn4);
		endTextureShape(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch);
		win->zmod -= 0.000001f;
		// L
		float passIn5[27] = {
			xpos - borderSize2, -(ypos), win->zmod, br, bg, bb, ba, 0.0f, 1.0f,
			xpos - borderSize2, -(ypos - h), win->zmod, br, bg, bb, ba, 0.0f, 0.0f,
			xpos + w, -(ypos - h), win->zmod, br, bg, bb, ba, 1.0f, 0.0f
		};
		float passIn6[9] = {
			xpos + w, -(ypos), win->zmod, br, bg, bb, ba, 1.0f, 1.0f
		};
		addTextureTriangle(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn5);
		addTextureVertice(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn6);
		endTextureShape(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch);
		win->zmod -= 0.000001f;
		// R
		float passIn7[27] = {
			xpos, -(ypos), win->zmod, br, bg, bb, ba, 0.0f, 1.0f,
			xpos, -(ypos - h), win->zmod, br, bg, bb, ba, 0.0f, 0.0f,
			xpos + borderSize2 + w, -(ypos - h), win->zmod, br, bg, bb, ba, 1.0f, 0.0f
		};
		float passIn8[9] = {
			xpos + borderSize2 + w, -(ypos), win->zmod, br, bg, bb, ba, 1.0f, 1.0f
		};
		addTextureTriangle(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn7);
		addTextureVertice(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn8);
		endTextureShape(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch);
		win->zmod -= 0.000001f;
		// UL
		float passIn9[27] = {
			xpos - borderSize2, -(ypos), win->zmod, br, bg, bb, ba, 0.0f, 1.0f,
			xpos - borderSize2, -(ypos - h - borderSize2), win->zmod, br, bg, bb, ba, 0.0f, 0.0f,
			xpos + w, -(ypos - h - borderSize2), win->zmod, br, bg, bb, ba, 1.0f, 0.0f
		};
		float passIn10[9] = {
			xpos + w, -(ypos), win->zmod, br, bg, bb, ba, 1.0f, 1.0f
		};
		addTextureTriangle(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn9);
		addTextureVertice(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn10);
		endTextureShape(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch);
		win->zmod -= 0.000001f;
		// UR
		float passIn11[27] = {
			xpos, -(ypos), win->zmod, br, bg, bb, ba, 0.0f, 1.0f,
			xpos, -(ypos - h - borderSize2), win->zmod, br, bg, bb, ba, 0.0f, 0.0f,
			xpos + w + borderSize2, -(ypos - h - borderSize2), win->zmod, br, bg, bb, ba, 1.0f, 0.0f
		};
		float passIn12[9] = {
			xpos + w + borderSize2, -(ypos), win->zmod, br, bg, bb, ba, 1.0f, 1.0f
		};
		addTextureTriangle(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn11);
		addTextureVertice(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn12);
		endTextureShape(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch);
		win->zmod -= 0.000001f;
		// DL
		float passIn13[27] = {
			xpos - borderSize2, -(ypos + borderSize2), win->zmod, br, bg, bb, ba, 0.0f, 1.0f,
			xpos - borderSize2, -(ypos - h), win->zmod, br, bg, bb, ba, 0.0f, 0.0f,
			xpos + w, -(ypos - h), win->zmod, br, bg, bb, ba, 1.0f, 0.0f
		};
		float passIn14[9] = {
			xpos + w, -(ypos + borderSize2), win->zmod, br, bg, bb, ba, 1.0f, 1.0f
		};
		addTextureTriangle(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn13);
		addTextureVertice(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn14);
		endTextureShape(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch);
		win->zmod -= 0.000001f;
		// DR
		float passIn15[27] = {
			xpos, -(ypos + borderSize2), win->zmod, br, bg, bb, ba, 0.0f, 1.0f,
			xpos, -(ypos - h), win->zmod, br, bg, bb, ba, 0.0f, 0.0f,
			xpos + w + borderSize2, -(ypos - h), win->zmod, br, bg, bb, ba, 1.0f, 0.0f
		};
		float passIn16[9] = {
			xpos + w + borderSize2, -(ypos + borderSize2), win->zmod, br, bg, bb, ba, 1.0f, 1.0f
		};
		addTextureTriangle(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn15);
		addTextureVertice(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn16);
		endTextureShape(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch);
		win->zmod -= 0.000001f;
		float passIn9999[27] = {
			xpos, -(ypos), win->zmod, r, g, b, a, 0.0f, 1.0f,
			xpos, -(ypos - h), win->zmod, r, g, b, a, 0.0f, 0.0f,
			xpos + w, -(ypos - h), win->zmod, r, g, b, a, 1.0f, 0.0f
		};
		float passIn999[9] = {
			xpos + w, -(ypos), win->zmod, r, g, b, a, 1.0f, 1.0f
		};
		addTextureTriangle(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn9999);
		addTextureVertice(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch, passIn999);
		endTextureShape(&win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]].batch);
		x += (c.advance >> 6) * scale;
		win->zmod -= 0.000001f;
	}
}
float getWidthOfText(Window* win, const char* text, FontID font, float scale) {
	float x = 0;
	if (font == -1) { return; }
	scale = scale / win->shaders.data[win->currentShader].fonts.data[font].scale;
	for (int i = 0; text[i] != '\0'; i++) {
		Character c = win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]];
		float xpos = x + c.bearingX * scale;
		float w = c.sizeX * scale, h = c.sizeY * scale;
		x += (c.advance >> 6) * scale;
	}
	return x;
}
float getHeightOfText(Window* win, const char* text, FontID font, float scale) {
	float finalh = 0.0f;
	if (font == -1) { return; }
	scale = scale / win->shaders.data[win->currentShader].fonts.data[font].scale;
	for (int i = 0; text[i] != '\0'; i++) {
		Character c = win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]];
		float h = c.sizeY * scale;
		if (h > finalh) finalh = h;
	}
	return finalh;
}
void drawPolygon(Window* win, float* xs, float* ys, int points, Color color) {
	float r = (float)color[0] / 255, g = (float)color[1] / 255, b = (float)color[2] / 255, a = (float)color[3] / 255;
	for (int i = 0; i < points; i++) {
		float passIn[7] = { xs[i], -ys[i], win->zmod, r, g, b, a };
		addVertice(&win->shaders.data[win->currentShader].shapeBatch, passIn);
	}
	endShape(&win->shaders.data[win->currentShader].shapeBatch);
	win->zmod -= 0.000001f;
}
void drawAdvancedRect(Window* win, float x, float y, float width, float height, float rotation, Color topLeft, Color topRight, Color bottomLeft, Color bottomRight) {
	float cr1 = (float)topRight[0] / 255, cg1 = (float)topRight[1] / 255, cb1 = (float)topRight[2] / 255, ca1 = (float)topRight[3] / 255;
	float cr2 = (float)bottomRight[0] / 255, cg2 = (float)bottomRight[1] / 255, cb2 = (float)bottomRight[2] / 255, ca2 = (float)bottomRight[3] / 255;
	float cr3 = (float)bottomLeft[0] / 255, cg3 = (float)bottomLeft[1] / 255, cb3 = (float)bottomLeft[2] / 255, ca3 = (float)bottomLeft[3] / 255;
	float cr4 = (float)topLeft[0] / 255, cg4 = (float)topLeft[1] / 255, cb4 = (float)topLeft[2] / 255, ca4 = (float)topLeft[3] / 255;
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
	addTriangle(&win->shaders.data[win->currentShader].shapeBatch, passIn1);
	addVertice(&win->shaders.data[win->currentShader].shapeBatch, passIn2);
	endShape(&win->shaders.data[win->currentShader].shapeBatch);

	win->zmod -= 0.000001f;
}
void drawAdvancedTriangle(Window* win, float x1, float y1, float x2, float y2, float x3, float y3, Color bottomLeft, Color topMiddle, Color bottomRight) {
	float passIn1[21] = {
		x1, -y1, win->zmod, (float)bottomLeft[0] / 255, (float)bottomLeft[1] / 255, (float)bottomLeft[2] / 255, (float)bottomLeft[3] / 255,
		x2, -y2, win->zmod, (float)topMiddle[0] / 255, (float)topMiddle[1] / 255, (float)topMiddle[2] / 255, (float)topMiddle[3] / 255,
		x3, -y3, win->zmod, (float)bottomRight[0] / 255, (float)bottomRight[1] / 255, (float)bottomRight[2] / 255, (float)bottomRight[3] / 255
	};
	addTriangle(&win->shaders.data[win->currentShader].shapeBatch, passIn1);
	endShape(&win->shaders.data[win->currentShader].shapeBatch);
	win->zmod -= 0.000001f;
}
void drawLine(Window* win, float x1, float y1, float x2, float y2, float thickness, Color color1) {
	y1 = -y1;
	y2 = -y2;
	float passIn1[7] = { x1, y1, win->zmod, (float)color1[0] / 255, (float)color1[1] / 255, (float)color1[2] / 255, (float)color1[3] / 255 };
	float passIn2[7] = { x2, y2, win->zmod, (float)color1[0] / 255, (float)color1[1] / 255, (float)color1[2] / 255, (float)color1[3] / 255 };
	glLineWidth(thickness);
	addVertice(&win->shaders.data[win->currentShader].lineBatch, passIn1);
	addVertice(&win->shaders.data[win->currentShader].lineBatch, passIn2);
	endShape(&win->shaders.data[win->currentShader].lineBatch);
	win->zmod -= 0.000001f;
}

void drawAdvancedLine(Window* win, float x1, float y1, float x2, float y2, float thickness, Color color1, Color color2) {
	y1 = -y1;
	y2 = -y2;
	float passIn1[7] = { x1, y1, win->zmod, (float)color1[0] / 255, (float)color1[1] / 255, (float)color1[2] / 255, (float)color1[3] / 255 };
	float passIn2[7] = { x2, y2, win->zmod, (float)color2[0] / 255, (float)color2[1] / 255, (float)color2[2] / 255, (float)color2[3] / 255 };
	glLineWidth(thickness);
	addVertice(&win->shaders.data[win->currentShader].lineBatch, passIn1);
	addVertice(&win->shaders.data[win->currentShader].lineBatch, passIn2);
	endShape(&win->shaders.data[win->currentShader].lineBatch);
	win->zmod -= 0.000001f;
}

Vertice Vertice_new(float x, float y, float z, Color color, float u, float v) {
	Vertice o;
	o.x = x;
	o.y = -y;
	o.z = z;
	o.r = (float)color[0] / 255.0f;
	o.g = (float)color[1] / 255.0f;
	o.b = (float)color[2] / 255.0f;
	o.a = (float)color[3] / 255.0f;
	o.u = u;
	o.v = v;
	o.nx = 0;
	o.ny = 0;
	o.nz = 0;
	return o;
}

Vertice Vertice_create(Vec3 pos, Color color, Vec2 uv, Vec3 normal) {
	Vertice o;
	o.x = pos.x;
	o.y = pos.y;
	o.z = pos.z;
	o.r = (float)color[0] / 255.0f;
	o.g = (float)color[1] / 255.0f;
	o.b = (float)color[2] / 255.0f;
	o.a = (float)color[3] / 255.0f;
	o.u = uv.x;
	o.v = uv.y;
	o.nx = normal.x;
	o.ny = normal.y;
	o.nz = normal.z;
	return o;
}

boolean vertEqToVec(Vertice a, Vec3 b) {
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

Vertices calcNormals(Vertices v) {
	Vertices o;
	o.size = v.size;
	o.vertices = (Vertice*)calloc(v.size, sizeof(Vertice));
	for (int i = 0; i < v.size; i++) {
		o.vertices[i] = v.vertices[i];
	}

	for (int i = 0; i < o.size; i += 3) {
		Vertice va = o.vertices[i];
		Vertice vb = o.vertices[i + 1];
		Vertice vc = o.vertices[i + 2];
		Vec3 a = Vec3_new(va.x, va.y, va.z);
		Vec3 b = Vec3_new(vb.x, vb.y, vb.z);
		Vec3 c = Vec3_new(vc.x, vc.y, vc.z);

		Vec3 p = Vec3_cross(Vec3_sub(b, a), Vec3_sub(c, a));

		for (int j = 0; j < o.size; j++) {
			if (vertEqToVec(o.vertices[j], a) || vertEqToVec(o.vertices[j], b) || vertEqToVec(o.vertices[j], c)) {
				o.vertices[j].nx += p.x;
				o.vertices[j].ny += p.y;
				o.vertices[j].nz += p.z;
			}
		}
	}

	for (int j = 0; j < o.size; j++) {
		Vec3 normal = Vec3_normalize(Vec3_new(o.vertices[j].nx, o.vertices[j].ny, o.vertices[j].nz));
		o.vertices[j].nx = normal.x;
		o.vertices[j].ny = normal.y;
		o.vertices[j].nz = normal.z;
	}

	return o;
}

void draw3DShape(Window* win, Texture texture, Vertices vert) {
	boolean a = TRUE;
	for (int i = 0; i < vert.size; i++) {
		if (vert.vertices[i].nx != 0 || vert.vertices[i].ny != 0 || vert.vertices[i].nz != 0) a = FALSE;
	}
	Vertices vertices;
	if (a) {
		vertices = calcNormals(vert);
	}
	else {
		vertices = vert;
	}
	for (int i = 0; i < vertices.size; i++) {

		Vertice v = vertices.vertices[i];
		float passIn1[12] = { v.x,v.y,v.z, v.r,v.g,v.b,v.a, v.u,v.v, v.nx,v.ny,v.nz };
		//printf("%f, %f, %f\n", v.nx, v.ny, v.nz);
		add3DVertice(&win->shaders.data[win->currentShader].textures3D.data[texture], passIn1);
	}
	//printf("\n");
	end3DShape(&win->shaders.data[win->currentShader].textures3D.data[texture]);
	win->zmod -= 0.000001f;
}

void setMouseLocked(Window* win, boolean locked) {
	win->mouseLocked = locked;
	if (locked == TRUE) {
		glfwSetInputMode(win->windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else {
		glfwSetInputMode(win->windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void setMousePos(Window* win, float x, float y) {
	glfwSetCursorPos(win->windowHandle, x, y);
}
