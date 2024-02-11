#ifndef __3DOBJECTDRAWER__
#define __3DOBJECTDRAWER__

#include <optional>

#include "models/3DObject.h"

class C3DObjectDrawer {
public:
  C3DObjectDrawer(uint32_t programId) : m_programId(programId){};
  ~C3DObjectDrawer();

  void operator()(C3DObject const &object);

private:
  GLuint load(C3DObject const &object);

  std::optional<GLuint> m_vao;
  uint32_t m_programId;
};

#endif // __3DOBJECTDRAWER__