#include "test.h"

#include "grey/grey.hpp"
TEST_CASE("XGinit") {
    initGrey(0);
    closeGrey();
}

TEST_CASE("CGinit") {
    grey::initGrey(0);
    grey::closeGrey();
}
