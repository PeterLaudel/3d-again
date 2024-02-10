#include <iostream>

#include <GLFW/glfw3.h>

#include "inputDevice.h"
#include "models/camera.h"

void InputDevice::processInput() {
  if (glfwGetKey(&m_window, GLFW_KEY_W) == GLFW_PRESS)
    m_camera.moveLateral(1.0);
  if (glfwGetKey(&m_window, GLFW_KEY_S) == GLFW_PRESS)
    m_camera.moveLateral(-0.1);
  if (glfwGetKey(&m_window, GLFW_KEY_A) == GLFW_PRESS)
    m_camera.moveHorizontal(0.1);
  if (glfwGetKey(&m_window, GLFW_KEY_D) == GLFW_PRESS)
    m_camera.moveHorizontal(-0.1);
}