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
  
  int window_width;
  int window_height;

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
    window_width = width;
    window_height = height;

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
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    for (Layer* layer : layers) {
      layer->render();
    }

    /* Swap front and back buffers */
    glfwSwapBuffers(window);
  }

  static void resize_pick_buffer(int width, int height) {
    if (pick_frame_buffer == 0) return;

    GLint standard_frame_buffer;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &standard_frame_buffer);

    glBindFramebuffer(GL_FRAMEBUFFER, pick_frame_buffer);
    glDeleteRenderbuffers(1, &pick_render_buffer);

    glGenRenderbuffers(1, &pick_render_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, pick_render_buffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, pick_render_buffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);

    glBindFramebuffer(GL_FRAMEBUFFER, standard_frame_buffer);
  }
  
  void resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    setProjection(width, height);
    resize_pick_buffer(width, height);
    draw();
  }

  void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    EventData event_data;
    event_data.numbers["xpos"] = xpos;
    event_data.numbers["ypos"] = ypos;
    EventManager::triggerEvent("mouse_move", event_data);
  }

  int InitGLWindow() {
    /* Initialize the library */
    if (!glfwInit())
      return -1;

    /* Create a windowed mode window and its OpenGL context */
    window_width = 1200;
    window_height = 800;
    setProjection(window_width, window_height);
    window = glfwCreateWindow(window_width, window_height, windowTitle.c_str(), NULL, NULL);
    if (!window) {
      glfwTerminate();
      return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    if (glewInit() != GLEW_OK)
      std::cout << "ERROR!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    EventManager::registerEvent("mouse_move");
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