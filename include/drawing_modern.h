#ifndef DRAWING_MODERN_H
#define DRAWING_MODERN_H

//clang-format off
#include "shader.h"
//clang-format on

#include "RenderGlobals.h"
#include "drawing_style.h"

void MGL_drawRectangle(float posx, float posy, float width, float height);
void MGL_drawCircle(float posx, float posy, float radius);
void MGL_drawLine(float x1, float y1, float x2, float y2);
void MGL_drawDot(float x1, float y1);
void MGL_drawCube(float posx, float posy, float posz, float width, float height,
                  float depth);
void MGL_drawSphere(float posx, float posy, float posz, float radius);
void MGL_drawRay(float x1, float y1, float z1, float x2, float y2, float z2);
void MGL_drawPoint(float x1, float y1, float z1);

#endif
