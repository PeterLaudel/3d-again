#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up)
    : m_pos(pos), m_front(front), m_up(up), m_view(glm::mat4(1.0f)),
      m_projection(glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f)) {}

Camera::~Camera() {}