#include "3DObject.h"

#include <iostream>

C3DObject::C3DObject(const std::vector<cPoint>& points): m_points(points)
{
    std::cout << "C3DObject" << std::endl;
}

C3DObject::~C3DObject()
{
    std::cout << "~C3DObject" << std::endl;
}
