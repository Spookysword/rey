#include "test.h"

#include "grey/grey.hpp"
TEST_CASE("CXGopenwindow") {
    initGrey(0);
    Window win(100, 100, "testwindow");
    CHECK(win.win.windowHandle != NULL);
    CHECK(win.win.title == "testwindow");
    CHECK(win.win.width == 100);
    CHECK(win.win.height == 100);
    win.del();
    closeGrey();
}

TEST_CASE("CCGopenwindow") {
    grey::initGrey(0);
    grey::Window win = grey::createWindow(100, 100, "testwindow");
    CHECK(win.windowHandle != NULL);
    CHECK(win.title == "testwindow");
    CHECK(win.width == 100);
    CHECK(win.height == 100);
    grey::deleteWindow(&win);
    grey::closeGrey();
}