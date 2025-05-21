#include "maths/small_vector.h"

#include <gtest/gtest.h>


TEST(SmallVector, Constructor)
{
	core::maths::SmallVector<int, 10> vec;
	EXPECT_EQ(vec.size(), 0);
	EXPECT_EQ(vec.capacity(), 10);
}

TEST(SmallVector, push_back)
{
	core::maths::SmallVector<int, 10> vec;
	vec.push_back(1);
	EXPECT_EQ(vec.size(), 1);
	EXPECT_EQ(vec.capacity(), 10);
}

TEST(SmallVector, pop_back)
{
	core::maths::SmallVector<int, 10> vec;
	vec.push_back(1);
	EXPECT_EQ(vec.size(), 1);
	EXPECT_EQ(vec.capacity(), 10);
	vec.pop_back();
	EXPECT_EQ(vec.size(), 0);
	EXPECT_EQ(vec.capacity(), 10);
}

TEST(SmallVector, Operator)
{
	core::maths::SmallVector<int, 10> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	EXPECT_EQ(vec.size(), 4);
	EXPECT_EQ(vec.capacity(), 10);
	EXPECT_EQ(vec.operator[](2), 3);
}

TEST(SmallVector, Begin)
{
	core::maths::SmallVector<int, 10> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	EXPECT_EQ(vec.size(), 4);
	EXPECT_EQ(vec.capacity(), 10);
	EXPECT_EQ(vec.begin(), 1);
}

TEST(SmallVector, End)
{
	core::maths::SmallVector<int, 10> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	EXPECT_EQ(vec.size(), 4);
	EXPECT_EQ(vec.capacity(), 10);
	EXPECT_EQ(vec.end(), 4);
}