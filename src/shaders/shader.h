#ifndef __SHADER__
#define __SHADER__

#include <string>

class Shader
{
public:
    ~Shader();

    static Shader createVertexShader(
        std::string shaderSource);

    static Shader createFragmentShader(
        std::string shaderSource);

    uint32_t id() const { return m_shaderId; }

private:
    Shader(uint32_t shaderId);

    uint32_t m_shaderId;
};

#endif // __SHADER__