#include "shader.h"

#include <fstream>
#include <iostream>
#include <optional>

#include <glad/glad.h>

std::optional<uint32_t> create(std::string const &shaderSource, GLenum shaderType)
{
    std::ifstream file(shaderSource, std::ios::in);
    if (!file.is_open())
    {
        std::cout << "Cannot load shader " << shaderSource;
        return {};
    }

    auto shaderText = std::string(std::istreambuf_iterator<char>(file),
                                  std::istreambuf_iterator<char>());
    auto src = shaderText.c_str();
    auto shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &src, nullptr);
    glCompileShader(shaderId);
    GLint isCompiled;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled)
    {
        GLint maxLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

        std::string errorLog(maxLength, '\0');
        glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);
        std::cout << errorLog;

        glDeleteShader(shaderId);
        return {};
    }
    return shaderId;
}

Shader::Shader(uint32_t shaderId) : m_shaderId(shaderId)
{
}

Shader::~Shader()
{
    glDeleteShader(this->id());
}

Shader Shader::createVertexShader(std::string shaderSource)
{
    auto shaderId = create(shaderSource, GL_VERTEX_SHADER);
    return Shader(*shaderId);
}

Shader Shader::createFragmentShader(std::string shaderSource)
{
    auto shaderId = create(shaderSource, GL_FRAGMENT_SHADER);
    return Shader(*shaderId);
}
