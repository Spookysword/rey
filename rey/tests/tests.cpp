#define DOCTEST_CONFIG_IMPLEMENT
#include "test.h"

int main(int argc, char** argv) {
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    return context.run(); 
} 