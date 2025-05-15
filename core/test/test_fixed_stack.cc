#include <gtest/gtest.h>

#include "maths/fixed_stack.h"

TEST(FixedStack, Constructor)
{
	core::FixedStack<int, 10> FS;
	EXPECT_TRUE(FS.IsEmpty());
	EXPECT_EQ(FS.Capacity(), 10);
	EXPECT_EQ(FS.Size(), 0);
}

TEST(FixedStack, Push)
{
	core::FixedStack<int, 10> FS;
	FS.push(1);
	EXPECT_EQ(FS.Capacity(), 10);
	EXPECT_EQ(FS.Size(), 1);
}

TEST(FixedStack, Pop)
{
	core::FixedStack<int, 10> FS;
	FS.push(1);
	EXPECT_EQ(FS.Capacity(), 10);
	EXPECT_EQ(FS.Size(), 1);
	FS.pop();
	EXPECT_EQ(FS.Capacity(), 10);
	EXPECT_EQ(FS.Size(), 0);
}

TEST(FixedStack, Top)
{
	core::FixedStack<int, 10> FS;
	FS.push(1);
	FS.push(2);
	FS.push(3);
	EXPECT_EQ(FS.top(), 3);
	FS.pop();
	EXPECT_EQ(FS.top(), 2);
	FS.pop();
	EXPECT_EQ(FS.top(), 1);
}