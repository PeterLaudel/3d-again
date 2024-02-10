#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up)
    : m_pos(pos), m_front(front), m_up(up), m_left(glm::cross(m_front, m_up)),
      m_view(glm::lookAt(m_pos, m_pos + m_front, m_up)),
      m_projection(glm::ortho(-512.0f, 512.0f, -384.0f, 384.0f, 0.1f, 100.0f)) {
}

Camera::~Camera() {}

void Camera::moveLateral(float distance) {
  m_view = glm::translate(m_view, m_front * distance);
}

void Camera::moveVertical(float distance) {
  m_view = glm::translate(m_view, m_up * distance);
}

void Camera::moveHorizontal(float distance) {
  m_view = glm::translate(m_view, m_left * distance);
}