#include "stl.h"

#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <optional>
#include <numeric>
#include <algorithm>
#include <string>

class Line : public std::string
{
};

std::istream &operator>>(std::istream &is, Line &line)
{
    return std::getline(is, line);
}

std::istream &operator>>(std::stringstream &is, cPoint point)
{
    std::string operation;
    is >> operation >> point.x >> point.y >> point.z;
    return is;
}

class StlFunctor
{
public:
    C3DObject operator()(C3DObject object, const Line &line)
    {
        if (auto point = this->getPoint(line))
        {
            object.addPoint(*point);
            return object;
        }
        return object;
    }

    std::optional<cPoint> getPoint(const Line &line)
    {
        if (line.rfind("vertex", 0) != 0)
            return {};

        std::stringstream ss(line);
        cPoint point;
        ss >> point;
        return point;
    };
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
