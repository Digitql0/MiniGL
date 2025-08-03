#ifndef RENDERGLOBALS_HPP
#define RENDERGLOBALS_HPP

#include "shader.hpp"
#include <GLFW/glfw3.h>

enum class Perspectives {
    Orthographic,
    Perspective
};

enum class Anchor {
    Center,
    TopLeft
};

// Declare globals using `extern`
extern Perspectives p;
extern int mousex;
extern int mousey;
extern unsigned int rectangleVAO;
extern const size_t rectangleVertexCount;
extern unsigned int circleVAO;
extern unsigned int circleSegments;
extern unsigned int lineVAO;
extern const size_t lineVertexCount;
extern GLFWwindow* frame;
extern int screenHeight;
extern int screenWidth;
extern char* screenTitle;
extern float rectangleVertices[];
extern float lineVertices[];
extern Shader myShader;

#endif
