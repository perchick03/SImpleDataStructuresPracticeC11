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
    {
        SimpleList<int> s0;
        SimpleList<int> s1{1, 2, 3, 4};
        cout<<s0<<s1;
    }
}

TEST(CCTOR, simple_cctor_list)
{
    SimpleList<int> s0{1, 2, 3, 4};
    SimpleList<int> s1{s0};
    cout<<"s1: "<<s1<<"so: "<<s0;
}
template<typename T>
class TypeName;

TEST(EQUAL, simple_equal_list_test)
{
    SimpleList<std::string> s0{"hello", "world"};
    SimpleList<std::string> s1{s0};
    SimpleList<std::string> s2{};
    //TypeName<decltype(s3)> TD;
    EXPECT_TRUE(s0 == s1);
    EXPECT_TRUE(s1 != s2);
    SimpleList<std::string> s3{"hello"};
    EXPECT_TRUE(s1 != s3);
    SimpleList<std::string> s4{"hello", "world", "!"};
    EXPECT_TRUE(s1 != s4);
}

TEST(MOVE_CCTOR, simple_move_cctor_list)
{
    SimpleList<std::string> s0{"hello", "world"};
    SimpleList<std::string> s2{s0};
    SimpleList<std::string> s1{std::move(s0)};

    EXPECT_TRUE(s0.empty());
    EXPECT_TRUE(s0.size() == 0);
    EXPECT_EQ(s2, s1);
}


TEST(MOVE_ASSIGNMENT, simple_move_assignment_list)
{
    SimpleList<std::string> s0{"hello", "world"};
    SimpleList<std::string> s1{s0};
    SimpleList<std::string> s2;
    s2 = std::move(s1);
    EXPECT_TRUE(s2 != s1);
    EXPECT_EQ(s2, s0);
}