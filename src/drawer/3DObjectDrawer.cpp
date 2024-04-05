#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "3DObjectDrawer.h"

#include "../models/3DObject.h"

C3DObjectDrawer::~C3DObjectDrawer()
{
  if (m_vao)
  {
    glDeleteBuffers(1, &m_vao.value());
    m_vao.reset();
  }
}

void C3DObjectDrawer::operator()(const C3DObject &object)
{
  if (!m_vao)
    m_vao.emplace(load(object));

  int projectionLoc = glGetUniformLocation(m_program.id(), "model");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
                     glm::value_ptr(object.matrix()));

  glBindVertexArray(*m_vao);
  glDrawElements(GL_TRIANGLES, object.triangles().size() * 3, GL_UNSIGNED_INT,
                 0);
  glBindVertexArray(0);
}

GLuint C3DObjectDrawer::load(const C3DObject &object)
{
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  auto const &points = object.vecs();
  auto pointsSize = points.size() * sizeof(points[0]);
  glBufferData(GL_ARRAY_BUFFER, pointsSize, &points[0],
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  auto const &triangles = object.triangles();
  auto triangleSize = triangles.size() * sizeof(triangles[0]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleSize, &triangles[0],
               GL_STATIC_DRAW);

  glBindVertexArray(0);

  return VAO;
}