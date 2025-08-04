#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include "glm/glm.hpp"
#include <string>

class Shader {
 public:
  unsigned int mgl_ID;
  Shader();
  void MGL_makeShader();
  void MGL_use();
  void MGL_setBool(const std::string &name, bool value) const;
  void MGL_setInt(const std::string &name, int value) const;
  void MGL_setFloat(const std::string &name, float value) const;
  void MGL_setVec2(const std::string &name, const glm::vec2 &value) const;
  void MGL_setVec2(const std::string &name, float x, float y) const;
  void MGL_setVec3(const std::string &name, const glm::vec3 &value) const;
  void MGL_setVec3(const std::string &name, float x, float y, float z) const;
  void MGL_setVec4(const std::string &name, const glm::vec4 &value) const;
  void MGL_setVec4(const std::string &name, float x, float y, float z,
               float w) const;
  void MGL_setMat2(const std::string &name, const glm::mat2 &mat) const;
  void MGL_setMat3(const std::string &name, const glm::mat3 &mat) const;
  void MGL_setMat4(const std::string &name, const glm::mat4 &mat) const;

 private:
  void MGL_checkCompileErrors(GLuint shader, std::string type);
};

#endif
