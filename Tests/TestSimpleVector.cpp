//
// Created by User on 6/26/2019.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../SimpleVector.h"

using namespace simple;
using namespace std;

TEST(CTOR, simple_ctor)
{
    SimpleVector v0;
    SimpleVector v1(1);
    SimpleVector v2();
    SimpleVector v3{1};
    SimpleVector v4{1, 2, 3, 4};
}

TEST(EQUAL, simple_equal)
{
    SimpleVector v0{1};
    SimpleVector v1{1, 2, 3, 4};
    SimpleVector v2{1, 2, 3, 4};
    EXPECT_TRUE(v0 != v1);
    EXPECT_EQ(v1, v2);
}

TEST(CCTOR, simple_cctor)
{
    SimpleVector v1{1, 2, 3, 4};
    SimpleVector v2{v1};
    EXPECT_EQ(v1, v2);
}

TEST(ASSIGMENT, simple_assignment)
{
    SimpleVector v1{1, 2, 3, 4};
    SimpleVector v2;
    SimpleVector v3{1, 2};
    v2 = v1;
    EXPECT_EQ(v1, v2);
    v3 = v2;
    EXPECT_EQ(v1, v2);
}

TEST(MOVE_CTOR, simple_move)
{
    SimpleVector v1{1, 2, 3, 4};
    SimpleVector v2{v1};
    SimpleVector v3{std::move(v1)};
    EXPECT_TRUE(v3 != v1);
    EXPECT_TRUE(v3 == v2);
}

TEST(MOVE_ASSIGNMENT, simple_move_assignment)
{
    SimpleVector v1{1, 2, 3, 4};
    SimpleVector v2{v1};
    SimpleVector v3;
    v3 = {std::move(v1)};
    EXPECT_TRUE(v3 != v1);
    EXPECT_TRUE(v3 == v2);
}

