#define IMPLEMENT_GREY_H
#include "grey.h"

void initGrey(unsigned int sampleRate = 4);

void closeGrey();

class Window {
public:
    C_Window window;
    Window(int width, int height, const char* title);
    bool shouldClose();
    void update();
    void render();
    void close();
    void setFlag(uint32_t flag, bool state);
    bool isKeyDown(int key);
    void clearBackground(Color color);

};