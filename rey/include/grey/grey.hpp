#pragma once
#define GREY_ENABLE_NAMESPACE
#include <grey/grey.h>
#include <string>
#include <vector>

using grey::initGrey;
using grey::closeGrey;
using grey::Color;
using grey::Texture;
using grey::FontID;
using grey::Vertice;
using grey::Vertices;

class Window {
public:
    grey::Window win;
    Window(int width, int height, const char* title) {
        win = grey::createWindow(width, height, title);
    }
    explicit operator bool() { 
        return !grey::shouldWindowClose(this->win); 
    }
    void update() {
        grey::updateWindow(&this->win);
    }
    void render() {
        grey::renderWindow(this->win);
    }
    void del() {
        grey::deleteWindow(&this->win);
    }
    bool isKeyDown(int key) {
        return grey::isKeyDown(this->win, key);
    }
    bool isKeyPressed(int key) {
        return grey::isKeyPressed(this->win, key);
    }
    void close() {
        grey::closeWindow(this->win);
    }
    void setFlag(uint32_t flag, bool state) {
        grey::setWindowFlag(this->win, flag, state);
    }
    void clearColor(Color color) {
        grey::clearWindowBackground(&this->win, color);
    }
    void setWireframe(bool state) {
        grey::setWireframeMode(this->win, state);
    }
    void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Color color=COLOR_WHITE) {
        grey::drawTriangle(&this->win, x1, y1, x2, y2, x3, y3, color);
    }
    void drawRectangle(float x, float y, float width, float height, float rotation=0, Color color=COLOR_WHITE) {
        grey::drawRectangle(&this->win, x, y, width, height, rotation, color);
    }
    void drawRectangle(Vec2 pos, Vec2 size, float rotation=0, Color color=COLOR_WHITE) {
        grey::drawRectangle(&this->win, pos.x, pos.y, size.x, size.y, rotation, color);
    }
    void drawTexture(Texture texture, float x, float y, float width, float height, float rotation=0, Color color=COLOR_WHITE) {
        grey::drawTexture(&this->win, texture, x, y, width, height, rotation, color);
    }
    void drawCircle(float x, float y, float radius, Color color=COLOR_WHITE) {
        grey::drawCircle(&this->win, x, y, radius, color);
    }
    void drawRoundedRect(float x, float y, float width, float height, float radius, float rotation=0, Color color=COLOR_WHITE) {
        grey::drawRoundedRect(&this->win, x, y, width, height, radius, rotation, color);
    }
    void drawText(const char* text, FontID font, float x, float y, float scale, Color color=COLOR_WHITE) {
        grey::drawText(&this->win, text, font, x, y, scale, color);
    }
    void drawText(std::string text, FontID font, float x, float y, float scale, Color color=COLOR_WHITE) {
        grey::drawText(&this->win, text.c_str(), font, x, y, scale, color);
    }
    void drawBorderedText(const char* text, FontID font, float x, float y, float scale, float borderSize, Color color=COLOR_WHITE, Color borderColor=COLOR_BLACK) {
        grey::drawBorderedText(&this->win, text, font, x, y, scale, borderSize, color, borderColor);
    }
    void drawBorderedText(std::string text, FontID font, float x, float y, float scale, float borderSize, Color color=COLOR_WHITE, Color borderColor=COLOR_BLACK) {
        grey::drawBorderedText(&this->win, text.c_str(), font, x, y, scale, borderSize, color, borderColor);
    }
    float getWidthOfText(const char* text, FontID font, float scale) {
        return grey::getWidthOfText(&this->win, text, font, scale);
    }
    float getWidthOfText(std::string text, FontID font, float scale) {
        return grey::getWidthOfText(&this->win, text.c_str(), font, scale);
    }
    float getHeightOfText(const char* text, FontID font, float scale) {
        return grey::getHeightOfText(&this->win, text, font, scale);
    }
    float getHeightOfText(std::string text, FontID font, float scale) {
        return grey::getHeightOfText(&this->win, text.c_str(), font, scale);
    }
    void drawPolygon(float* xs, float* ys, int points, Color color=COLOR_WHITE) {
        grey::drawPolygon(&this->win, xs, ys, points, color);
    }
    void drawAdvancedRect(float x, float y, float width, float height, float rotation, Color topLeft=COLOR_WHITE, Color topRight=COLOR_WHITE, Color bottomLeft=COLOR_WHITE, Color bottomRight=COLOR_WHITE) {
        grey::drawAdvancedRect(&this->win, x, y, width, height, rotation, topLeft, topRight, bottomLeft, bottomRight);
    }
    void drawAdvancedTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Color bottomLeft=COLOR_WHITE, Color topMiddle=COLOR_WHITE, Color bottomRight=COLOR_WHITE) {
        grey::drawAdvancedTriangle(&this->win, x1, y1, x2, y2, x3, y3, bottomLeft, topMiddle, bottomRight);
    }
    void drawLine(float x1, float y1, float x2, float y2, float thickness=2, Color color=COLOR_WHITE) {
        grey::drawLine(&this->win, x1, y1, x2, y2, thickness, color);
    }
    void drawAdvancedLine(float x1, float y1, float x2, float y2, float thickness=2, Color color1=COLOR_WHITE, Color color2=COLOR_WHITE) {
        grey::drawAdvancedLine(&this->win, x1, y1, x2, y2, thickness, color1, color2);
    }
    void draw3DShape(Texture texture, Vertices vertices) {
        grey::draw3DShape(&this->win, texture, vertices);
    }
    Texture loadTexture(const char* path, int filter=FILTER_LINEAR) {
        return grey::newTexture(&this->win, path, filter);
    }
    FontID loadFont(const char* filePath, float size) {
        return grey::loadFont(&this->win, filePath, size);
    }
    std::vector<std::vector<Color>> loadTexturePixels(Texture texture) {
        stbi_set_flip_vertically_on_load(FALSE);
        glBindTexture(GL_TEXTURE_2D, win.shaders.data[win.currentShader].textures.data[texture].textureID);
        int w, h;
        int miplevel = 0;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &w);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &h);
        GLubyte* pixels = new GLubyte[w*h*4];
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        std::vector<std::vector<Color>> colors;
        for (int i = 0; i < w; i++) {
            std::vector<Color> row;
            for (int j = 0; j < h; j++) {
                int r = j*w*4;
                int c = i*4;
                row.push_back(Color(pixels[r+c], pixels[r+c+1], pixels[r+c+2], pixels[r+c+3]));
            }
            colors.push_back(row);
        }
        delete[] pixels;
        return colors;
    }
};

operator!=(const Vec2& a, const Vec2& b) {
    return a.x != b.x || a.y != b.y;
}