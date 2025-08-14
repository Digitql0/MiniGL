#ifndef WINDOW_HPP
#define WINDOW_HPP

//clang-format off
#include <glad/glad.h>
//clang-format on

#include <GLFW/glfw3.h>
#include <string.h>

#include "RenderGlobals.h"
#include "camera.h"
#include "shader.h"

void MGL_framebuffer_size_callback(GLFWwindow* window, int width, int height);
void MGL_mouse_callback(GLFWwindow* window, double xpos, double ypos);
void MGL_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void MGL_makeWindow(int width, int height, const char* title);
int MGL_windowShouldClose();
void MGL_closeWindow();

void MGL_glfwSetup();
void MGL_gladSetup();

void MGL_initializeRectangleVAO();
void MGL_initializeCircleVAO(int segments);
void MGL_initializeLineVAO();
void MGL_initializeDotVAO();

void MGL_initializeCubeVAO();
void MGL_initializeSphereVAO(int rings, int segments);
void MGL_initializeRayVAO();
void MGL_initializePointVAO();

#endif
