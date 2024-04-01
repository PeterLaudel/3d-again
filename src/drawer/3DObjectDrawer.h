#ifndef __3DOBJECTDRAWER__
#define __3DOBJECTDRAWER__

#include <optional>

class C3DObject;

#include "../shaders/program.h"

class C3DObjectDrawer
{
public:
  C3DObjectDrawer(Program &program) : m_program(program){};
  ~C3DObjectDrawer();

  void operator()(C3DObject const &object);

private:
  uint32_t load(C3DObject const &object);

  std::optional<uint32_t> m_vao;
  Program m_program;
};

#endif // __3DOBJECTDRAWER__