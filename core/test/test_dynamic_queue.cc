#include "maths/dynamic_queue.h"

#include <gtest/gtest.h>



TEST(DinamicQueue, Constructor)
{
	core::maths::DynamicQueue<int> DQ;
	EXPECT_TRUE(DQ.IsEmpty());
	EXPECT_EQ(DQ.Capacity(), 0);
	EXPECT_EQ(DQ.Size(), 0);
}

TEST(DinamicQueue, Enqueue)
{
	core::maths::DynamicQueue<int> DQ;
	DQ.enqueue(1);
	EXPECT_EQ(DQ.Capacity(), 1);
	EXPECT_EQ(DQ.Size(), 1);
}

TEST(DinamicQueue, Dequeue)
{
	core::maths::DynamicQueue<int> DQ;
	DQ.enqueue(1);
	EXPECT_EQ(DQ.Capacity(), 1);
	EXPECT_EQ(DQ.Size(), 1);
	DQ.dequeue();
	EXPECT_EQ(DQ.Capacity(), 0);
	EXPECT_EQ(DQ.Size(), 0);
}

TEST(DinamicQueue, Front)
{
	core::maths::DynamicQueue<int> DQ;
	DQ.enqueue(1);
	DQ.enqueue(2);
	DQ.enqueue(3);
	EXPECT_EQ(DQ.front(), 1);
	DQ.dequeue();
	EXPECT_EQ(DQ.front(), 2);
	DQ.dequeue();
	EXPECT_EQ(DQ.front(), 3);
}