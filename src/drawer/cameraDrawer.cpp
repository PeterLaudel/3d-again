#include "models/camera.h"

#include "cameraDrawer.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

void CameraDrawer::operator()(Camera const &camera) {
  int projectionLoc = glGetUniformLocation(m_programId, "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
                     glm::value_ptr(camera.projection()));

  int viewLoc = glGetUniformLocation(m_programId, "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.view()));
}