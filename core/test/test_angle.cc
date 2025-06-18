#include <gtest/gtest.h>
#include "maths/angle.h"  // adapte le chemin selon ton projet

TEST(AngleConversionTest, DegreeToRadian)
{
	constexpr core::maths::Degree deg90(90.0f);
	const auto rad = core::maths::Radian<float>(deg90);
	EXPECT_NEAR(static_cast<float>(rad), core::maths::Pi<float> / 2.0f, 1e-5f);
}

TEST(AngleConversionTest, RadianToDegree)
{
	constexpr core::maths::Radian rad_pi(core::maths::Pi<float>);
	const auto         deg = core::maths::Degree<float>(rad_pi);
	EXPECT_NEAR(static_cast<float>(deg), 180.0f, 1e-5f);
}

TEST(AngleConversionTest, RoundTripConversion)
{
	constexpr core::maths::Degree original(123.45f);
	const core::maths::Radian<float> rad(original);
	const core::maths::Degree<float> converted(rad);
	EXPECT_NEAR(static_cast<float>(converted), static_cast<float>(original), 1e-5f);
}