#include "window.h"

void MGL_framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void MGL_mouse_callback(GLFWwindow* window, double xpos, double ypos) {
  mgl_mousex = xpos;
  mgl_mousey = ypos;
}

void MGL_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {}

void MGL_makeWindow(int width, int height, const char* title) {
  MGL_glfwSetup();

  GLFWwindow* win = glfwCreateWindow(width, height, title, NULL, NULL);

  if (win == NULL) {
    printf("Failed to create GLFW window.");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(win);

  MGL_gladSetup();

  glViewport(0, 0, width, height);

  glfwSetFramebufferSizeCallback(win, MGL_framebuffer_size_callback);
  glfwSetCursorPosCallback(win, MGL_mouse_callback);
  glfwSetScrollCallback(win, MGL_scroll_callback);

  mgl_screenHeight = height;
  mgl_screenWidth = width;

  mgl_screenTitle = (char*)malloc(strlen(title) + 1);
  if (mgl_screenTitle != NULL) {
    strcpy(mgl_screenTitle, title);
  }

  glEnable(GL_PROGRAM_POINT_SIZE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
  // glDisable(GL_BLEND);
  // glDepthMask(GL_TRUE);
  // glfwWindowHint(GLFW_DEPTH_BITS, 24);  // request a 24-bit depth buffer

  // Initialize basic default Camera
  mgl_frame = win;
  Camera* cam = MGLC_getCamera();
  float pos[] = {mgl_screenWidth / 2, mgl_screenHeight / 2, 0.0f};
  MGLC_setPosition(pos, cam);
  float rot[] = {0, 0, 0};
  MGLC_setRotation(rot, cam);
  MGLC_setFOV(45, cam);
  MGLC_setZoom(mgl_screenHeight / 2, cam);
  MGLC_setAspectRatio(mgl_screenWidth / mgl_screenHeight, cam);
  MGLC_setNearPlane(0.1f, cam);
  MGLC_setFarPlane(1000.0f, cam);
  MGLC_setPerspective(Perspective, cam);
  MGLC_setSpeed(20.0f, cam);
  MGLC_setSensitivity(0.002f, cam);

  // Make all Shaders
  mgl_objectShaderID =
      MGL_makeShader(mgl_vertexShaderSource, mgl_fragmentShaderSource);
  mgl_lightObjectShaderID = MGL_makeShader(mgl_lightObjectVertexShaderSource,
                                           mgl_lightObjectFragmentShaderSource);

  // Initialize VAOs of all objects
  MGL_initializeRectangleVAO();
  MGL_initializeCircleVAO(32);
  MGL_initializeLineVAO();
  MGL_initializeDotVAO();
  MGL_initializeCubeVAO();
  MGL_initializeSphereVAO(16, 32);
  MGL_initializeRayVAO();
  MGL_initializePointVAO();
}

int MGL_windowShouldClose() { return glfwWindowShouldClose(mgl_frame); }

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

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  mgl_rectangleVAO = VAO;
}

void MGL_initializeCircleVAO(int segments) {
  size_t verticeSize = sizeof(float) * (3 * (segments + 2));
  float* vertices = malloc(verticeSize);

  if (vertices == NULL) {
    printf("Circle Vao Problems");
    exit(EXIT_FAILURE);
  }

  size_t index = 0;

  // Center of the triangle fan
  vertices[index++] = 0.0f;
  vertices[index++] = 0.0f;
  vertices[index++] = 0.0f;

  for (int i = 0; i <= segments; ++i) {
    float angle = 2.0f * M_PI * i / segments;
    vertices[index++] = cosf(angle);
    vertices[index++] = sinf(angle);
    vertices[index++] = 0.0f;
  }

  unsigned int vao, vbo;

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, verticeSize, vertices, GL_STATIC_DRAW);

  // Assuming only position (x, y)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
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

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  mgl_lineVAO = vao;
}

void MGL_initializeDotVAO() {
  unsigned int vbo, vao;

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, mgl_dotVertexCount * sizeof(float),
               mgl_dotVertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  mgl_dotVAO = vao;
}

void MGL_initializeCubeVAO() {
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, mgl_cubeVertexCount * sizeof(float),
               mgl_cubeVertices, GL_STATIC_DRAW);
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // normal attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  unsigned int EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               mgl_cubeIndexCount * sizeof(unsigned int), mgl_cubeIndices,
               GL_STATIC_DRAW);

  glBindVertexArray(0);

  mgl_cubeVAO = VAO;
}

void MGL_initializeSphereVAO(int rings, int segments) {
  size_t vertCount = (rings + 1) * (segments + 1);
  size_t vertSize = vertCount * 3 * sizeof(float);
  float* vertices = malloc(vertSize);
  if (!vertices) {
    printf("Failed to allocate vertices\n");
    exit(EXIT_FAILURE);
  }

  size_t idx = 0;
  for (int i = 0; i <= rings; i++) {
    float theta = (float)i * M_PI / (float)rings;  // latitude angle
    float sinTheta = sinf(theta);
    float cosTheta = cosf(theta);

    for (int j = 0; j <= segments; j++) {
      float phi = (float)j * 2.0f * M_PI / (float)segments;  // longitude angle
      float sinPhi = sinf(phi);
      float cosPhi = cosf(phi);

      float x = cosPhi * sinTheta;
      float y = cosTheta;
      float z = sinPhi * sinTheta;

      vertices[idx++] = x;
      vertices[idx++] = y;
      vertices[idx++] = z;
    }
  }

  size_t indexCount = rings * (segments + 1) * 2;
  unsigned int* indices = malloc(indexCount * sizeof(unsigned int));
  if (!indices) {
    printf("Failed to allocate indices\n");
    free(vertices);
    exit(EXIT_FAILURE);
  }

  size_t idxIdx = 0;
  for (int i = 0; i < rings; i++) {
    for (int j = 0; j <= segments; j++) {
      indices[idxIdx++] = i * (segments + 1) + j;  // vertex on current ring
      indices[idxIdx++] = (i + 1) * (segments + 1) + j;  // vertex on next ring
    }
  }

  unsigned int vao, vbo, ebo;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertSize, vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int),
               indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  free(vertices);
  free(indices);

  mgl_sphereVAO = vao;
  mgl_sphereRings = rings;
  mgl_sphereSegments = segments;
}

void MGL_initializeRayVAO() {
  unsigned int vbo, vao;

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, mgl_rayVertexCount * sizeof(float),
               mgl_rayVertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  mgl_rayVAO = vao;
}

void MGL_initializePointVAO() {
  unsigned int vbo, vao;

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, mgl_pointVertexCount * sizeof(float),
               mgl_pointVertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  mgl_pointVAO = vao;
}
