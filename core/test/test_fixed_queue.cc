#include "maths/fixed_queue.h"

#include <gtest/gtest.h>

TEST(FixedQueue, Constructor)
{
	core::maths::FixedQueue<int, 10> FQ;
	EXPECT_TRUE(FQ.IsEmpty());
	EXPECT_EQ(FQ.Capacity(), 10);
	EXPECT_EQ(FQ.Size(), 0);
}

TEST(FixedQueue, Enqueue)
{
	core::maths::FixedQueue<int, 10> FQ;
	FQ.enqueue(1);
	EXPECT_EQ(FQ.Capacity(), 10);
	EXPECT_EQ(FQ.Size(), 1);
}

TEST(FixedQueue, Dequeue)
{
	core::maths::FixedQueue<int, 10> FQ;
	FQ.enqueue(1);
	EXPECT_EQ(FQ.Capacity(), 10);
	EXPECT_EQ(FQ.Size(), 1);
	FQ.dequeue();
	EXPECT_EQ(FQ.Capacity(), 10);
	EXPECT_EQ(FQ.Size(), 0);
}

TEST(FixedQueue, Front)
{
	core::maths::FixedQueue<int, 10> FQ;
	FQ.enqueue(1);
	FQ.enqueue(2);
	FQ.enqueue(3);
	EXPECT_EQ(FQ.front(), 1);
	FQ.dequeue();
	EXPECT_EQ(FQ.front(), 2);
	FQ.dequeue();
	EXPECT_EQ(FQ.front(), 3);
}