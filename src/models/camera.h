#ifndef __CAMERA__
#define __CAMERA__

#include <functional>
#include <glm/matrix.hpp>
#include <glm/vec3.hpp>

class Camera {
public:
  Camera(glm::vec3 pos = glm::vec3(0.0f, -1.0f, 0.0f),
         glm::vec3 front = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 0.0f, 0.0f));
  ~Camera();

  using CameraDrawer = std::function<void(Camera const &)>;

  glm::mat4 const &view() const { return m_view; };
  glm::mat4 const &projection() const { return m_projection; };

  void setDrawer(CameraDrawer cameraDrawer) { m_drawer = cameraDrawer; }
  void draw() const { m_drawer(*this); };

private:
  glm::vec3 m_pos;
  glm::vec3 m_front;
  glm::vec3 m_up;
  glm::mat4 m_view;
  glm::mat4 m_projection;
  CameraDrawer m_drawer;
};

#endif // __CAMERA__