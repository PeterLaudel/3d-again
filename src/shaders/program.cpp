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
}

Program Program::create(
    std::string const &vertexShaderSource,
    std::string const &fragmentShaderSource)
{

    auto vertexShader = Shader::createVertexShader(vertexShaderSource);
    auto fragmentShader = Shader::createFragmentShader(fragmentShaderSource);

    auto programId = glCreateProgram();
    glAttachShader(programId, vertexShader.m_shaderId);
    glAttachShader(programId, fragmentShader.m_shaderId);

    glLinkProgram(programId);

    GLint isLinked = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::string infoLog(maxLength, '\0');
        glGetProgramInfoLog(programId, maxLength, &maxLength, &infoLog[0]);

        std::cout << infoLog;

        // We don't need the program anymore.
        glDeleteProgram(programId);
        // Don't leak shaders either.
        glDeleteShader(vertexShader.m_shaderId);
        glDeleteShader(fragmentShader.m_shaderId);
    }

    // Always detach shaders after a successful link.
    glDetachShader(programId, vertexShader.m_shaderId);
    glDetachShader(programId, fragmentShader.m_shaderId);

    return Program(programId);
}
