//
// Created by User on 3/22/2019.
//


#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../Complex.h"
#include <sstream>

using namespace exercises;

TEST(logic, equals)
{
    Complex first{0, 0};
    Complex second{0, 0};
    ASSERT_TRUE(first.GetReal() == second.GetReal());
    ASSERT_TRUE(first.GetIm() == second.GetIm());
    ASSERT_TRUE(first == second);
    first.SetReal(1);
    ASSERT_TRUE(first != second);
}


TEST(arithmetics, addition)
{
    Complex first{2, 0};
    Complex second{1, 1};
    Complex expected{3, 1};
    EXPECT_EQ(first + second, expected);


    second.SetIm(0);
    expected.SetIm(0);
    first += second;
    EXPECT_EQ(first, expected);
}

TEST(arithmetics, subtraction)
{
    Complex first{2, 0};
    Complex second{1, 1};
    Complex expected{1, -1};
    EXPECT_EQ(first - second, expected);


    second.SetReal(0);
    expected.SetReal(2);
    first -= second;
    EXPECT_EQ(first, expected);
}

TEST(arithmetics, multiplication)
{
    //(1+i)(2-i) = 3 + i
    Complex first{1, 1};
    Complex second{2, -1};
    Complex expected{3, 1};

    EXPECT_EQ(first * second, expected);
    first.SetReal(0);
    //i(2-i) =1 + 2i
    expected = {1, 2};
    first*= second;
    EXPECT_EQ(first, expected);
}

TEST(arithmetics, division)
{
    //(3+2i)/(4-3i) = (6/25) + i(17/25)
    Complex first{3, 2};
    Complex second{4, -3};
    Complex expected{double(6)/25, double(17)/25};

    EXPECT_EQ(first / second, expected);


    //(4 + 5i)/(2+6i) = (19/20) - i(7/20)
    first = {4, 5};
    second = {2, 6};
    expected = {double(19)/20, double(-7)/20};
    first/= second;
    EXPECT_EQ(first, expected);
}



TEST(stream, ostream)
{
    std::stringstream out;
    Complex c{1,1};
    out << c;
    std::string expected{"(1, 1)"};
    EXPECT_EQ(out.str(), expected);
}


TEST(stream, ostream1)
{
    Complex a {1, 2};
    Complex b {1, 2};
    //std::cout<< (1 + 2 += 3)<<std::endl;
    //std::cout<<(a + b += {2, 3})<<std::endl;
}



