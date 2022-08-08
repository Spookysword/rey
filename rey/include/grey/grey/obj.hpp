#pragma once

#include "mrey/mrey.h"
extern "C" {
#include "grey/grey/vertices.h"
}
Vertices loadObj(const char* objFile, bool autoCalcNormals, Color color);