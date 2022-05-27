#include "grey.hpp"

void initGrey(unsigned int sampleRate) {
    C_initGrey(sampleRate);
}

void closeGrey() {
    C_closeGrey();
}


Window::Window(int width, int height, const char* title) {
    window = C_createWindow(width, height, title);
}
bool Window::shouldClose() {
    return C_shouldWindowClose(window);
}
void Window::update() {
    C_updateWindow(&window);
}
void Window::render() {
    C_renderWindow(window);
}
void Window::close() {
    C_closeWindow(window);
}
void Window::setFlag(uint32_t flag, bool state) {
    C_setWindowFlag(window, flag, (boolean)state);
}
bool Window::isKeyDown(int key) {
    return C_isKeyDown(window, key);
}
void Window::clearBackground(Color color) {
    C_clearWindowBackground(window, color);
}