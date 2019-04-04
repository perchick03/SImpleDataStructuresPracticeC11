//
// Created by User on 4/1/2019.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

//TODO: handle relative path
#include "../linked_list.h"

namespace ex = exercise;

class TestSimpleList: public ::testing::Test
{
public:

protected:
    ex::list<int> mList;
};

TEST_F(TestSimpleList, push_back)
{
    mList.push_back(1);
    EXPECT_EQ(mList.back(), 1);
    mList.push_back(2);
    EXPECT_EQ(mList.back(), 2);
}

TEST_F(TestSimpleList, list_state)
{
    EXPECT_TRUE(mList.empty());
    mList.push_back(1);
    mList.push_back(2);
    EXPECT_EQ(mList.size(), 2);
}

TEST_F(TestSimpleList, push_front)
{
    mList.push_back(1);
    EXPECT_EQ(mList.back(), 1);
    mList.push_front(2);
    EXPECT_EQ(mList.front(), 2);
}

TEST_F(TestSimpleList, pop_back)
{
    mList.push_back(1);
    mList.push_back(2);
    mList.push_back(3);
    EXPECT_EQ(mList.size(), 3);
    mList.pop_back();
    EXPECT_EQ(mList.size(), 2);
    EXPECT_EQ(mList.back(), 2);
}

TEST_F(TestSimpleList, pop_front)
{
    mList.push_back(1);
    mList.push_back(2);
    mList.push_back(3);
    EXPECT_EQ(mList.size(), 3);
    mList.pop_front();
    EXPECT_EQ(mList.size(), 2);
    EXPECT_EQ(mList.front(), 2);
}


TEST_F(TestSimpleList, sort)
{

    constexpr size_t LIST_SIZE = 10;
    std::array<int, LIST_SIZE> arr{0};
    std::srand(std::time(nullptr));

    for (size_t i = 0; i < LIST_SIZE; ++i) {
        auto rand_int = std::rand()%100;
        arr[i] = rand_int;
        mList.push_back(rand_int);
    }
    std::sort(arr.begin(), arr.end());
  //  std::cout<<mList<<std::endl;
    mList.sort();
    //std::cout<<mList<<std::endl;
    for (size_t j = 0; j < LIST_SIZE; ++j) {
        EXPECT_EQ(arr[j], mList.front());
        mList.pop_front();
    }
}

TEST_F(TestSimpleList, remove_duplicates)
{
    constexpr size_t ARR_SIZE = 10;
    std::array<int, ARR_SIZE> arr{0};
    for(auto num: arr){
        mList.push_back(num);
    }
    mList.remove_duplicates();
    std::cout<<mList<<std::endl;
    EXPECT_EQ(mList.size(), 1);
    EXPECT_EQ(mList.front(), 0);
    mList.pop_front();
    int number_for_duplication =10;
    for (size_t i = 0; i < ARR_SIZE; ++i) {
        if(i == 2 || i == 1 || i == 5){
            mList.push_back(number_for_duplication);
            continue;
        }
        mList.push_back(i);
    }
    //std::cout<<mList<<std::endl;
    mList.remove_duplicates();
    //std::cout<<mList<<std::endl;
    bool found_testing_number = false;
    while(!mList.empty()){
        if(mList.front() == number_for_duplication){
            EXPECT_FALSE(found_testing_number);
            found_testing_number = true;
        }
        mList.pop_front();
    }
}

TEST_F(TestSimpleList, flip)
{
    constexpr size_t LIST_SIZE = 10;
    std::array<int, LIST_SIZE> arr{0};
    std::srand(std::time(nullptr));

    for (size_t i = 0; i < LIST_SIZE; ++i) {
        auto rand_int = std::rand()%100;
        arr[i] = rand_int;
        mList.push_front(rand_int);
    }
    //std::cout<<mList<<std::endl;
    mList.flip();
    //std::cout<<mList<<std::endl;
    for (size_t j = 0; j < LIST_SIZE; ++j) {
        EXPECT_EQ(arr[j], mList.front());
        mList.pop_front();
    }
}