#include "drawing.h"

#include <stdlib.h>

#include "RenderGlobals.h"

void MGL_drawRectangle(float posx, float posy, float width, float height) {
  vec3 rgb = {mgl_fillColor[0], mgl_fillColor[1], mgl_fillColor[2]};
  MGL_setVec3("color", &rgb);

  posx += mgl_currentTranslate[0];
  posy += mgl_currentTranslate[1];

  mat4 model;
  glm_mat4_identity(model);
  glm_translate(model, (vec3){posx, posy, 0.0f});
  glm_scale(model, (vec3){width, height, 1.0f});
  MGL_setMat4("model", &model);

  glBindVertexArray(mgl_rectangleVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void MGL_drawCircle(float posx, float posy, float radius) {
  // if (anchor == TopLeft) {
  //   posx += radius;
  //   posy += radius;
  // }

  vec3 rgb = {mgl_fillColor[0], mgl_fillColor[1], mgl_fillColor[2]};
  MGL_setVec3("color", &rgb);

  posx += mgl_currentTranslate[0];
  posy += mgl_currentTranslate[1];

  mat4 model;
  glm_mat4_identity(model);
  glm_translate(model, (vec3){posx, posy, 0.0f});
  glm_scale(model, (vec3){radius, radius, 1.0f});
  MGL_setMat4("model", &model);

  glBindVertexArray(mgl_circleVAO);
  glDrawArrays(GL_TRIANGLE_FAN, 0, mgl_circleSegments + 2);
  glBindVertexArray(0);
}

void MGL_drawLine(float x1, float y1, float x2, float y2) {
  vec3 rgb = {mgl_strokeColor[0], mgl_strokeColor[1], mgl_strokeColor[2]};
  MGL_setVec3("color", &rgb);

  vec2 from = {x1, y1};
  glm_vec2_add(from, mgl_currentTranslate, from);
  vec2 to = {x2, y2};
  glm_vec2_add(to, mgl_currentTranslate, to);

  vec2 dir;
  glm_vec2_sub(to, from, dir);
  float length = glm_vec2_norm(dir);
  float angle = atan2f(dir[1], dir[0]);

  mat4 model;
  glm_mat4_identity(model);
  glm_translate(model, (vec3){from[0], from[1], 0.0f});
  glm_rotate(model, angle, (vec3){0.0f, 0.0f, 1.0f});
  glm_scale(model, (vec3){length, 1.0f, 1.0f});
  MGL_setMat4("model", &model);

  glBindVertexArray(mgl_lineVAO);
  glDrawArrays(GL_LINES, 0, 2);
  glBindVertexArray(0);
}

void MGL_stroke(int r, int g, int b, int a) {
  mgl_strokeColor[0] = r;
  mgl_strokeColor[1] = g;
  mgl_strokeColor[2] = b;
  mgl_strokeColor[3] = a;
}

void MGL_fill(int r, int g, int b, int a) {
  mgl_fillColor[0] = r;
  mgl_fillColor[1] = g;
  mgl_fillColor[2] = b;
  mgl_fillColor[3] = a;
}

void MGL_strokeWeight(unsigned int value) { mgl_strokeWidth = value; }

void MGL_translate(int x, int y) {
  mgl_currentTranslate[0] += x;
  mgl_currentTranslate[1] += y;
}

void MGL_push() {
  mgl_translationHistorySize++;
  vec2* temp_ptr = realloc(mgl_translationHistory,
                           sizeof(vec2) * mgl_translationHistorySize);

  if (temp_ptr == NULL) {
    printf("Translation Allocation Error");
    return;
  }

  mgl_translationHistory = temp_ptr;

  memcpy(&mgl_translationHistory[mgl_translationHistorySize - 1],
         mgl_currentTranslate, sizeof(vec2));
}

void MGL_pop() {
  if (mgl_translationHistorySize <= 0) {
    return;
  }
  mgl_translationHistorySize--;

  mgl_currentTranslate[0] =
      mgl_translationHistory[mgl_translationHistorySize - 1][0];
  mgl_currentTranslate[1] =
      mgl_translationHistory[mgl_translationHistorySize - 1][1];
}

void MGL_drawRectangleLegacy(float posx, float posy, float width, float height,
                             int r, int g, int b) {
  vec3 rgb = {r / 255.0f, g / 255.0f, b / 255.0f};
  MGL_setVec3("color", &rgb);

  mat4 model;
  glm_mat4_identity(model);
  glm_translate(model, (vec3){posx, posy, 0.0f});
  glm_scale(model, (vec3){width, height, 1.0f});
  MGL_setMat4("model", &model);

  glBindVertexArray(mgl_rectangleVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void MGL_drawCircleLegacy(float posx, float posy, float radius, int r, int g,
                          int b, Anchor anchor) {
  if (anchor == TopLeft) {
    posx += radius;
    posy += radius;
  }

  vec3 rgb = {r / 255.0f, g / 255.0f, b / 255.0f};
  MGL_setVec3("color", &rgb);

  mat4 model;
  glm_mat4_identity(model);
  glm_translate(model, (vec3){posx, posy, 0.0f});
  glm_scale(model, (vec3){radius, radius, 1.0f});
  MGL_setMat4("model", &model);

  glBindVertexArray(mgl_circleVAO);
  glDrawArrays(GL_TRIANGLE_FAN, 0, mgl_circleSegments + 2);
  glBindVertexArray(0);
}

void MGL_drawLineLegacy(float x1, float y1, float x2, float y2, int r, int g,
                        int b) {
  vec3 rgb = {r / 255.0f, g / 255.0f, b / 255.0f};
  MGL_setVec3("color", &rgb);

  vec2 from = {x1, y1};
  vec2 to = {x2, y2};

  vec2 dir;
  glm_vec2_sub(to, from, dir);
  float length = glm_vec2_norm(dir);
  float angle = atan2f(dir[1], dir[0]);

  mat4 model;
  glm_mat4_identity(model);
  glm_translate(model, (vec3){from[0], from[1], 0.0f});
  glm_rotate(model, angle, (vec3){0.0f, 0.0f, 1.0f});
  glm_scale(model, (vec3){length, 1.0f, 1.0f});
  MGL_setMat4("model", &model);

  glBindVertexArray(mgl_lineVAO);
  glDrawArrays(GL_LINES, 0, 2);
  glBindVertexArray(0);
}

void MGL_lineWidth(float width) { glLineWidth(width); }

void MGL_beginDrawing() {
  MGL_processInput(mgl_frame);
  MGL_use();

  if (mgl_perspective == Orthographic) {
    mat4 projection;
    glm_ortho(0.0f, mgl_screenWidth, mgl_screenHeight, 0.0f, -1.0f, 1.0f,
              projection);
    MGL_setMat4("projection", &projection);
  } else if (mgl_perspective == Perspective) {
    mat4 projection;
    glm_mat4_identity(projection);
    float fov = glm_rad(45.0f);
    float aspectRatio = 800.0f / 600.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    glm_perspective(fov, aspectRatio, nearPlane, farPlane, projection);
    MGL_setMat4("projection", &projection);
  }

  mgl_currentTranslate[0] = 0;
  mgl_currentTranslate[1] = 0;
}

void MGL_clearBackground(int r, int g, int b) {
  glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void MGL_endDrawing() {
  glfwSwapBuffers(mgl_frame);
  glfwPollEvents();
}
