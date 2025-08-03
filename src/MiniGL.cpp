#include "MiniGL.hpp"

#include <iostream>
#include <vector>

// Mathematics
#include "RenderGlobals.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shader.hpp"

void setPerspective(Perspectives perspective) { p = perspective; }

bool WindowShouldClose() { return glfwWindowShouldClose(frame); }

void CloseWindow() { glfwTerminate(); }

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

void glfwSetup() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void GLADSetup() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD." << std::endl;
    exit(EXIT_FAILURE);
  }
}

void MakeWindow(int width, int height, const char* title) {
  std::cout << "1" << std::endl;
  glfwSetup();

  std::cout << "1" << std::endl;
  GLFWwindow* win = glfwCreateWindow(800, 600, title, NULL, NULL);

  std::cout << "1" << std::endl;
  if (win == NULL) {
    std::cout << "Failed to create GLFW window." << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  std::cout << "1" << std::endl;
  glfwMakeContextCurrent(win);

  std::cout << "1" << std::endl;
  GLADSetup();

  std::cout << "1" << std::endl;
  glViewport(0, 0, width, height);

  std::cout << "1" << std::endl;
  glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
  glfwSetCursorPosCallback(win, mouse_callback);
  glfwSetScrollCallback(win, scroll_callback);

  std::cout << "1" << std::endl;
  glDisable(GL_DEPTH_TEST);

  std::cout << "1" << std::endl;
  screenHeight = height;
  screenWidth = width;

  std::cout << "1" << std::endl;
  screenTitle = (char*)malloc(strlen(title) + 1);
  if (screenTitle != NULL) {
    strcpy(screenTitle, title);
  }

  std::cout << "1" << std::endl;
  frame = win;

  myShader.MakeShader();

  std::cout << "1" << std::endl;
  initializeRectangleVAO();
  initializeCircleVAO();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {}

void initializeRectangleVAO() {
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, rectangleVertexCount * sizeof(float),
               rectangleVertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  rectangleVAO = VAO;
}

void initializeCircleVAO(int segments) {
  std::vector<float> vertices;

  // Center of the triangle fan
  vertices.push_back(0.0f);
  vertices.push_back(0.0f);

  for (int i = 0; i <= segments; ++i) {
    float angle = 2.0f * M_PI * i / segments;
    vertices.push_back(std::cos(angle));
    vertices.push_back(std::sin(angle));
  }

  unsigned int vao, vbo;

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
               vertices.data(), GL_STATIC_DRAW);

  // Assuming only position (x, y)
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  circleVAO = vao;
  circleSegments = segments;
}
