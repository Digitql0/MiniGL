#ifndef MINIGL_H
#define MINIGL_H

// OpenGL
#include "glad/glad.h"
#include "GLFW/glfw3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void MakeWindow(int width, int height, const char *title);
void drawRectangle(float posx, float posy, float width, float height, int r, int g, int b);
bool WindowShouldClose();
void BeginDrawing();
void ClearBackground(int r, int g, int b);
void EndDrawing();
void CloseWindow();
void glfwSetup();
void GLADSetup();
void processInput(GLFWwindow* window);
void initializeRectangleVAO();

#endif //MINIGL_H 