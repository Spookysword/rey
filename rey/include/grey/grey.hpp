#pragma once
#define GREY_ENABLE_NAMESPACE
#include <grey/grey.h>

using grey::initGrey;
using grey::closeGrey;
using grey::Color;

class Window {
public:
    grey::Window* win;
    Window(int width, int height, const char* title) {
        grey::Window window = grey::createWindow(width, height, title);
        this->win = &window;
    }
    ~Window() {
        grey::deleteWindow(this->win);
    }
    explicit operator bool() { 
        return grey::shouldWindowClose(*this->win); 
    }
    void update() {
        grey::updateWindow(this->win);
    }
    void render() {
        grey::renderWindow(*this->win);
    }
    void del() {
        grey::deleteWindow(this->win);
    }
    bool isKeyDown(int key) {
        return grey::isKeyDown(*this->win, key);
    }
    bool isKeyPressed(int key) {
        return grey::isKeyPressed(*this->win, key);
    }
    void close() {
        grey::closeWindow(*this->win);
    }
    void setFlag(uint32_t flag, bool state) {
        grey::setWindowFlag(*this->win, flag, state);
    }
    void clearColor(Color color) {
        grey::clearWindowBackground(this->win, color);
    }
    void setWireframe(bool state) {
        grey::setWireframeMode(*this->win, state);
    }
    void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Color color=COLOR_WHITE) {
        grey::drawTriangle(this->win, x1, y1, x2, y2, x3, y3, color);
    }
    void drawRectangle(float x, float y, float width, float height, float rotation=0, Color color=COLOR_WHITE) {
        grey::drawRectangle(this->win, x, y, width, height, rotation, color);
    }
};