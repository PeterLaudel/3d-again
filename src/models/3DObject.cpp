#include "3DObject.h"

#include <iostream>

void C3DObject::setDrawer(C3DObjectDrawer drawer) { m_drawer = drawer; }

void C3DObject::draw() { m_drawer(*this); }

void C3DObject::addVec(glm::vec3 vec) { m_vecs.emplace_back(vec); }

std::vector<glm::vec3> const &C3DObject::vecs() const { return m_vecs; }

void C3DObject::addTriangle(glm::uvec3 triangle)
{
    m_triangles.emplace_back(triangle);
}

std::vector<glm::uvec3> const &C3DObject::triangles() const
{
    return m_triangles;
}
