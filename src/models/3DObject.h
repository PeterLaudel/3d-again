#ifndef __3DOBJECT__
#define __3DOBJECT__

#include <vector>

#include "point.h"

class C3DObject
{
public:
    C3DObject() = default;
    ~C3DObject();

    int addPoint(cPoint point)
    {
        this->m_points.emplace_back(point);
        return m_points.size();
    };

    std::vector<cPoint> &points() { return this->m_points; };

private:
    std::vector<cPoint> m_points;
};

#endif /* __3DOBJECT__ */
