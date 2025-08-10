#include <WashingBear.h>
#include "global.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shaders.h"
#include "layer/Layer.h"

namespace WashingBear {

  std::string windowTitle = "WashingBear Engine";
  std::string resourcePath = "resources";
  
  float projection_x;
  float projection_y;

  GLFWwindow* window;

  void SetTitle(std::string title) {
    windowTitle = title;
  }

  void SetResourcePath(std::string path) {
    resourcePath = path;
  }

  void setProjection(int width, int height) {
    float x = 1.0;
    float y = 1.0;
    if (width > height) {
      x = (float)height / width;
    }
    else {
      y = (float)width / height;
    }
    projection_x = x;
    projection_y = y;

    for (Layer* layer : layers) {
      layer->setProjection(projection_x, projection_y);
    }
  }

  void draw() {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    for (Layer* layer : layers) {
      layer->render();
    }

    /* Swap front and back buffers */
    glfwSwapBuffers(window);
  }
  
  void resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    setProjection(width, height);
    draw();
  }

  int InitGLWindow() {
    /* Initialize the library */
    if (!glfwInit())
      return -1;

    /* Create a windowed mode window and its OpenGL context */
    int width = 1200;
    int height = 800;
    setProjection(width, height);
    window = glfwCreateWindow(width, height, windowTitle.c_str(), NULL, NULL);
    if (!window) {
      glfwTerminate();
      return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize_callback);

    if (glewInit() != GLEW_OK)
      std::cout << "ERROR!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
  }

  int Run() {

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
      draw();

      /* Poll for and process events */
      glfwPollEvents();
    }

    glfwTerminate();
    return 0;
  }

}