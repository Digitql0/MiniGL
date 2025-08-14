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
    // positions        // normals
    // Back face (Z = -0.5) - CCW winding
    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,
    0.5f,  -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,
    0.5f,  0.5f,  -0.5f, 0.0f,  0.0f, -1.0f,
    -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f, -1.0f,
    
    // Front face (Z = 0.5) - CCW winding
    -0.5f, -0.5f, 0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, 0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    0.5f,  -0.5f, 0.5f,  0.0f,  0.0f, 1.0f,
    
    // Left face (X = -0.5) - CCW winding
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f,  -0.5f, -1.0f, 0.0f, 0.0f,
    
    // Right face (X = 0.5) - CCW winding
    0.5f,  -0.5f, -0.5f, 1.0f,  0.0f, 0.0f,
    0.5f,  0.5f,  -0.5f, 1.0f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f, 0.0f,
    0.5f,  -0.5f, 0.5f,  1.0f,  0.0f, 0.0f,
    
    // Bottom face (Y = -0.5) - CCW winding
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    0.5f,  -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    0.5f,  -0.5f, 0.5f,  0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, -1.0f, 0.0f,
    
    // Top face (Y = 0.5) - CCW winding
    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f,  0.0f,
    -0.5f, 0.5f,  0.5f,  0.0f, 1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f,
    0.5f,  0.5f,  -0.5f, 0.0f, 1.0f,  0.0f,
};
unsigned int mgl_cubeIndices[] = {
    0,  1,  2,  0,  2,  3,   // back
    4,  5,  6,  4,  6,  7,   // front
    8,  9,  10, 8,  10, 11,  // left
    12, 13, 14, 12, 14, 15,  // right
    16, 17, 18, 16, 18, 19,  // bottom
    20, 21, 22, 20, 22, 23   // top
};
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
GLFWwindow *mgl_frame = NULL;
int mgl_screenHeight = 0;
int mgl_screenWidth = 0;
char *mgl_screenTitle = (char *)"My Window";
void (*MGL_processInput)(void) = NULL;

// IMMEDIATE-STYLE DRAWING
vec3 *mgl_translationHistory = NULL;
size_t mgl_translationHistorySize = 0;
vec3 mgl_currentTranslate = {0, 0, 0};
vec4 mgl_strokeColor = {255, 255, 255, 255};
float mgl_strokeWidth = 1;
vec4 mgl_fillColor = {0, 0, 0, 255};

// RENDER VARIABLES
unsigned int is2D = 0;

// LIGHTING
unsigned int mgl_lightEnabled = 0;
pointLight light = {{100, 100, 100}, {5, 5, 5}, {1.0f, 1.0f, 1.0f}};

// SHADERS
unsigned int mgl_objectShaderID;
unsigned int mgl_lightObjectShaderID = 0;
const char *mgl_vertexShaderSource = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    // Normal = mat3(transpose(inverse(model))) * aNormal;
    Normal = aNormal; // ignore model transform


    gl_Position = projection * view * vec4(FragPos, 1.0);
}
)glsl";
const char *mgl_fragmentShaderSource = R"glsl(
#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{    
    // Original lighting code (commented out for debugging)
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}
)glsl";
const char *mgl_lightObjectVertexShaderSource = R"glsl(
#version 330 core
layout(location = 0) in vec3 aPos;

uniform float pointSize;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    gl_PointSize = pointSize;
}
)glsl";
const char *mgl_lightObjectFragmentShaderSource = R"glsl(
#version 330 core
out vec4 FragColor;

uniform vec3 color;

void main() {
    FragColor = vec4(color, 1.0);
}
)glsl";
