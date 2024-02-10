#ifndef __CAMERA_DRAWER__
#define __CAMERA_DRAWER__

class Camera;

class CameraDrawer {
public:
  CameraDrawer(u_int32_t programId) : m_programId(programId){};
  ~CameraDrawer() = default;

  void operator()(Camera const &camera);

private:
  uint32_t m_programId;
};

#endif /* __CAMERA_DRAWER__ */
