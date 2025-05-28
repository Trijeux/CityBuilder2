#include <gtest/gtest.h>
#include "maths/angle.h"  // adapte le chemin selon ton projet

TEST(AngleConversionTest, DegreeToRadian)
{
	constexpr core::Degree deg90(90.0f);
	constexpr auto         rad = core::Radian(deg90);
	EXPECT_NEAR(static_cast<float>(rad), core::Pi / 2.0f, 1e-5f);
}

TEST(AngleConversionTest, RadianToDegree)
{
	constexpr core::Radian rad_pi(core::Pi);
	constexpr auto         deg = core::Degree(rad_pi);
	EXPECT_NEAR(static_cast<float>(deg), 180.0f, 1e-5f);
}

TEST(AngleConversionTest, RoundTripConversion)
{
	constexpr core::Degree original(123.45f);
	constexpr core::Radian rad(original);
	constexpr core::Degree converted(rad);
	EXPECT_NEAR(static_cast<float>(converted), static_cast<float>(original), 1e-5f);
}