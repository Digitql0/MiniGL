#ifndef RENDERGLOBALS_HPP
#define RENDERGLOBALS_HPP

#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

typedef enum { Orthographic, Perspective } Perspectives;

typedef enum { Center, TopLeft } Anchor;

typedef struct {
  vec3 position;
  vec3 rotation;
  versor orientation;
  float fov;
  float zoom;
  float aspectRatio;
  float nearPlane;
  float farPlane;
  Perspectives perspective;
  float speed;
  float sensitivity;
  mat4 projection;
  mat4 view;
} Camera;

typedef struct {
  vec3 position;
  vec3 dimensions;
  vec3 lightColor;
} pointLight;

extern Camera camera;

// INPUT
extern int mgl_mousex;
extern int mgl_mousey;
extern int mgl_scrollx;
extern int mgl_scrolly;

// OPENGL DRAWING 2D
extern float mgl_rectangleVertices[];
extern float mgl_lineVertices[];
extern float mgl_dotVertices[];
extern unsigned int mgl_rectangleVAO;
extern const size_t mgl_rectangleVertexCount;
extern unsigned int mgl_circleVAO;
extern unsigned int mgl_circleSegments;
extern unsigned int mgl_lineVAO;
extern const size_t mgl_lineVertexCount;
extern unsigned int mgl_dotVAO;
extern const size_t mgl_dotVertexCount;

// OPENGL DRAWING 3D
extern float mgl_cubeVertices[];
extern unsigned int mgl_cubeIndices[];
extern float mgl_rayVertices[];
extern float mgl_pointVertices[];
extern unsigned int mgl_cubeVAO;
extern const size_t mgl_cubeVertexCount;
extern const size_t mgl_cubeIndexCount;
extern unsigned int mgl_sphereVAO;
extern unsigned int mgl_sphereSegments;
extern unsigned int mgl_sphereRings;
extern unsigned int mgl_rayVAO;
extern const size_t mgl_rayVertexCount;
extern unsigned int mgl_pointVAO;
extern const size_t mgl_pointVertexCount;

// OPENGL WINDOW
extern GLFWwindow* mgl_frame;
extern int mgl_screenHeight;
extern int mgl_screenWidth;
extern char* mgl_screenTitle;
extern void (*MGL_processInput)(void);

// IMMEDIATE-STYLE DRAWING
extern unsigned int mgl_myShader;
extern vec3* mgl_translationHistory;
extern size_t mgl_translationHistorySize;
extern vec3 mgl_currentTranslate;
extern vec4 mgl_strokeColor;
extern float mgl_strokeWidth;
extern vec4 mgl_fillColor;

// RENDER VARIABLES
extern unsigned int is2D;

// LIGHTING
extern unsigned int mgl_lightEnabled;
extern pointLight light;

// SHADERS
extern unsigned int mgl_objectShaderID;
extern unsigned int mgl_lightObjectShaderID;
extern const char* mgl_vertexShaderSource;
extern const char* mgl_fragmentShaderSource;
extern const char* mgl_lightObjectVertexShaderSource;
extern const char* mgl_lightObjectFragmentShaderSource;

#endif
