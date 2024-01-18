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

using namespace testing;

class AStlFileLoader : public Test
{

protected:
    void SetUp() override
    {
        m_o3Dobject = Stl::load("cube_ascii.stl");
    };

    C3DObject m_o3Dobject;
};

TEST_F(AStlFileLoader, AddsAllPointsTo3DObject)
{
    std::vector<cPoint> array{{1, 2, 3}};
    EXPECT_EQ(m_o3Dobject.points().size(), 36);
};
