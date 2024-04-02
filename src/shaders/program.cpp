#include "program.h"
#include "shader.h"

#include <iostream>

#include <glad/glad.h>

Program::Program(uint32_t programId)
    : m_programId(programId)
{
}

Program::~Program()
{
    glDeleteProgram(m_programId);
}

bool Program::verify() const
{
    GLint isLinked = 0;
    glGetProgramiv(m_programId, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::string infoLog(maxLength, '\0');
        glGetProgramInfoLog(m_programId, maxLength, &maxLength, &infoLog[0]);

        std::cout << infoLog;
        return false;
    }
    return true;
}

Program Program::create(
    Shader const &vertexShader,
    Shader const &fragmentShader)
{

    auto programId = glCreateProgram();
    glAttachShader(programId, vertexShader.id());
    glAttachShader(programId, fragmentShader.id());

    glLinkProgram(programId);

    glDetachShader(programId, vertexShader.id());
    glDetachShader(programId, fragmentShader.id());

    return Program(programId);
}
