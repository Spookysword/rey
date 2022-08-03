#include <grey/grey.h>
#include <grey/gui.h>

int main() {
    initGrey(4);

    Window win = createWindow(1280, 720, "grey");
    Texture block = newTexture(&win, "resources/block.png", FILTER_NEAREST);
    //FontID arial = loadFont(&win, "resources/arial.ttf", 100);
    //IconButton iconButton = createIconButton(0, 0, 500, 100, block, 0, 0, 25, arial, 50, "hello");

    while (!shouldWindowClose(win)) {
        updateWindow(&win);

        //renderIconButton(win, &iconButton);
        drawTexture(&win, block, 0, 0, 100, 100, 0, COLOR_WHITE);

        renderWindow(win);
    }

    deleteWindow(&win);
    closeGrey();
}