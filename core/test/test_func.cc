#include <gtest/gtest.h>
#include "maths/func.h"
#include "maths/angle.h"

using namespace core;

TEST(TrigTest, Cosine)
{
	EXPECT_NEAR(Cos(Degree(0)), 1.0f, 1e-5f);
	EXPECT_NEAR(Cos(Degree(90)), 0.0f, 1e-5f);
	EXPECT_NEAR(Cos(Degree(180)), -1.0f, 1e-5f);
	EXPECT_NEAR(Cos(Degree(270)), 0.0f, 1e-5f);
}

TEST(TrigTest, Sine)
{
	EXPECT_NEAR(Sin(Degree(0)), 0.0f, 1e-5f);
	EXPECT_NEAR(Sin(Degree(90)), 1.0f, 1e-5f);
	EXPECT_NEAR(Sin(Degree(180)), 0.0f, 1e-5f);
	EXPECT_NEAR(Sin(Degree(270)), -1.0f, 1e-5f);
}

TEST(TrigTest, Tangent)
{
	EXPECT_NEAR(Tan(Degree(0)), 0.0f, 1e-5f);
	EXPECT_NEAR(Tan(Degree(45)), 1.0f, 1e-5f);
	EXPECT_NEAR(Tan(Degree(135)), -1.0f, 1e-5f);
	const float t = Tan(Degree(90));
	EXPECT_TRUE(std::abs(t) > 1e6f);
}
