#include "maths/dynamic_stack.h"

#include <gtest/gtest.h>


TEST(DynamicStack, Constructor)
{
	core::maths::DynamicStack<int> DS;
	EXPECT_TRUE(DS.IsEmpty());
	EXPECT_EQ(DS.Capacity(), 0);
	EXPECT_EQ(DS.Size(), 0);
}

TEST(DynamicStack, Push)
{
	core::maths::DynamicStack<int> DS;
	DS.push(1);
	EXPECT_EQ(DS.Capacity(), 1);
	EXPECT_EQ(DS.Size(), 1);
}

TEST(DynamicStack, Pop)
{
	core::maths::DynamicStack<int> DS;
	DS.push(1);
	EXPECT_EQ(DS.Capacity(), 1);
	EXPECT_EQ(DS.Size(), 1);
	DS.pop();
	EXPECT_EQ(DS.Capacity(), 0);
	EXPECT_EQ(DS.Size(), 0);
}

TEST(DynamicStack, Top)
{
	core::maths::DynamicStack<int> DS;
	DS.push(1);
	DS.push(2);
	DS.push(3);
	EXPECT_EQ(DS.top(), 3);
	DS.pop();
	EXPECT_EQ(DS.top(), 2);
	DS.pop();
	EXPECT_EQ(DS.top(), 1);
}