//
// Created by User on 6/29/2019.
//


#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "../SimpleQueue.h"

using namespace simple;
using namespace std;


TEST(CTOR, simple_queue_ctor)
{
    SimpleQueue<int, 3> q;
    SimpleQueue<int, 3> q2{};
    SimpleQueue<int, 3> q3{1, 2, 3};
    EXPECT_EQ(q, q2);
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(3, q3.size());
    SimpleQueue<int, 3> q4{1, 2, 3, 4, 5, 6};
    SimpleQueue<int, 2> q5{1, 0};
    EXPECT_EQ(q3, q4);
    cout<<q;
    cout<<q3;
    cout<<q5;
}

TEST(PUSH_AND_POP, simple_queue_push)
{
    srand(time(nullptr));
    std::vector<int> v{};
    SimpleQueue<int> q{};
    for (int i = 0; i < 10; ++i) {
        auto val = rand()%100;
        v.push_back(val);
        if(i%5)
            q.push(std::move(val));
        else
            q.push(val);
    }

    EXPECT_EQ(10, q.size());
    while(!q.empty())
    {
        EXPECT_EQ(q.pop(), v.front());
        v.erase(v.begin());
    }
}
TEST(FRONT_AND_BACK, simple_queue_front_and_back)
{
    SimpleQueue<std::string, 4> q{"One", "Two", "Three", "Four"};

    EXPECT_EQ(std::string{"One"}, q.front());
    EXPECT_EQ(std::string{"Four"}, q.back());
}
TEST(UNDEFINED_BEHAVIOR, simple_queue_UB)
{
    SimpleQueue<int> q;
    bool UB_flag = false;
    try
    {
        q.pop();
    }
    catch (std::out_of_range& e)
    {
        UB_flag = true;
    }
    EXPECT_TRUE(UB_flag);

}

