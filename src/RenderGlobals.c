#include "RenderGlobals.h"

Camera camera;

// INPUT
int mgl_mousex = 0;
int mgl_mousey = 0;
int mgl_scrollx = 0;
int mgl_scrolly = 0;

// OPENGL DRAWING 2D
float mgl_rectangleVertices[] = {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                                 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f};
float mgl_lineVertices[] = {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
float mgl_dotVertices[] = {0.0f, 0.0f, 0.0f};
unsigned int mgl_rectangleVAO = 0;
const size_t mgl_rectangleVertexCount =
    sizeof(mgl_rectangleVertices) / sizeof(float);
unsigned int mgl_circleVAO = 0;
unsigned int mgl_circleSegments = 0;
unsigned int mgl_lineVAO = 0;
const size_t mgl_lineVertexCount = sizeof(mgl_lineVertices) / sizeof(float);
unsigned int mgl_dotVAO = 0;
const size_t mgl_dotVertexCount = sizeof(mgl_dotVertices) / sizeof(float);

// OPENGL DRAWING 3D
float mgl_cubeVertices[] = {
    -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,
    0.5f,  -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, -0.5f,
    0.5f,  -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,
    -0.5f, 0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
    0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,
    0.5f,  -0.5f, -0.5f, -0.5f, -0.5f, -0.5f};
unsigned int mgl_cubeIndices[] = {
    0,  1,  2,  2,  3,  0,  4,  5,  6,  6,  7,  4,  8,  9,  10, 10, 11, 8,
    12, 13, 14, 14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20};
float mgl_rayVertices[] = {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
float mgl_pointVertices[] = {0.0f, 0.0f, 0.0f};
unsigned int mgl_cubeVAO = 0;
const size_t mgl_cubeVertexCount = sizeof(mgl_cubeVertices) / sizeof(float);
const size_t mgl_cubeIndexCount =
    sizeof(mgl_cubeIndices) / sizeof(unsigned int);
unsigned int mgl_sphereVAO = 0;
unsigned int mgl_sphereSegments = 0;
unsigned int mgl_sphereRings = 0;
unsigned int mgl_rayVAO = 0;
const size_t mgl_rayVertexCount = sizeof(mgl_rayVertices) / sizeof(float);
unsigned int mgl_pointVAO = 0;
const size_t mgl_pointVertexCount = sizeof(mgl_pointVertices) / sizeof(float);

// OPENGL WINDOW
GLFWwindow* mgl_frame = NULL;
int mgl_screenHeight = 0;
int mgl_screenWidth = 0;
char* mgl_screenTitle = (char*)"My Window";
void (*MGL_processInput)(void) = NULL;

// IMMEDIATE-STYLE DRAWING
vec3* mgl_translationHistory = NULL;
size_t mgl_translationHistorySize = 0;
vec3 mgl_currentTranslate = {0, 0, 0};
vec4 mgl_strokeColor = {255, 255, 255, 255};
float mgl_strokeWidth = 1;
vec4 mgl_fillColor = {0, 0, 0, 255};
