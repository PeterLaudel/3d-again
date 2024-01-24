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
        auto result = Stl::load("./files/cube_ascii.stl");
        std::cout << "HUHU";
        m_o3Dobject = *result;
    };

    C3DObject m_o3Dobject;
};

TEST_F(AStlFileLoader, AddsAllPointsTo3DObject)
{
    EXPECT_EQ(m_o3Dobject.points().size(), 36);
};
