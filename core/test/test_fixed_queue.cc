#include <gtest/gtest.h>

#include "maths/fixed_queue.h"

TEST(FixedQueue, Constructor)
{
	core::FixedQueue<int, 10> FQ;
	EXPECT_TRUE(FQ.IsEmpty());
	EXPECT_EQ(FQ.Capacity(), 10);
	EXPECT_EQ(FQ.Size(), 0);
}

TEST(FixedQueue, Enqueue)
{
	core::FixedQueue<int, 10> FQ;
	FQ.enqueue(1);
	EXPECT_EQ(FQ.Capacity(), 10);
	EXPECT_EQ(FQ.Size(), 1);
}

TEST(FixedQueue, Dequeue)
{
	core::FixedQueue<int, 10> FQ;
	FQ.enqueue(1);
	EXPECT_EQ(FQ.Capacity(), 10);
	EXPECT_EQ(FQ.Size(), 1);
	FQ.dequeue();
	EXPECT_EQ(FQ.Capacity(), 10);
	EXPECT_EQ(FQ.Size(), 0);
}

TEST(FixedQueue, Front)
{
	core::FixedQueue<int, 10> FQ;
	FQ.enqueue(1);
	FQ.enqueue(2);
	FQ.enqueue(3);
	EXPECT_EQ(FQ.front(), 1);
	FQ.dequeue();
	EXPECT_EQ(FQ.front(), 2);
	FQ.dequeue();
	EXPECT_EQ(FQ.front(), 3);
}