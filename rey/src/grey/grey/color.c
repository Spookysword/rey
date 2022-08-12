#include "grey/grey/color.h"
#ifdef __cplusplus
namespace grey {
#endif
	void setColor(Color* oldColor, Color newColor) {
    #ifdef __cplusplus
	    *oldColor = newColor;
    #else
        oldColor[0][0] = newColor[0];
        oldColor[0][1] = newColor[1];
        oldColor[0][2] = newColor[2];
        oldColor[0][3] = newColor[3];
    #endif
}
#ifdef __cplusplus
}
#endif