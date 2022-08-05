#include <grey/menu.hpp>

Menu::Menu(double x, double y, double width, double height, Color color) {
    style.x = x; style.y = y; style.width = width; style.height = height; style.normalColor = color;
}

unsigned int Menu::addButton(double x, double y, double width, double height) {
    Button b = createButton(x, y, width, height);
    buttons.push_back(b);
    return buttons.size() - 1;
}

void Menu::deleteButton(unsigned int buttonID) {
    //buttons.data()[buttonID] = nil;
    // NO CLUE how to do this
}

void Menu::drawMenu(Window win) {
    drawRectangle(&win, style.x, style.y, style.width, style.height, 0, style.normalColor);

    for (int i = 0; i < buttons.size(); i++) {
        renderButton(win, &buttons.data()[i]);
    }
}