#include "drawing.h"

void MGL_drawRectangle(float posx, float posy, float width, float height, int r,
                       int g, int b) {
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

void MGL_drawCircle(float posx, float posy, float radius, int r, int g, int b,
                    Anchor anchor) {
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

void MGL_drawLine(float x1, float y1, float x2, float y2, int r, int g, int b) {
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
}

void MGL_clearBackground(int r, int g, int b) {
  glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void MGL_endDrawing() {
  glfwSwapBuffers(mgl_frame);
  glfwPollEvents();
}
