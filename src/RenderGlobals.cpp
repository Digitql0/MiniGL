#include "RenderGlobals.hpp"

Perspectives p = Perspectives::Orthographic;
int mousex = 0;
int mousey = 0;
unsigned int rectangleVAO = 0;
unsigned int circleVAO = 0;
unsigned int circleSegments = 0;
GLFWwindow* frame = nullptr;
int screenHeight = 800;
int screenWidth = 600;
char* screenTitle = (char*)"My Window";

float rectangleVertices[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                             0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};

const size_t rectangleVertexCount = sizeof(rectangleVertices) / sizeof(float);

Shader myShader;
