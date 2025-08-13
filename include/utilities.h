#ifndef UTILITIES_H
#define UTILITIES_H

#include "RenderGlobals.h"

vec2* MGL_getTranslation();
void MGL_euler_to_quat(float pitch, float yaw, float roll, versor q);

#endif
