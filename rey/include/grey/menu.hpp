#ifndef MENU_H
#define MENU_H

#include <grey/gui.h>
#include <vector>

class Menu {
public:
    Style style;

    Menu(double x, double y, double width, double height, Color color);

    std::vector<Button> buttons;
    unsigned int addButton(double x, double y, double width, double height);
    void deleteButton(unsigned int buttonID);
    void drawMenu(Window win);
};

#endif // MENU_H