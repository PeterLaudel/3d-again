#ifndef __3DOBJECT__
#define __3DOBJECT__

#include <functional>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <optional>
#include <vector>

class C3DObject {
public:
  C3DObject() = default;
  ~C3DObject() = default;

  using C3DObjectDrawer = std::function<void(const C3DObject &)>;

  void setDrawer(C3DObjectDrawer drawer);
  void draw();

  void addVec(glm::vec3 vec);
  std::vector<glm::vec3> const &vecs() const;

  void addTriangle(glm::uvec3 triangle);
  std::vector<glm::uvec3> const &triangles() const;

  glm::mat4 const &matrix() const { return m_modelMatrix; }

private:
  std::vector<glm::vec3> m_vecs;
  std::vector<glm::uvec3> m_triangles;
  C3DObjectDrawer m_drawer;
  glm::mat4 m_modelMatrix{ glm::mat4(1.0)};
};

#endif /* __3DOBJECT__ */
