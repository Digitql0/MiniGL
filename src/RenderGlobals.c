#include "RenderGlobals.h"

Perspectives mgl_perspective = Orthographic;
int mgl_mousex = 0;
int mgl_mousey = 0;
unsigned int mgl_rectangleVAO = 0;
unsigned int mgl_circleVAO = 0;
unsigned int mgl_circleSegments = 0;
unsigned int mgl_lineVAO = 0;
GLFWwindow* mgl_frame = NULL;
int mgl_screenHeight = 800;
int mgl_screenWidth = 600;
char* mgl_screenTitle = (char*)"My Window";
vec2* mgl_translationHistory = NULL;
size_t mgl_translationHistorySize = 0;
vec2 mgl_currentTranslate = {0, 0};
vec4 mgl_strokeColor = {255, 255, 255, 255};
unsigned int mgl_strokeWidth = 1;
vec4 mgl_fillColor = {0, 0, 0, 255};

float mgl_rectangleVertices[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                                 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};

float mgl_lineVertices[] = {0.0f, 0.0f, 1.0f, 0.0f};

const size_t mgl_rectangleVertexCount =
    sizeof(mgl_rectangleVertices) / sizeof(float);
const size_t mgl_lineVertexCount = sizeof(mgl_lineVertices) / sizeof(float);

unsigned int mgl_myShader;
