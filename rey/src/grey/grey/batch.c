#include "grey/grey/batch.h"

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