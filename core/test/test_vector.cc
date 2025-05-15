#include <gtest/gtest.h>
#include "maths/Vector.h"


TEST(Vector, Constructor)
{
	core::Vector<int> vec;
	EXPECT_EQ(vec.size(), 0);
	EXPECT_EQ(vec.capacity(), 0);
	EXPECT_TRUE(vec.IsEmpty());
}

TEST(Vector, push_back)
{
	core::Vector<int> vec;
	vec.push_back(1);
	EXPECT_EQ(vec.size(), 1);
	EXPECT_EQ(vec.capacity(), 1);
	EXPECT_FALSE(vec.IsEmpty());
}

TEST(Vector, pop_back)
{
	core::Vector<int> vec;
	vec.push_back(1);
	EXPECT_EQ(vec.size(), 1);
	EXPECT_EQ(vec.capacity(), 1);
	vec.pop_back();
	EXPECT_EQ(vec.size(), 0);
	EXPECT_EQ(vec.capacity(), 0);
}

TEST(Vector, Operator)
{
	core::Vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	EXPECT_EQ(vec.size(), 4);
	EXPECT_EQ(vec.capacity(), 4);
	EXPECT_EQ(vec.operator[](2), 3);
}

TEST(Vector, Reserve)
{
	core::Vector<int> vec;
	vec.reserve(50);
	EXPECT_EQ(vec.size(), 0);
	EXPECT_EQ(vec.capacity(), 50);
	EXPECT_TRUE(vec.IsEmpty());
}

TEST(Vector, Resize)
{
	core::Vector<int> vec;
	vec.reserve(50);
	EXPECT_EQ(vec.size(), 0);
	EXPECT_EQ(vec.capacity(), 50);
	EXPECT_TRUE(vec.IsEmpty());
	vec.resize(25);
	EXPECT_EQ(vec.size(), 25);
	EXPECT_EQ(vec.capacity(), 50);
}

TEST(Vector, Clear)
{
	core::Vector<int> vec;
	vec.reserve(50);
	vec.resize(25);
	EXPECT_EQ(vec.size(), 25);
	EXPECT_EQ(vec.capacity(), 50);
	vec.clear();
	EXPECT_EQ(vec.size(), 0);
	EXPECT_EQ(vec.capacity(), 0);
}