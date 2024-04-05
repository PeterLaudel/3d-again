#include <fstream>
#include <numeric>
#include <sstream>

#include "obj.h"

namespace obj
{

    class Line : public std::string
    {
    };

    std::istream &operator>>(std::istream &is, Line &line)
    {
        return std::getline(is, line);
    }

    std::istream &operator>>(std::stringstream &is, glm::vec3 &point)
    {
        std::string operation;
        is >> operation >> point.x >> point.y >> point.z;
        return is;
    }

    std::istream &operator>>(std::stringstream &is, glm::uvec3 &triangle)
    {
        std::string operation;
        is >> operation >> triangle.x >> triangle.y >> triangle.z;
        triangle.x--;
        triangle.y--;
        triangle.z--;
        return is;
    }

    std::optional<glm::vec3> getVec(const Line &line)
    {
        if (line.rfind("v", 0) != 0)
            return {};

        std::stringstream ss(line);
        glm::vec3 point;
        ss >> point;
        return point;
    };

    std::optional<glm::uvec3> getFace(const Line &line)
    {
        if (line.rfind("f", 0) != 0)
            return {};

        std::stringstream ss(line);
        glm::uvec3 triangle;
        ss >> triangle;
        return triangle;
    };

    C3DObject create(C3DObject object, const Line &line)
    {
        if (auto point = getVec(line))
        {
            object.addVec(*point);
            return object;
        }
        else if (auto triangle = getFace(line))
        {
            object.addTriangle(*triangle);
            return object;
        }
        return object;
    }
}

std::optional<C3DObject> Obj::load(const std::string &filename)
{
    std::ifstream istream(filename);
    if (!istream.is_open())
        return {};

    return std::accumulate(
        std::istream_iterator<obj::Line>(istream),
        std::istream_iterator<obj::Line>(),
        C3DObject(),
        &obj::create);
}