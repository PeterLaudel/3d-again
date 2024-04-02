#include <iostream>

// Include standard headers
#include <glad/glad.h>
// Include GLFW
#include <GLFW/glfw3.h>
#include <fstream>
#include <memory>
#include <streambuf>

#include <drawer/3DObjectDrawer.h>
#include <drawer/cameraDrawer.h>
#include <file_loader/stl.h>
#include <models/3DObject.h>
#include <models/camera.h>
#include <ui/inputDevice.h>
#include <shaders/shader.h>
#include <shaders/program.h>

struct destroyWindow
{
  void operator()(GLFWwindow *ptr) { glfwDestroyWindow(ptr); }
};

using unique_glfwwindow = std::unique_ptr<GLFWwindow, destroyWindow>;

unique_glfwwindow initWindow()
{
  if (!glfwInit())
  {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return unique_glfwwindow(nullptr);
  }

  glfwWindowHint(GLFW_SAMPLES, 4);               // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                 GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE,
                 GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

  // Open a window and create its OpenGL context
  unique_glfwwindow window(
      glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL));
  if (window == nullptr)
  {
    fprintf(stderr,
            "Failed to open GLFW window. If you have an Intel GPU, they are "
            "not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
    glfwTerminate();
    return {};
  }
  glfwMakeContextCurrent(window.get()); // Initialize GLEW

  gladLoadGL();

  glfwSetInputMode(window.get(), GLFW_STICKY_KEYS, GL_TRUE);
  return window;
};

int main()
{
  auto window = initWindow();
  if (!window)
    return 0;

  auto vertexShader = Shader::createVertexShader("./shaders/vertex.shader");
  auto fragmentShader =
      Shader::createFragmentShader("./shaders/fragment.shader");

  auto program = Program::create(vertexShader, fragmentShader);
  if (!program.verify())
  {
    return 0;
  }

  std::vector<C3DObject> vec;
  vec.push_back(*Stl::load("./files/cube_ascii.stl"));
  // vec.push_back(*Stl::load("./files/triangle.stl"));
  // vec.push_back(*Stl::load("./files/20mm_cube.stl"));

  Camera camera;
  camera.setDrawer(CameraDrawer(program));
  for (auto &v : vec)
  {
    v.setDrawer(C3DObjectDrawer(program));
  }

  InputDevice inputDevice(camera, *window.get());

  do
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program.id());

    camera.draw();
    for (auto &v : vec)
    {
      v.draw();
    }
    glfwSwapBuffers(window.get());
    glfwPollEvents();
    inputDevice.processInput();
  } // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window.get(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window.get()) == 0);
  return 0;
}
