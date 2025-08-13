#ifndef DRAWING_HPP
#define DRAWING_HPP

// clang-format off
#include <glad/glad.h>
// clang-format on

#include <string.h>

#include "RenderGlobals.h"
#include "camera.h"
#include "input.h"
#include "utilities.h"

void MGL_drawRectangle(float posx, float posy, float width, float height);
void MGL_drawCircle(float posx, float posy, float radius);
void MGL_drawLine(float x1, float y1, float x2, float y2);
void MGL_drawDot(float x1, float y1);

void MGL_drawCube(float posx, float posy, float posz, float width, float height,
                  float depth);
void MGL_drawSphere(float posx, float posy, float posz, float radius);
void MGL_drawRay(float x1, float y1, float z1, float x2, float y2, float z2);
void MGL_drawPoint(float x1, float y1, float z1);

void MGL_stroke(int r, int g, int b, int a);
void MGL_fill(int r, int g, int b, int a);
void MGL_strokeWeight(unsigned int value);
void MGL_translate(float x, float y, float z);
void MGL_push();
void MGL_pop();

void MGL_drawRectangleLegacy(float posx, float posy, float width, float height,
                             int r, int g, int b);
void MGL_drawCircleLegacy(float posx, float posy, float radius, int r, int g,
                          int b, Anchor anchor);
void MGL_drawLineLegacy(float x1, float y1, float x2, float y2, int r, int g,
                        int b);
void MGL_lineWidth(float width);

void MGL_beginDrawing();
void MGL_activate2D();
void MGL_activate3D();
void MGL_clearBackground(int r, int g, int b);
void MGL_endDrawing();

#endif
