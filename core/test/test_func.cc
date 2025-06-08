#include <gtest/gtest.h>
#include "maths/func.h"
#include "maths/angle.h"

using namespace core;

TEST(TrigTest, Cosine)
{
	EXPECT_NEAR(Cos(Degree(0)), 1.0f, 1e-6f);
	EXPECT_NEAR(Cos(Degree(90)), 0.0f, 1e-6f);
	EXPECT_NEAR(Cos(Degree(180)), -1.0f, 1e-6f);
	EXPECT_NEAR(Cos(Degree(270)), 0.0f, 1e-6f);
}

TEST(TrigTest, Sine)
{
	EXPECT_NEAR(Sin(Degree(0)), 0.0f, 1e-6f);
	EXPECT_NEAR(Sin(Degree(90)), 1.0f, 1e-6f);
	EXPECT_NEAR(Sin(Degree(180)), 0.0f, 1e-6f);
	EXPECT_NEAR(Sin(Degree(270)), -1.0f, 1e-6f);
}

TEST(TrigTest, Tangent)
{
	EXPECT_NEAR(Tan(Degree(0)), 0.0f, 1e-6f);
	EXPECT_NEAR(Tan(Degree(45)), 1.0f, 1e-6f);
	EXPECT_NEAR(Tan(Degree(135)), -1.0f, 1e-6f);
	const float t = Tan(Degree(90));
	EXPECT_TRUE(std::abs(t) > 1e6f);
}

TEST(TrigTest, Secant)
{
	EXPECT_NEAR(Sec(Degree(0)), 1.0f, 1e-6f);
	EXPECT_NEAR(Sec(Degree(30)), 1.0f / Cos(Degree(30)), 1e-6f);
	EXPECT_NEAR(Sec(Degree(60)), 1.0f / Cos(Degree(60)), 1e-6f);
	EXPECT_NEAR(Sec(Degree(180)), 1.0f / Cos(Degree(180)), 1e-6f);
}

TEST(MathPow, Power)
{
	EXPECT_EQ(Pow(2, 0), 1.0f);
	EXPECT_EQ(Pow(2, 1), 2.0f);
	EXPECT_EQ(Pow(2, 2), 4.0f);
	EXPECT_EQ(Pow(2, 3), 8.0f);
	EXPECT_EQ(Pow(2, 4), 16.0);
	EXPECT_EQ(Pow(2, 5), 32.0f);
	EXPECT_EQ(Pow(2, 6), 64.0f);
	EXPECT_EQ(Pow(2, 7), 128.0f);
	EXPECT_EQ(Pow(2, 8), 256.0f);
	EXPECT_EQ(Pow(2, 9), 512.0f);
}

TEST(TrigTest, ASine)
{
	EXPECT_NEAR(Degree(Radian(ASin(Sin(Degree(45))))).Value(), 45.0f, 1e-0f);
	EXPECT_NEAR(Degree(Radian(ASin(Sin(Degree(90))))).Value(), 90.0f, 1e-0f);
}

TEST(TrigTest, ACosine)
{
	EXPECT_NEAR(Degree(Radian(Acos(Cos(Degree(45))))).Value(), 45.0f, 1e-0f);
	EXPECT_NEAR(Degree(Radian(Acos(Cos(Degree(90))))).Value(), 90.0f, 1e-0f);
}

TEST(TrigTest, ATangent)
{
	EXPECT_NEAR(Degree(Radian(Atan(Tan(Degree(45))))).Value(), 45.0f, 1e-0f);
}