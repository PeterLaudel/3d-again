#ifndef __PROGRAM__
#define __PROGRAM__

#include <optional>

class Shader;

class Program
{
public:
    ~Program();

    const uint32_t id() const { return m_programId; }

    bool verify() const;

    static Program create(
        Shader const &vertexShaderSource,
        Shader const &fragmentShaderSource);

private:
    Program(uint32_t programId);

    uint32_t m_programId;
};

#endif // __PROGRAM__