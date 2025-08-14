#include "drawing_legacy.h"

void MGL_drawRectangleLegacy(float posx, float posy, float width, float height,
                             int r, int g, int b) {
  vec3 rgb = {r / 255.0f, g / 255.0f, b / 255.0f};
  if (mgl_lightEnabled == 1) {
    MGL_setVec3(mgl_objectShaderID, "objectColor", &rgb);
  } else {
    MGL_setVec3(mgl_lightObjectShaderID, "color", &rgb);
  }

  mat4 model;
  glm_mat4_identity(model);
  glm_translate(model, (vec3){posx, posy, 0.0f});
  glm_scale(model, (vec3){width, height, 1.0f});
  if (mgl_lightEnabled == 1) {
    MGL_setMat4(mgl_objectShaderID, "model", &model);
  } else {
    MGL_setMat4(mgl_lightObjectShaderID, "model", &model);
  }

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
  if (mgl_lightEnabled == 1) {
    MGL_setVec3(mgl_objectShaderID, "objectColor", &rgb);
  } else {
    MGL_setVec3(mgl_lightObjectShaderID, "color", &rgb);
  }

  mat4 model;
  glm_mat4_identity(model);
  glm_translate(model, (vec3){posx, posy, 0.0f});
  glm_scale(model, (vec3){radius, radius, 1.0f});
  if (mgl_lightEnabled == 1) {
    MGL_setMat4(mgl_objectShaderID, "model", &model);
  } else {
    MGL_setMat4(mgl_lightObjectShaderID, "model", &model);
  }

  glBindVertexArray(mgl_circleVAO);
  glDrawArrays(GL_TRIANGLE_FAN, 0, mgl_circleSegments + 2);
  glBindVertexArray(0);
}
void MGL_drawLineLegacy(float x1, float y1, float x2, float y2, int r, int g,
                        int b) {
  vec3 rgb = {r / 255.0f, g / 255.0f, b / 255.0f};
  if (mgl_lightEnabled == 1) {
    MGL_setVec3(mgl_objectShaderID, "objectColor", &rgb);
  } else {
    MGL_setVec3(mgl_lightObjectShaderID, "color", &rgb);
  }

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

  if (mgl_lightEnabled == 1) {
    MGL_setMat4(mgl_objectShaderID, "model", &model);
  } else {
    MGL_setMat4(mgl_lightObjectShaderID, "model", &model);
  }

  glBindVertexArray(mgl_lineVAO);
  glDrawArrays(GL_LINES, 0, 2);
  glBindVertexArray(0);
}
void MGL_drawDotLegacy(float x1, float y1, int r, int g, int b);
void MGL_drawCubeLegacy(float posx, float posy, float posz, float width,
                        float height, float depth, int r, int g, int b);
void MGL_drawSphereLegacy(float posx, float posy, float posz, float radius,
                          int r, int g, int b) {
  vec3 rgb = {r, g, b};
  if (mgl_lightEnabled == 1) {
    MGL_setVec3(mgl_objectShaderID, "objectColor", &rgb);
  } else {
    MGL_setVec3(mgl_lightObjectShaderID, "color", &rgb);
  }

  mat4 model;
  glm_mat4_identity(model);
  glm_translate(model, (vec3){posx, posy, posz});
  glm_scale(model, (vec3){radius, radius, radius});
  if (mgl_lightEnabled == 1) {
    MGL_setMat4(mgl_objectShaderID, "model", &model);
  } else {
    MGL_setMat4(mgl_lightObjectShaderID, "model", &model);
  }

  glBindVertexArray(mgl_sphereVAO);
  for (int i = 0; i < mgl_sphereRings; i++) {
    glDrawElements(
        GL_TRIANGLE_STRIP, (mgl_sphereSegments + 1) * 2, GL_UNSIGNED_INT,
        (void*)(i * (mgl_sphereSegments + 1) * 2 * sizeof(unsigned int)));
  }

  glBindVertexArray(0);
}
void MGL_drawRayLegacy(float x1, float y1, float z1, float x2, float y2,
                       float z2, int r, int g, int b);
void MGL_drawPointLegacy(float x1, float y1, float z1, int r, int g, int b);
