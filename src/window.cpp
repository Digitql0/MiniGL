#include "window.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {}

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
  initializeLineVAO();
}

bool WindowShouldClose() { return glfwWindowShouldClose(frame); }

void CloseWindow() { glfwTerminate(); }

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

void initializeLineVAO() {
  unsigned int vbo, vao;

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, lineVertexCount * sizeof(float), lineVertices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  lineVAO = vao;
}
