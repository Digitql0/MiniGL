#include "window.h"

void MGL_framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void MGL_mouse_callback(GLFWwindow* window, double xpos, double ypos) {}

void MGL_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {}

void MGL_makeWindow(int width, int height, const char* title) {
  MGL_glfwSetup();

  GLFWwindow* win = glfwCreateWindow(800, 600, title, NULL, NULL);

  if (win == NULL) {
    printf("Failed to create GLFW window.");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(win);

  MGL_gladSetup();

  glViewport(0, 0, width, height);
  int fbWidth, fbHeight;
  glfwGetFramebufferSize(win, &fbWidth, &fbHeight);
  glViewport(0, 0, fbWidth, fbHeight);

  glfwSetFramebufferSizeCallback(win, MGL_framebuffer_size_callback);
  glfwSetCursorPosCallback(win, MGL_mouse_callback);
  glfwSetScrollCallback(win, MGL_scroll_callback);

  glDisable(GL_DEPTH_TEST);

  mgl_screenHeight = height;
  mgl_screenWidth = width;

  mgl_screenTitle = (char*)malloc(strlen(title) + 1);
  if (mgl_screenTitle != NULL) {
    strcpy(mgl_screenTitle, title);
  }

  mgl_frame = win;

  MGL_makeShader();

  MGL_initializeRectangleVAO();
  MGL_initializeCircleVAO(32);
  MGL_initializeLineVAO();
}

bool MGL_windowShouldClose() { return glfwWindowShouldClose(mgl_frame); }

void MGL_closeWindow() { glfwTerminate(); }

void MGL_glfwSetup() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void MGL_gladSetup() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD.");
    exit(EXIT_FAILURE);
  }
}

void MGL_initializeRectangleVAO() {
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, mgl_rectangleVertexCount * sizeof(float),
               mgl_rectangleVertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  mgl_rectangleVAO = VAO;
}

void MGL_initializeCircleVAO(int segments) {
  size_t verticeSize = sizeof(float) * (2 * (segments + 2));
  float* vertices = malloc(verticeSize);

  if (vertices == NULL) {
    printf("Circle Vao Problems");
    exit(EXIT_FAILURE);
  }

  size_t index = 0;

  // Center of the triangle fan
  vertices[index++] = 0.0f;
  vertices[index++] = 0.0f;

  for (int i = 0; i <= segments; ++i) {
    float angle = 2.0f * M_PI * i / segments;
    vertices[index++] = cosf(angle);
    vertices[index++] = sinf(angle);
  }

  unsigned int vao, vbo;

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, verticeSize, vertices, GL_STATIC_DRAW);

  // Assuming only position (x, y)
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  free(vertices);

  mgl_circleVAO = vao;
  mgl_circleSegments = segments;
}

void MGL_initializeLineVAO() {
  unsigned int vbo, vao;

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, mgl_lineVertexCount * sizeof(float),
               mgl_lineVertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  mgl_lineVAO = vao;
}
