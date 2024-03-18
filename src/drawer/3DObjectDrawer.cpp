#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "3DObjectDrawer.h"

#include "../models/3DObject.h"

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
  glEnableVertexAttribArray(0);
  glDrawArrays(GL_TRIANGLES, 0, object.vecs().size());
  glDisableVertexAttribArray(0);
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
  glEnableVertexAttribArray(0);
  glBufferData(GL_ARRAY_BUFFER, points.size() * value_type_size, points.data(),
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  return VAO;
}