#ifndef __SHADER__
#define __SHADER__

#include <string>

class Shader
{
public:
    Shader(uint32_t shaderId);
    ~Shader();

    static Shader createVertexShader(
        std::string const &shaderSource);

    static Shader createFragmentShader(
        std::string const &shaderSource);

    uint32_t m_shaderId;
};

#endif // __SHADER__