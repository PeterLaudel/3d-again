#ifndef __INPUTDEVICE__
#define __INPUTDEVICE__

class Camera;
class GLFWwindow;

class InputDevice {
public:
  InputDevice(Camera &camera, GLFWwindow &window);
  ~InputDevice() = default;

  void processInput();

private:
  Camera &m_camera;
  GLFWwindow &m_window;
  bool m_mousePressed;
  double m_mousePosX, m_mousePosY;
};

#endif /* __INPUTDEVICE__ */
