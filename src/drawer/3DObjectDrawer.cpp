#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "3DObjectDrawer.h"

C3DObjectDrawer::~C3DObjectDrawer() {
  if (m_vao) {

    glDeleteBuffers(1, &m_vao.value());
    m_vao.reset();
  }
}

void C3DObjectDrawer::operator()(const C3DObject &object) {
  if (!m_vao) {
    m_vao.emplace(load(object));
  }
  int projectionLoc = glGetUniformLocation(m_programId, "model");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
                     glm::value_ptr(object.matrix()));

  glBindVertexArray(*m_vao);
  glDrawArrays(GL_TRIANGLES, 0, object.vecs().size());
  glBindVertexArray(0);
}

GLuint C3DObjectDrawer::load(const C3DObject &object) {
  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  auto const &points = object.vecs();
  auto value_type_size = sizeof(decltype(points.back()));
  glBufferData(GL_ARRAY_BUFFER, sizeof(points.size()) * sizeof(float),
               &points[0], GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  return VAO;
}