#ifndef DRAWING_HPP
#define DRAWING_HPP

// clang-format off
#include <glad/glad.h>
// clang-format on

#include "RenderGlobals.h"
#include "input.h"

void MGL_drawRectangle(float posx, float posy, float width, float height, int r,
                       int g, int b);
void MGL_drawCircle(float posx, float posy, float radius, int r, int g, int b,
                    Anchor anchor);
void MGL_drawLine(float x1, float y1, float x2, float y2, int r, int g, int b);
void MGL_lineWidth(float width);

void MGL_beginDrawing();
void MGL_clearBackground(int r, int g, int b);
void MGL_endDrawing();

#endif
