#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up)
    : m_yaw(-90.0), m_pitch(0.0), m_pos(pos), m_front(front), m_up(up),
      m_left(glm::cross(m_front, m_up)),
      m_view(glm::lookAt(pos, pos + m_front, m_up)),
      m_projection(glm::ortho(-512.0f, 512.0f, -384.0f, 384.0f, 0.1f, 100.0f)) {
}

Camera::~Camera() {}

void Camera::moveLateral(float distance) { m_pos += m_front * distance; }

void Camera::moveVertical(float distance) { m_pos += m_up * distance; }

void Camera::moveHorizontal(float distance) { m_pos += m_left * distance; }

glm::mat4 const Camera::view() const {
  return glm::lookAt(m_pos, m_pos + m_front, m_up);
}

glm::mat4 const Camera::projection() const { return m_projection; }

void Camera::addPitch(float angle) {
  m_pitch += angle;
  updateCameraVecs();
}

void Camera::addYaw(float angle) {
  m_yaw += angle;
  updateCameraVecs();
}

void Camera::updateCameraVecs() {
  glm::vec3 direction(cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)),
                      sin(glm::radians(m_pitch)),
                      sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)));
  m_front = glm::normalize(direction);
  m_left = glm::normalize(glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f)));
  m_up = glm::normalize(glm::cross(m_front, m_left));
}