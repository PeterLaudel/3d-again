#include <iostream>

#include "point.h"

cPoint::cPoint(float x, float y, float z) : m_x(x), m_y(y), m_z(z)
{
    std::cout << "cPoint" << std::endl;
};

cPoint::~cPoint()
{
    std::cout << "~cPoint" << std::endl;
}