#ifndef DRAWING_LEGACY_H
#define DRAWING_LEGACY_H

//clang-format off
#include "shader.h"
//clang-format on

#include "RenderGlobals.h"

void MGL_drawRectangleLegacy(float posx, float posy, float width, float height,
                             int r, int g, int b);
void MGL_drawCircleLegacy(float posx, float posy, float radius, int r, int g,
                          int b, Anchor anchor);
void MGL_drawLineLegacy(float x1, float y1, float x2, float y2, int r, int g,
                        int b);
void MGL_drawDotLegacy(float x1, float y1, int r, int g, int b);

void MGL_drawCubeLegacy(float posx, float posy, float posz, float width,
                        float height, float depth, int r, int g, int b);
void MGL_drawSphereLegacy(float posx, float posy, float posz, float radius,
                          int r, int g, int b);
void MGL_drawRayLegacy(float x1, float y1, float z1, float x2, float y2,
                       float z2, int r, int g, int b);
void MGL_drawPointLegacy(float x1, float y1, float z1, int r, int g, int b);

#endif
