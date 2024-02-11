#include <functional>
#include <iostream>

#include <GLFW/glfw3.h>

#include "inputDevice.h"
#include "models/camera.h"

InputDevice::InputDevice(Camera &camera, GLFWwindow &window)
    : m_camera(camera), m_window(window), m_mousePressed(false){};

void InputDevice::processInput() {
  if (glfwGetKey(&m_window, GLFW_KEY_W) == GLFW_PRESS)
    m_camera.moveLateral(1.0);
  if (glfwGetKey(&m_window, GLFW_KEY_S) == GLFW_PRESS)
    m_camera.moveLateral(-1.0);
  if (glfwGetKey(&m_window, GLFW_KEY_A) == GLFW_PRESS)
    m_camera.moveHorizontal(1.0);
  if (glfwGetKey(&m_window, GLFW_KEY_D) == GLFW_PRESS)
    m_camera.moveHorizontal(-1.0);
  auto mouseButton = glfwGetMouseButton(&m_window, GLFW_MOUSE_BUTTON_LEFT);
  if (mouseButton == GLFW_PRESS) {
    if (m_mousePressed) {
      double mousePosX, mousePosY;
      glfwGetCursorPos(&m_window, &mousePosX, &mousePosY);
      m_camera.addYaw(mousePosX - m_mousePosX);
      m_camera.addPitch(mousePosY - m_mousePosY);
      m_mousePosX = mousePosX;
      m_mousePosY = mousePosY;
    } else {
      m_mousePressed = true;
      glfwGetCursorPos(&m_window, &m_mousePosX, &m_mousePosY);
    }
  }
  if (mouseButton == GLFW_RELEASE) {
    m_mousePressed = false;
  }
}
