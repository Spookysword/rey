#pragma once

#include "mrey/mrey.h"
extern "C" {
#include "grey/grey/vertices.h"
}
#ifdef __cplusplus
namespace grey {
#endif
Vertices loadObj(const char* objFile, bool autoCalcNormals, Color color);
#ifdef __cplusplus
}
#endif