#include "drawing.hpp"

void drawRectangle(float posx, float posy, float width, float height, int r,
                   int g, int b) {
  glm::vec3 rgb = glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f);
  myShader.setVec3("color", rgb);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(posx, posy, 0.0f));
  model = glm::scale(model, glm::vec3(width, height, 1.0f));
  myShader.setMat4("model", model);

  glBindVertexArray(rectangleVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void drawCircle(float posx, float posy, float radius, int r, int g, int b,
                Anchor anchor) {
  if (anchor == Anchor::TopLeft) {
    posx += radius;
    posy += radius;
  }

  glm::vec3 rgb = glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f);
  myShader.setVec3("color", rgb);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(posx, posy, 0.0f));
  model = glm::scale(model, glm::vec3(radius, radius, 1.0f));
  myShader.setMat4("model", model);

  glBindVertexArray(circleVAO);
  glDrawArrays(GL_TRIANGLE_FAN, 0, circleSegments + 2);
  glBindVertexArray(0);
}

void drawLine(float x1, float y1, float x2, float y2, int r, int g, int b) {
  glm::vec3 rgb = glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f);
  myShader.setVec3("color", rgb);

  glm::vec2 from(x1, y1);
  glm::vec2 to(x2, y2);

  glm::vec2 dir = to - from;
  float length = glm::length(dir);
  float angle = atan2(dir.y, dir.x);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(from, 0.0f));
  model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, glm::vec3(length, 1.0f, 1.0f));
  myShader.setMat4("model", model);

  glBindVertexArray(lineVAO);
  glDrawArrays(GL_LINES, 0, 2);
  glBindVertexArray(0);
}

void lineWidth(float width) { glLineWidth(width); }

void BeginDrawing() {
  processInput(frame);
  myShader.use();

  if (p == Perspectives::Orthographic) {
    glm::mat4 projection = glm::mat4(1.0f);
    projection =
        glm::ortho(0.0f, float(screenWidth), float(screenHeight), 0.0f);
    myShader.setMat4("projection", projection);
  } else if (p == Perspectives::Perspective) {
    glm::mat4 projection = glm::mat4(1.0f);
    float fov = glm::radians(45.0f);
    float aspectRatio = 800.0f / 600.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    projection = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
    myShader.setMat4("projection", projection);
  }
}

void ClearBackground(int r, int g, int b) {
  glClearColor(r / 255, g / 255, b / 255, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void EndDrawing() {
  glfwSwapBuffers(frame);
  glfwPollEvents();
}
