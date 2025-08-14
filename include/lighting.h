#ifndef LIGHTING_H
#define LIGHTING_H

// clang-format off
#include "shader.h"
#include "drawing.h"
// clang-format on

void initializePointLightVBO();
void enableLight(int a);
void drawLightObjects();
void setPointLight();

#endif
