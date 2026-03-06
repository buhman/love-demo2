#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#include "glad/gl.h"
#include <GLFW/glfw3.h>

extern void load();
extern void draw();

int main()
{
  glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

  GLFWwindow* window = glfwCreateWindow(1024, 1024, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    const char* description;
    glfwGetError(&description);
    printf("Failed to create GLFW window: %s\n", description);
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  gladLoadGL(glfwGetProcAddress);

  glViewport(0, 0, 1024, 1024);

  load();

  while(!glfwWindowShouldClose(window)) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);

    draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
