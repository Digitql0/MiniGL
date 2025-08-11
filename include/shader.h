#ifndef SHADER_H
#define SHADER_H

// clang-format off
#include <glad/glad.h>
// clang-format on
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

extern unsigned int mgl_ID;

void MGL_makeShader(void);
void MGL_use(void);
void MGL_setBool(const char* name, int value);
void MGL_setInt(const char* name, int value);
void MGL_setFloat(const char* name, float value);
void MGL_setVec2(const char* name, const vec2* value);
void MGL_setVec2_xy(const char* name, float x, float y);
void MGL_setVec3(const char* name, const vec3* value);
void MGL_setVec3_xyz(const char* name, float x, float y, float z);
void MGL_setVec4(const char* name, const vec4* value);
void MGL_setVec4_xyzw(const char* name, float x, float y, float z, float w);
void MGL_setMat2(const char* name, const mat2* mat);
void MGL_setMat3(const char* name, const mat3* mat);
void MGL_setMat4(const char* name, const mat4* mat);

void MGL_checkCompileErrors(GLuint shader, const char* type);

#endif
