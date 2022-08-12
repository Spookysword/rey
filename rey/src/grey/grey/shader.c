#include "grey/grey/shader.h"

#ifdef __cplusplus
namespace grey {
#endif
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
#ifdef __cplusplus
}
#endif