#include <grey/grey.h>
#include <grey/menu.hpp>

int main() {
    initGrey(4);

    Window win = createWindow(1280, 720, "grey");
    Texture block = newTexture(&win, "resources/block.png", FILTER_NEAREST);
    FontID arial = loadFont(&win, "resources/arial.ttf", 100);
    Menu menu(0, 0, 200, 200, COLOR_BLACK);
    menu.addButton(0, 0, 100, 100);

    while (!shouldWindowClose(win)) {
        updateWindow(&win);

        clearWindowBackground(&win, COLOR_DARK_GREY);

        menu.drawMenu(win);

        renderWindow(win);
    }

    deleteTexture(&win, block);
    deleteFont(&win, arial);
    deleteWindow(&win);
    closeGrey();
}