#ifndef __3DOBJECT__
#define __3DOBJECT__

#include <vector>
#include <optional>
#include <functional>
#include <glm/vec3.hpp>

class C3DObject
{
public:
    C3DObject() = default;
    ~C3DObject() = default;

    using C3DObjectDrawer = std::function<void(const C3DObject &)>;

    void setDrawer(C3DObjectDrawer drawer);
    void draw();

    void addVec(glm::vec3 vec);
    const std::vector<glm::vec3> &vecs() const;

private:
    std::vector<glm::vec3> m_vecs;
    C3DObjectDrawer m_drawer;
};

#endif /* __3DOBJECT__ */
