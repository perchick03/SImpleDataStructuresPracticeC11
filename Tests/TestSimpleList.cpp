//
// Created by User on 6/27/2019.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "../SimpleList.h"

using namespace simple;
using namespace std;

TEST(CTOR, simple_ctor_list)
{

    SimpleList<int> s0{};
    SimpleList<int> s1{1, 2, 3, 4};
    SimpleList<int> s2{};
    EXPECT_EQ(s0, s2);
}

TEST(CCTOR, simple_cctor_list)
{
    SimpleList<int> s0{1, 2, 3, 4};
    SimpleList<int> s1{s0};
    EXPECT_EQ(s0, s1);
}

TEST(EQUAL, simple_equal_list_test)
{
    SimpleList<std::string> s0{"hello", "world"};
    SimpleList<std::string> s1{s0};
    SimpleList<std::string> s2{};
    EXPECT_TRUE(s0 == s1);
    EXPECT_TRUE(s1 != s2);
    SimpleList<std::string> s3{"hello"};
    EXPECT_TRUE(s1 != s3);

}

TEST(MOVE_CCTOR, simple_move_cctor_list)
{
    SimpleList<std::string> s0{"hello", "world"};
    SimpleList<std::string> s2{s0};
    SimpleList<std::string> s1{std::move(s0)};


    EXPECT_EQ(s2, s1);
}


TEST(MOVE_ASSIGNMENT, simple_move_assignment_list)
{
    SimpleList<std::string> s0{"hello", "world"};
    SimpleList<std::string> s1{s0};
    SimpleList<std::string> s2;
    s2 = std::move(s1);

    EXPECT_EQ(s2, s0);
}