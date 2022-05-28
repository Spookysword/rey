#include "grey++"

void initGrey(unsigned int sampleRate) {
    C_initGrey(sampleRate);
}

void closeGrey() {
    C_closeGrey();
}


Window::Window(int width, int height, const char* title) {
    win = C_createWindow(width, height, title);
}
Window::Window(int width, int height, std::string title) {
    win = C_createWindow(width, height, title.c_str());
}
bool Window::shouldClose() {
    return C_shouldWindowClose(win);
}
void Window::update() {
    C_updateWindow(&win);
    deltaTime = win.deltaTime;
    title = win.title;
}
void Window::render() {
    C_renderWindow(win);
}
void Window::close() {
    C_closeWindow(win);
}
void Window::setFlag(uint32_t flag, bool state) {
    C_setWindowFlag(win, flag, state);
}
bool Window::isKeyDown(int key) {
    return C_isKeyDown(win, key);
}
void Window::clearBackground(Color color) {
    C_clearWindowBackground(win, color);
}
void Window::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Color color) {
    C_drawTriangle(&win, x1, y1, x2, y2, x3, y3, color);
}
void Window::drawRectangle(float x, float y, float width, float height, Color color) {
    C_drawRectangle(&win, x, y, width, height, color);
}