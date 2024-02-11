#ifndef __CAMERA__
#define __CAMERA__

#include <functional>
#include <glm/matrix.hpp>
#include <glm/vec3.hpp>

class Camera {
public:
  Camera();
  ~Camera();

  using CameraDrawer = std::function<void(Camera const &)>;

  glm::mat4 const view() const;
  glm::mat4 const projection() const;

  void moveLateral(float distance);
  void moveHorizontal(float distance);
  void moveVertical(float distance);

  void addPitch(float angle);
  void addYaw(float angle);

  void setDrawer(CameraDrawer cameraDrawer) { m_drawer = cameraDrawer; }
  void draw() const { m_drawer(*this); };

private:
  void updateCameraVecs();

  float m_yaw;
  float m_pitch;
  glm::vec3 m_pos;
  CameraDrawer m_drawer;
};

#endif // __CAMERA__