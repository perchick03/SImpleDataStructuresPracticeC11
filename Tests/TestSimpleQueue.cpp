//
// Created by User on 4/2/2019.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../SimpleQueue.h"

using namespace exercise;


TEST(TestSimpleQueue, sanity_push_pop)
{
    constexpr size_t QUEUE_SIZE = 5;
    SimpleQueue<int, QUEUE_SIZE> simple_queue;

    EXPECT_TRUE(simple_queue.empty());
    simple_queue.push(1);
    EXPECT_FALSE(simple_queue.empty());

    EXPECT_EQ(simple_queue.size(), 1);
    EXPECT_EQ(simple_queue.pop(), 1);
    EXPECT_TRUE(simple_queue.empty());

    simple_queue.pop();
    EXPECT_TRUE(simple_queue.empty());


    for(size_t i = 0; i < QUEUE_SIZE + 2; ++i){
        simple_queue.push(i); //{0, 1, 2, 3, 4}
    }
    EXPECT_EQ(simple_queue.size(), 5);

    for(size_t i = 0; i < QUEUE_SIZE; ++i){
        EXPECT_EQ(simple_queue.pop(), i);
    }
}

TEST(TestSimpleQueue, back)
{
    constexpr size_t QUEUE_SIZE = 5;
    SimpleQueue<int, QUEUE_SIZE> simple_queue;
    auto q_expected_size = QUEUE_SIZE -1;
    auto final_element_to_insert = QUEUE_SIZE -2;
    for (size_t i = 0; i < QUEUE_SIZE - 1; ++i) {
        simple_queue.push(i);
    }

    EXPECT_EQ(simple_queue.size(), q_expected_size);
    EXPECT_EQ(simple_queue.back(), final_element_to_insert);
    EXPECT_EQ(simple_queue.size(), q_expected_size -1);
}

