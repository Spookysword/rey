#define IMPLEMENT_REY_H
#include "grey.h"

void initGrey(unsigned int sampleRate=4) {
    C_initGrey(sampleRate);
}

void closeGrey() {
    C_closeGrey();
}

class Window {
    public:
    C_Window window;
    Window(int width, int height, const char* title) {
        window = C_createWindow(width, height, title);
    }
    bool shouldClose() {
        return C_shouldWindowClose(window);
    }
    void update() {
        C_updateWindow(&window);
    }
    void render() {
        C_renderWindow(window);
    }
    void close() {
        C_closeWindow(window);
    }
    void setFlag(uint32_t flag, bool state) {
        C_setWindowFlag(window, flag, (boolean)state);
    }
    bool isKeyDown(int key) {
        return C_isKeyDown(window, key);
    }
    void clearBackground(float R, float G, float B, float A = 255) {
        C_clearWindowBackground(window, R, G, B, A);
    }

};