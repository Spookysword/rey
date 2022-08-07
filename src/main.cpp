#include <grey/grey.h>
#include <grey/menu.hpp>
#include <arey/arey.hpp>

int main() {
    initGrey(4);
    initArey();

    Window win = createWindow(1280, 720, "grey");

    while (!shouldWindowClose(win)) {
        updateWindow(&win);

        if (isKeyPressed(win, KEY_F11)) {
            win.fullscreen = !win.fullscreen;
        }

        clearWindowBackground(&win, COLOR_DARK_GREY);

        renderWindow(win);
    }
    
    deleteWindow(&win);
    closeGrey();
    closeArey();
}