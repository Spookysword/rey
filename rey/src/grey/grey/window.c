#include "grey/grey/window.h"

#ifdef __cplusplus
namespace grey {
#endif
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
		texture3DVecClear(&win->shaders.data[i].textures3D);
		texture3DVecDelete(&win->shaders.data[i].textures3D);
		glDeleteProgram(win->shaders.data[i].colorShader.shaderID);
		glDeleteProgram(win->shaders.data[i].textureShader.shaderID);
		glDeleteProgram(win->shaders.data[i].fontShader.shaderID);
		glDeleteProgram(win->shaders.data[i].texture3DShader.shaderID);
	}
}
boolean shouldWindowClose(Window win) {
	return glfwWindowShouldClose(win.windowHandle);
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
			flush3DBatch(&win->shaders.data[i].textures3D.data[z]);
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
	glfwGetCursorPos(win->windowHandle, &win->mouse.x, &win->mouse.y);
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
	if (font == -1) { return 0.0f; }
	scale = scale / win->shaders.data[win->currentShader].fonts.data[font].scale;
	for (int i = 0; text[i] != '\0'; i++) {
		Character c = win->shaders.data[win->currentShader].fonts.data[font].characters[text[i]];
		float xpos = x + c.bearingX * scale;
		float w = c.sizeX * scale, h = c.sizeY * scale;
		x += (c.advance >> 6) * scale;
	}
	return x;
}
float getWidthOfChar(Window* win, char text, FontID font, float scale) {
	Character c = win->shaders.data[win->currentShader].fonts.data[font].characters[text];
	float size = (c.advance >> 6) * (scale / win->shaders.data[win->currentShader].fonts.data[font].scale);
	return size;
}
float getHeightOfText(Window* win, const char* text, FontID font, float scale) {
	float finalh = 0.0f;
	if (font == -1) { return 0.0f; }
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
#ifdef __cplusplus
}
#endif