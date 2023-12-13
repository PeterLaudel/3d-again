#include <vector>

#include "point.h"

class C3DObject {
public:
    C3DObject(const std::vector<cPoint>& points);
    ~C3DObject();

private:
    std::vector<cPoint> m_points;
};