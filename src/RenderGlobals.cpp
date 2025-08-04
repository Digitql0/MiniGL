#include "RenderGlobals.hpp"

Perspectives mgl_perspective = Perspectives::Orthographic;
int mgl_mousex = 0;
int mgl_mousey = 0;
unsigned int mgl_rectangleVAO = 0;
unsigned int mgl_circleVAO = 0;
unsigned int mgl_circleSegments = 0;
unsigned int mgl_lineVAO = 0;
GLFWwindow* mgl_frame = nullptr;
int mgl_screenHeight = 800;
int mgl_screenWidth = 600;
char* mgl_screenTitle = (char*)"My Window";

float mgl_rectangleVertices[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                                 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};

float mgl_lineVertices[] = {0.0f, 0.0f, 1.0f, 0.0f};

const size_t mgl_rectangleVertexCount =
    sizeof(mgl_rectangleVertices) / sizeof(float);
const size_t mgl_lineVertexCount = sizeof(mgl_lineVertices) / sizeof(float);

Shader mgl_myShader;
