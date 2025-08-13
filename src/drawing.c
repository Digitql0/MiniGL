#include "drawing.h"

#include "RenderGlobals.h"
#include "camera.h"
#include "input.h"
#include "shader.h"

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
  from[0] += mgl_currentTranslate[0];
  from[1] += mgl_currentTranslate[1];
  vec2 to = {x2, y2};
  to[0] += mgl_currentTranslate[0];
  to[1] += mgl_currentTranslate[1];

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

  MGL_lineWidth(mgl_strokeWidth);

  glBindVertexArray(mgl_lineVAO);
  glDrawArrays(GL_LINES, 0, 2);
  glBindVertexArray(0);
}

void MGL_drawDot(float x1, float y1) {
  vec3 rgb = {mgl_strokeColor[0], mgl_strokeColor[1], mgl_strokeColor[2]};
  MGL_setVec3("color", &rgb);

  mat4 model;
  glm_mat4_identity(model);
  glm_translate(model, (vec3){x1, y1, 0.0f});
  MGL_setMat4("model", &model);

  MGL_setFloat("pointSize", mgl_strokeWidth);

  glBindVertexArray(mgl_dotVAO);
  glDrawArrays(GL_POINTS, 0, 1);
  glBindVertexArray(0);
}

void MGL_drawCube(float posx, float posy, float posz, float width, float height,
                  float depth) {
  vec3 rgb = {mgl_fillColor[0], mgl_fillColor[1], mgl_fillColor[2]};
  MGL_setVec3("color", &rgb);

  posx += mgl_currentTranslate[0];
  posy += mgl_currentTranslate[1];
  posz += mgl_currentTranslate[2];

  mat4 model;
  glm_mat4_identity(model);
  glm_translate(model, (vec3){posx, posy, posz});
  glm_scale(model, (vec3){width, height, depth});
  MGL_setMat4("model", &model);

  glBindVertexArray(mgl_cubeVAO);
  glDrawElements(GL_TRIANGLES, mgl_cubeIndexCount, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void MGL_drawSphere(float posx, float posy, float posz, float radius) {
  vec3 rgb = {mgl_fillColor[0], mgl_fillColor[1], mgl_fillColor[2]};
  MGL_setVec3("color", &rgb);

  posx += mgl_currentTranslate[0];
  posy += mgl_currentTranslate[1];
  posz += mgl_currentTranslate[2];

  mat4 model;
  glm_mat4_identity(model);
  glm_translate(model, (vec3){posx, posy, posz});
  glm_scale(model, (vec3){radius, radius, radius});
  MGL_setMat4("model", &model);

  glBindVertexArray(mgl_sphereVAO);
  for (int i = 0; i < mgl_sphereRings; i++) {
    glDrawElements(
        GL_TRIANGLE_STRIP, (mgl_sphereSegments + 1) * 2, GL_UNSIGNED_INT,
        (void*)(i * (mgl_sphereSegments + 1) * 2 * sizeof(unsigned int)));
  }

  glBindVertexArray(0);
}

void MGL_drawRay(float x1, float y1, float z1, float x2, float y2, float z2) {
  vec3 rgb = {mgl_strokeColor[0], mgl_strokeColor[1], mgl_strokeColor[2]};
  MGL_setVec3("color", &rgb);

  vec3 from = {x1, y1, z1};
  from[0] += mgl_currentTranslate[0];
  from[1] += mgl_currentTranslate[1];
  from[2] += mgl_currentTranslate[2];
  vec3 to = {x2, y2, z2};
  to[0] += mgl_currentTranslate[0];
  to[1] += mgl_currentTranslate[1];
  to[2] += mgl_currentTranslate[2];

  // Get Direction Vector and Normalize it
  vec3 dir;
  glm_vec3_sub(to, from, dir);
  float length = glm_vec3_norm(dir);
  if (length == 0.0f) length = 1e-6f;
  vec3 dirNormalized;
  glm_vec3_normalize_to(dir, dirNormalized);

  vec3 xAxis = {1.0f, 0.0f, 0.0f};
  vec3 rotationAxis;
  glm_vec3_cross(xAxis, dirNormalized, rotationAxis);
  float dot = glm_vec3_dot(xAxis, dirNormalized);
  float angle = acosf(dot);

  mat4 model;
  glm_mat4_identity(model);
  glm_translate(model, from);  // Move Ray to Start Point

  if (glm_vec3_norm(rotationAxis) < 1e-6f && dot <= 0) {
    glm_rotate(model, M_PI, (vec3){0.0f, 1.0f, 0.0f});
  } else {
    glm_rotate(model, angle, rotationAxis);
  }
  glm_scale(model, (vec3){length, 1.0f, 1.0f});

  MGL_setMat4("model", &model);

  MGL_lineWidth(mgl_strokeWidth);

  glBindVertexArray(mgl_rayVAO);
  glDrawArrays(GL_LINES, 0, 2);
  glBindVertexArray(0);
}

void MGL_drawPoint(float x1, float y1, float z1) {
  vec3 rgb = {mgl_strokeColor[0], mgl_strokeColor[1], mgl_strokeColor[2]};
  MGL_setVec3("color", &rgb);

  mat4 model;
  glm_mat4_identity(model);
  glm_translate(model, (vec3){x1, y1, z1});
  MGL_setMat4("model", &model);

  MGL_setFloat("pointSize", mgl_strokeWidth);
  printf("%f\n", mgl_strokeWidth);

  glBindVertexArray(mgl_pointVAO);
  glDrawArrays(GL_POINTS, 0, 1);
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

void MGL_translate(float x, float y, float z) {
  mgl_currentTranslate[0] += x;
  mgl_currentTranslate[1] += y;
  mgl_currentTranslate[2] += z;
}

void MGL_push() {
  mgl_translationHistorySize++;
  vec3* temp_ptr = realloc(mgl_translationHistory,
                           sizeof(vec3) * mgl_translationHistorySize);

  if (temp_ptr == NULL) {
    printf("Translation Allocation Error");
    return;
  }

  mgl_translationHistory = temp_ptr;

  memcpy(&mgl_translationHistory[mgl_translationHistorySize - 1],
         mgl_currentTranslate, sizeof(vec3));
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
  mgl_currentTranslate[2] =
      mgl_translationHistory[mgl_translationHistorySize - 1][2];
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
  if (MGL_processInput != NULL) {
    MGL_processInput();  // Compute Input
  }

  MGL_use();  // Activate Shader

  mgl_currentTranslate[0] = 0;
  mgl_currentTranslate[1] = 0;
  mgl_currentTranslate[2] = 0;
}

void MGL_activate2D() { glDisable(GL_DEPTH_TEST); }

void MGL_activate3D() { glEnable(GL_DEPTH_TEST); }

void MGL_clearBackground(int r, int g, int b) {
  glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MGL_endDrawing() {
  Camera* cam = MGLC_getCamera();
  MGLC_updateMatrices(cam);

  MGL_setMat4("projection", &cam->projection);
  MGL_setMat4("view", &cam->view);

  glfwSwapBuffers(mgl_frame);
  glfwPollEvents();
}
