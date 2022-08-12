#include "grey/grey/batch_3d.h"
#ifdef __cplusplus
namespace grey {
#endif
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
#ifdef __cplusplus
}
#endif