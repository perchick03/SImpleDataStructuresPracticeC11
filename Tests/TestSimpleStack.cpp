//
// Created by User on 6/28/2019.
//



#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <initializer_list>
#include <iterator> //rbegin
#include "../SimpleStack.h"


using namespace std;
using namespace simple;

TEST(CTOR, simple_stack_ctor)
{
    SimpleStack<int> s0;
    SimpleStack<int> s1{};
    SimpleStack<int> s2{1, 2, 3};
    cout<<"s0: "<<s0<<"\n";
    cout<<"s1: "<<s1<<"\n";
    cout<<"s2: "<<s2<<"\n";

}

TEST(COPY_BEHAVIOR, simple_stack_cctor_and_assignment)
{
    SimpleStack<int> s0{1, 2, 3};
    SimpleStack<int> s1{s0};
    EXPECT_TRUE(s0 == s1);
    SimpleStack<int> s2{};
    EXPECT_TRUE(s1 != s2);
    SimpleStack<int> s3{};
    EXPECT_TRUE(s2 == s3);
    s2 = s0;
    EXPECT_TRUE(s0 == s2);
}

TEST(MOVE_BEHAVIOR, simple_stack_move_cctor_and_assignment)
{
    SimpleStack<int> s0{1, 2, 3};
    SimpleStack<int> s1{s0};
    SimpleStack<int> s2{std::move(s0)};
    EXPECT_TRUE(s2 == s1);
    EXPECT_TRUE(s0.empty());
    s0 = s1 = {1, 2};
    s2 = std::move(s0);
    EXPECT_TRUE(s1 == s2);
}


TEST(PUSH, simple_stack_push)
{
    SimpleStack<std::string> s0;
    SimpleStack<std::string> s1 {"hello", "world"};
    s0.push("hello");
    s0.push("world");
    EXPECT_EQ(s0, s1);
    s0.push("!");
    EXPECT_TRUE(s0 != s1);
    EXPECT_EQ(3, s0.size());

}
TEST(EMPLACE, simple_stack_emplace)
{
    SimpleStack<std::string> s0;
    SimpleStack<std::string> s1 {"hello", "world"};
    s0.emplace("hello");
    s0.emplace("world");
    EXPECT_EQ(s0, s1);
    s0.emplace(std::string{"!"});
    EXPECT_TRUE(s0 != s1);
    EXPECT_EQ(3, s0.size());
}

TEST(TOP_AND_POP, simple_stack_top)
{
    auto il = {1, 2, 3, 4};

    SimpleStack<int> s0{il};
    for (auto it = std::rbegin(il); it != std::rend(il); ++it) {
        EXPECT_EQ(*it, s0.top());
        s0.pop();
    }

}

