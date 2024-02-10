#ifndef __INPUTDEVICE__
#define __INPUTDEVICE__

class Camera;
class GLFWwindow;

class InputDevice {
public:
  InputDevice(Camera &camera, GLFWwindow &window)
      : m_camera(camera), m_window(window){};
  ~InputDevice() = default;

  void processInput();

private:
  Camera &m_camera;
  GLFWwindow &m_window;
};

#endif /* __INPUTDEVICE__ */
