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
extern GLFWwindow* frame;
extern int screenHeight;
extern int screenWidth;
extern char* screenTitle;
extern float rectangleVertices[];
extern Shader myShader;

#endif
