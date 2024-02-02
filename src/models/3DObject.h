#ifndef __3DOBJECT__
#define __3DOBJECT__

#include <vector>
#include <optional>
#include <functional>

#include "point.h"

class C3DObject
{
public:
    C3DObject() = default;
    ~C3DObject() = default;

    using C3DObjectDrawer = std::function<void(const C3DObject &)>;

    void setDrawer(C3DObjectDrawer drawer)
    {
        m_drawer = drawer;
    }

    void draw()
    {
        m_drawer(*this);
    }

    void addPoint(cPoint point)
    {
        m_points.emplace_back(point);
    }

    const std::vector<cPoint> &points() const
    {
        return this->m_points;
    };

private:
    std::vector<cPoint> m_points;
    C3DObjectDrawer m_drawer;
};

#endif /* __3DOBJECT__ */
