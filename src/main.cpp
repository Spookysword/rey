#include <grey/grey.h>
#include <grey/gui.h>

int main() {
    initGrey(4);

    Window win = createWindow(1280, 720, "grey");
    Texture block = newTexture(&win, "resources/block.png", FILTER_NEAREST);
    FontID arial = loadFont(&win, "resources/arial.ttf", 100);
    IconButton iconButton = createIconButton(0, 0, 500, 100, block, 30, 30, 30, arial, 50, "hello");
    iconButton.buttonStyle.borderSize = 7.5f;
    iconButton.buttonStyle.drawShape = STYLE_SHAPE_ROUNDED_RECT;
    iconButton.buttonStyle.roundedness = 15;

    while (!shouldWindowClose(win)) {
        updateWindow(&win);

        clearWindowBackground(&win, COLOR_DARK_GREY);

        //renderIconButton(win, &iconButton);
        //drawTexture(&win, block, 0, 0, 100, 100, 0, COLOR_WHITE);
        drawText(&win, "this text is at (0, 0)", arial, 0, 0, 50, COLOR_BLACK);

        renderWindow(win);
    }

    deleteTexture(&win, block);
    deleteFont(&win, arial);
    deleteWindow(&win);
    closeGrey();
}