#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>

namespace WashingBear {

  unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
      int length;
      glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
      char* message = new char[length];
      glGetShaderInfoLog(id, length, &length, message);

      std::string type_name;
      switch (type)
      {
      case GL_VERTEX_SHADER:
        type_name = "vertex";
        break;
      case GL_GEOMETRY_SHADER:
        type_name = "geometry";
        break;
      case GL_FRAGMENT_SHADER:
        type_name = "fragment";
        break;
      }

      std::cout << "Failed to compile " << type_name << "shader" << std::endl;
      std::cout << message << std::endl;

      glDeleteShader(id);
      return 0;
    }

    return id;
  }

  unsigned int CreateShader(
    const std::string& geometryShader,
    const std::string& vertexShader,
    const std::string& fragmentShader
  ) {
    unsigned int program = glCreateProgram();

    unsigned int geometry = 0;
    if (!geometryShader.empty()) {
      geometry = CompileShader(GL_GEOMETRY_SHADER, geometryShader);
      glAttachShader(program, geometry);
    }

    unsigned int vertex = CompileShader(GL_VERTEX_SHADER, vertexShader);
    glAttachShader(program, vertex); 
    
    unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, fragment);
    
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    if (geometry != 0) {
      glDeleteShader(geometry);
    }

    return program;
  }

  unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    return CreateShader("", vertexShader, fragmentShader);
  }

  std::string LoadShaderFile(const std::string& filepath) {
    std::cout << "Loading shader from file: " << filepath << std::endl;

    std::ifstream fileStream(filepath);
    if (!fileStream.is_open()) {
      std::cout << "Failed to open file" << std::endl;
      return "";
    }

    std::string line;
    std::stringstream stringStream;

    while (getline(fileStream, line)) {
      stringStream << line << '\n';
    }

    return stringStream.str();
  }

  unsigned int CreateShaderFromFiles(const std::string& geometryFile, const std::string& vertexFile, const std::string& fragmentFile) {
    std::string vertexShader    = LoadShaderFile(vertexFile);
    std::string fragmentShader  = LoadShaderFile(fragmentFile);

    if (geometryFile.empty()) {
      return CreateShader(vertexShader, fragmentShader);
    }
    else {
      std::string geometryShader = LoadShaderFile(geometryFile);
      return CreateShader(geometryShader, vertexShader, fragmentShader);
    }
  }

  unsigned int CreateShaderFromFiles(const std::string& vertexFile, const std::string& fragmentFile) {
    return CreateShaderFromFiles("", vertexFile, fragmentFile);
  }
}