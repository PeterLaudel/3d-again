#ifndef __CAMERA_DRAWER__
#define __CAMERA_DRAWER__

class Camera;

#include "../shaders/program.h"

class CameraDrawer
{
public:
  CameraDrawer(Program &program) : m_program(program){};
  ~CameraDrawer() = default;

  void operator()(Camera const &camera);

private:
  Program &m_program;
};

#endif /* __CAMERA_DRAWER__ */
