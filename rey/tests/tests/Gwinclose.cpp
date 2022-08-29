#include "test.h"

#include "grey/grey.hpp"
TEST_CASE("CXGopenwindow") {
    initGrey(0);
    Window win(100, 100, "testwindow");
    CHECK(win.isopen() == true);
    win.close();
    CHECK(win.isopen() == false);
    win.del();
    closeGrey();
}

TEST_CASE("CCGopenwindow") {
    grey::initGrey(0);
    grey::Window win = grey::createWindow(100, 100, "testwindow");
    CHECK(grey::shouldWindowClose(win) == false);
    grey::closeWindow(win);
    CHECK(grey::shouldWindowClose(win) == true);
    grey::deleteWindow(&win);
    grey::closeGrey();
}