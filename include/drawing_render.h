#ifndef DRAWING_RENDER_H
#define DRAWING_RENDER_H

//clang-format off
#include "shader.h"
//clang-format on

#include "RenderGlobals.h"
#include "camera.h"

void MGL_beginDrawing();
void MGL_activate2D();
void MGL_activate3D();
void MGL_clearBackground(int r, int g, int b);
void MGL_endDrawing();

#endif
