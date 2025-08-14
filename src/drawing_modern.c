#include "drawing_modern.h"

void MGL_drawRectangle(float posx, float posy, float width, float height) {
  vec3 rgb = {mgl_fillColor[0], mgl_fillColor[1], mgl_fillColor[2]};
  if (mgl_lightEnabled == 1) {
    MGL_setVec3(mgl_objectShaderID, "objectColor", &rgb);
  } else {
    MGL_setVec3(mgl_lightObjectShaderID, "color", &rgb);
  }

  posx += mgl_currentTranslate[0];
  posy += mgl_currentTranslate[1];

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
void MGL_drawCircle(float posx, float posy, float radius) {
  vec3 rgb = {mgl_fillColor[0], mgl_fillColor[1], mgl_fillColor[2]};
  if (mgl_lightEnabled == 1) {
    MGL_setVec3(mgl_objectShaderID, "objectColor", &rgb);
  } else {
    MGL_setVec3(mgl_lightObjectShaderID, "color", &rgb);
  }

  posx += mgl_currentTranslate[0];
  posy += mgl_currentTranslate[1];

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

void MGL_drawLine(float x1, float y1, float x2, float y2) {
  vec3 rgb = {mgl_strokeColor[0], mgl_strokeColor[1], mgl_strokeColor[2]};
  if (mgl_lightEnabled == 1) {
    MGL_setVec3(mgl_objectShaderID, "objectColor", &rgb);
  } else {
    MGL_setVec3(mgl_lightObjectShaderID, "color", &rgb);
  }

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
  if (mgl_lightEnabled == 1) {
    MGL_setMat4(mgl_objectShaderID, "model", &model);
  } else {
    MGL_setMat4(mgl_lightObjectShaderID, "model", &model);
  }

  MGL_lineWidth(mgl_strokeWidth);

  glBindVertexArray(mgl_lineVAO);
  glDrawArrays(GL_LINES, 0, 2);
  glBindVertexArray(0);
}

void MGL_drawDot(float x1, float y1) {
  vec3 rgb = {mgl_strokeColor[0], mgl_strokeColor[1], mgl_strokeColor[2]};
  if (mgl_lightEnabled == 1) {
    MGL_setVec3(mgl_objectShaderID, "objectColor", &rgb);
  } else {
    MGL_setVec3(mgl_lightObjectShaderID, "color", &rgb);
  }

  mat4 model;
  glm_mat4_identity(model);
  glm_translate(model, (vec3){x1, y1, 0.0f});
  if (mgl_lightEnabled == 1) {
    MGL_setMat4(mgl_objectShaderID, "model", &model);
  } else {
    MGL_setMat4(mgl_lightObjectShaderID, "model", &model);
  }

  if (mgl_lightEnabled == 1) {
    MGL_setFloat(mgl_objectShaderID, "pointSize", mgl_strokeWidth);
  } else {
    MGL_setFloat(mgl_lightObjectShaderID, "pointSize", mgl_strokeWidth);
  }

  glBindVertexArray(mgl_dotVAO);
  glDrawArrays(GL_POINTS, 0, 1);
  glBindVertexArray(0);
}

void MGL_drawCube(float posx, float posy, float posz, float width, float height,
                  float depth) {
  vec3 rgb = {mgl_fillColor[0] / 255.0f, mgl_fillColor[1] / 255.0f,
              mgl_fillColor[2] / 255.0f};
  if (mgl_lightEnabled == 1) {
    MGL_setVec3(mgl_objectShaderID, "objectColor", &rgb);
  } else {
    MGL_setVec3(mgl_lightObjectShaderID, "color", &rgb);
  }

  posx += mgl_currentTranslate[0];
  posy += mgl_currentTranslate[1];
  posz += mgl_currentTranslate[2];

  mat4 model;
  glm_mat4_identity(model);
  glm_translate(model, (vec3){posx, posy, posz});
  glm_scale(model, (vec3){width, height, depth});
  if (mgl_lightEnabled == 1) {
    // MGL_setVec3(mgl_objectShaderID, "objectColor", &(vec3){255, 255, 255});
    MGL_setMat4(mgl_objectShaderID, "model", &model);
  } else {
    MGL_setMat4(mgl_lightObjectShaderID, "model", &model);
  }

  glBindVertexArray(mgl_cubeVAO);
  glDrawElements(GL_TRIANGLES, mgl_cubeIndexCount, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void MGL_drawSphere(float posx, float posy, float posz, float radius) {
  vec3 rgb = {mgl_fillColor[0], mgl_fillColor[1], mgl_fillColor[2]};
  if (mgl_lightEnabled == 1) {
    MGL_setVec3(mgl_objectShaderID, "objectColor", &rgb);
  } else {
    MGL_setVec3(mgl_lightObjectShaderID, "color", &rgb);
  }

  posx += mgl_currentTranslate[0];
  posy += mgl_currentTranslate[1];
  posz += mgl_currentTranslate[2];

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

void MGL_drawRay(float x1, float y1, float z1, float x2, float y2, float z2) {
  vec3 rgb = {mgl_strokeColor[0], mgl_strokeColor[1], mgl_strokeColor[2]};
  if (mgl_lightEnabled == 1) {
    MGL_setVec3(mgl_objectShaderID, "objectColor", &rgb);
  } else {
    MGL_setVec3(mgl_lightObjectShaderID, "color", &rgb);
  }

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

  if (mgl_lightEnabled == 1) {
    MGL_setMat4(mgl_objectShaderID, "model", &model);
  } else {
    MGL_setMat4(mgl_lightObjectShaderID, "model", &model);
  }

  MGL_lineWidth(mgl_strokeWidth);

  glBindVertexArray(mgl_rayVAO);
  glDrawArrays(GL_LINES, 0, 2);
  glBindVertexArray(0);
}

void MGL_drawPoint(float x1, float y1, float z1) {
  vec3 rgb = {mgl_strokeColor[0], mgl_strokeColor[1], mgl_strokeColor[2]};
  if (mgl_lightEnabled == 1) {
    MGL_setVec3(mgl_objectShaderID, "objectColor", &rgb);
  } else {
    MGL_setVec3(mgl_lightObjectShaderID, "color", &rgb);
  }

  mat4 model;
  glm_mat4_identity(model);
  glm_translate(model, (vec3){x1, y1, z1});
  if (mgl_lightEnabled == 1) {
    MGL_setMat4(mgl_objectShaderID, "model", &model);
  } else {
    MGL_setMat4(mgl_lightObjectShaderID, "model", &model);
  }

  if (mgl_lightEnabled == 1) {
    MGL_setFloat(mgl_objectShaderID, "pointSize", mgl_strokeWidth);
  } else {
    MGL_setFloat(mgl_lightObjectShaderID, "pointSize", mgl_strokeWidth);
  }
  printf("%f\n", mgl_strokeWidth);

  glBindVertexArray(mgl_pointVAO);
  glDrawArrays(GL_POINTS, 0, 1);
  glBindVertexArray(0);
}
