#pragma once
#include <string>

namespace WashingBear {
  std::string LoadShaderFile(const std::string& filepath);

  unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
  unsigned int CreateShader(const std::string& geometryShader,const std::string& vertexShader,const std::string& fragmentShader);

  unsigned int CreateShaderFromFiles(const std::string& vertexFile, const std::string& fragmentFile);
  unsigned int CreateShaderFromFiles(const std::string& geometryFile, const std::string& vertexFile, const std::string& fragmentFile);
}