#ifndef __PROGRAM__
#define __PROGRAM__

#include <optional>

class Program
{
public:
    ~Program();

    const uint32_t id() const { return m_programId; }

    static Program create(
        std::string const &vertexShaderSource,
        std::string const &fragmentShaderSource);

private:
    Program(uint32_t programId);

    uint32_t m_programId;
};

#endif // __PROGRAM__