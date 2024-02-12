#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

Camera::Camera()
    : m_yaw(-90.0), m_pitch(0.0), m_pos(glm::vec3(0.0, 0.0, 30.0)) {}

Camera::~Camera() {}

void Camera::moveLateral(float distance) {
  m_pos += glm::vec3(0.0f, 0.0f, -1.0f) * distance;
}

void Camera::moveVertical(float distance) {
  m_pos += glm::vec3(0.0, 1.0, 0.0) * distance;
}

void Camera::moveHorizontal(float distance) {
  m_pos += glm::vec3(1.0, 0.0, 0.0) * distance;
}

glm::mat4 const Camera::view() const {
  return glm::lookAt(m_pos, m_pos + glm::vec3(0.0f, 0.0f, -1.0f),
                     glm::vec3(0.0, 1.0, 0.0)) *
         glm::yawPitchRoll(m_yaw, m_pitch, 0.0f);
}

glm::mat4 const Camera::projection() const {
  return glm::ortho(-512.0f, 512.0f, -384.0f, 384.0f, -100.0f, 100.0f);
}

void Camera::addPitch(float angle) { m_pitch += angle; }

void Camera::addYaw(float angle) { m_yaw += angle; }
