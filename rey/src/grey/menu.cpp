#include <grey/menu.hpp>

Menu::Menu(double x, double y, double width, double height, Color color) {
    style.x = x; style.y = y; style.width = width; style.height = height; style.normalColor = color;
    style.borderColor = COLOR_BLACK;
    style.borderSize = 0;
    style.drawShape = STYLE_SHAPE_RECT;
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
    switch (style.drawShape) {
    default:
        break;
    case STYLE_SHAPE_RECT:
        drawRectangle(&win, style.x, style.y, style.width, style.height, 0, style.normalColor);
		if (style.borderSize > 0) {
			drawRectangle(&win, style.x, style.y, style.width, style.borderSize, 0, style.borderColor);
			drawRectangle(&win, style.x, (style.y + style.height) - style.borderSize, style.width, style.borderSize, 0, style.borderColor);
			drawRectangle(&win, style.x, style.y + style.borderSize, style.borderSize, style.height - (style.borderSize * 2.0), 0, style.borderColor);
			drawRectangle(&win, (style.x + style.width) - style.borderSize, style.y + style.borderSize, style.borderSize, style.height - (style.borderSize * 2.0), 0, style.borderColor);
		}
        break;
    case STYLE_SHAPE_ROUNDED_RECT:
        if (style.borderSize > 0) {
			drawRoundedRect(&win, style.x, style.y, style.width, style.height, style.roundedness, 0, style.borderColor);
			drawRoundedRect(&win, style.x + style.borderSize, style.y + style.borderSize, style.width - (style.borderSize * 2.0), style.height - (style.borderSize * 2.0), style.roundedness / 1.5f, 0, style.normalColor);
		}
		else {
			drawRoundedRect(&win, style.x, style.y, style.width, style.height, style.roundedness, 0, style.normalColor);
		}
        break;
    }

    for (int i = 0; i < buttons.size(); i++) {
        buttons[i].style.x += style.x;
        buttons[i].style.y += style.y;
        renderButton(win, &buttons[i]);
        buttons[i].style.x -= style.x;
        buttons[i].style.y -= style.y;
    }
}