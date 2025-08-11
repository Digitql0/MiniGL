#ifndef RENDERGLOBALS_HPP
#define RENDERGLOBALS_HPP

#include "shader.h"

typedef enum { Orthographic, Perspective } Perspectives;

typedef enum { Center, TopLeft } Anchor;

// Declare globals using `extern`
extern Perspectives mgl_perspective;
extern int mgl_mousex;
extern int mgl_mousey;
extern unsigned int mgl_rectangleVAO;
extern const size_t mgl_rectangleVertexCount;
extern unsigned int mgl_circleVAO;
extern unsigned int mgl_circleSegments;
extern unsigned int mgl_lineVAO;
extern const size_t mgl_lineVertexCount;
extern GLFWwindow* mgl_frame;
extern int mgl_screenHeight;
extern int mgl_screenWidth;
extern char* mgl_screenTitle;
extern float mgl_rectangleVertices[];
extern float mgl_lineVertices[];
extern unsigned int mgl_myShader;

#endif
