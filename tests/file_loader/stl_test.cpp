#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <memory>

#include "models/3DObject.h"

#include "file_loader/stl.h"
#include <iostream>
using namespace testing;

class AStlFileLoader : public Test
{

protected:
    void SetUp() override
    {
        auto result = Stl::load("./files/triangle.stl");
        m_o3Dobject = *result;
    };

    C3DObject m_o3Dobject;
};

TEST_F(AStlFileLoader, AddsAllPointsTo3DObject)
{
    auto const &points = m_o3Dobject.points();
    EXPECT_EQ(points.size(), 3);
    EXPECT_EQ(points[0], cPoint(-0.5f, -0.5f, 0.0f));
    EXPECT_EQ(points[1], cPoint(0.5, -0.5, 0.0));
    EXPECT_EQ(points[2], cPoint(0.0, 0.5, 0.0));
};
