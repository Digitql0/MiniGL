#ifndef SHADER_H
#define SHADER_H

// clang-format off
#include <glad/glad.h>
// clang-format on
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

unsigned int MGL_makeShader(const char* vertexShaderSource,
                            const char* fragmentShaderSource);
void MGL_use(unsigned int id);
void MGL_setBool(unsigned int id, const char* name, int value);
void MGL_setInt(unsigned int id, const char* name, int value);
void MGL_setFloat(unsigned int id, const char* name, float value);
void MGL_setVec2(unsigned int id, const char* name, const vec2* value);
void MGL_setVec2_xy(unsigned int id, const char* name, float x, float y);
void MGL_setVec3(unsigned int id, const char* name, const vec3* value);
void MGL_setVec3_xyz(unsigned int id, const char* name, float x, float y,
                     float z);
void MGL_setVec4(unsigned int id, const char* name, const vec4* value);
void MGL_setVec4_xyzw(unsigned int id, const char* name, float x, float y,
                      float z, float w);
void MGL_setMat2(unsigned int id, const char* name, const mat2* mat);
void MGL_setMat3(unsigned int id, const char* name, const mat3* mat);
void MGL_setMat4(unsigned int id, const char* name, const mat4* mat);
void MGL_checkCompileErrors(GLuint shader, const char* type);

#endif
