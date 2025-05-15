#include <gtest/gtest.h>
#include "maths/basic_vector.h"


TEST(BasicVector, Constructor)
{
	core::BasicVector<int, 10> vec;
	EXPECT_EQ(vec.size(), 0);
	EXPECT_EQ(vec.capacity(), 10);
}

TEST(BasicVector, push_back)
{
	core::BasicVector<int, 10> vec;
	vec.push_back(1);
	EXPECT_EQ(vec.size(), 1);
	EXPECT_EQ(vec.capacity(), 10);
}

TEST(BasicVector, pop_back)
{
	core::BasicVector<int, 10> vec;
	vec.push_back(1);
	EXPECT_EQ(vec.size(), 1);
	EXPECT_EQ(vec.capacity(), 10);
	vec.pop_back();
	EXPECT_EQ(vec.size(), 0);
	EXPECT_EQ(vec.capacity(), 10);
}

TEST(BasicVector, Operator)
{
	core::BasicVector<int, 10> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	EXPECT_EQ(vec.size(), 4);
	EXPECT_EQ(vec.capacity(), 10);
	EXPECT_EQ(vec.operator[](2), 3);
}

TEST(BasicVector, Reserve)
{
	core::BasicVector<int, 10> vec;
	EXPECT_EQ(vec.size(), 0);
	EXPECT_EQ(vec.capacity(), 10);
	vec.reserve(50);
	EXPECT_EQ(vec.size(), 0);
	EXPECT_EQ(vec.capacity(), 50);
}

TEST(BasicVector, Begin)
{
	core::BasicVector<int, 10> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	EXPECT_EQ(vec.size(), 4);
	EXPECT_EQ(vec.capacity(), 10);
	EXPECT_EQ(vec.begin(), 1);
}

TEST(BasicVector, End)
{
	core::BasicVector<int, 10> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	EXPECT_EQ(vec.size(), 4);
	EXPECT_EQ(vec.capacity(), 10);
	EXPECT_EQ(vec.end(), 4);
}