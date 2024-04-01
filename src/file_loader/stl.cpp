#include "stl.h"

#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <optional>
#include <numeric>
#include <algorithm>
#include <string>

#include <glm/vec3.hpp>

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

class StlFunctor
{
public:
    StlFunctor(){
        m_lastTriangleIndices.reserve(3);
    };

    C3DObject operator()(C3DObject object, const Line &line)
    {
        if (auto point = this->getVec(line))
        {
            object.addVec(*point);
            m_lastTriangleIndices.push_back(object.vecs().size() - 1);
            return object;
        }
        else if (auto triangle = this->getTriangle(line))
        {
            object.addTriangle(*triangle);
            return object;
        }
        return object;
    }

    std::optional<glm::vec3> getVec(const Line &line)
    {
        if (line.rfind("vertex", 0) != 0)
            return {};

        std::stringstream ss(line);
        glm::vec3 point;
        ss >> point;
        return point;
    };

    std::optional<glm::uvec3> getTriangle(const Line &line)
    {
        if (line.rfind("endloop", 0) != 0)
            return {};
        auto triangle =  glm::uvec3(
            m_lastTriangleIndices[0],
            m_lastTriangleIndices[1],
            m_lastTriangleIndices[2]
        );

        m_lastTriangleIndices.clear();
        return triangle;
    };

    private:

    std::vector<uint32_t> m_lastTriangleIndices;

};

std::optional<C3DObject> Stl::load(const std::string &filename)
{
    std::ifstream istream(filename);
    if (!istream.is_open())
        return {};

    return std::accumulate(
        std::istream_iterator<Line>(istream),
        std::istream_iterator<Line>(),
        C3DObject(),
        StlFunctor());
};
