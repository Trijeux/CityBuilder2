#include <maths/vec2f.h>
#include <gtest/gtest.h>

struct Vec2fOperationFixture :
	public ::testing::TestWithParam<std::pair<core::Vec2f, core::Vec2f>>
{

};

TEST_P(Vec2fOperationFixture, Add)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 + v2;
	EXPECT_FLOAT_EQ(result.x, v1.x + v2.x);
	EXPECT_FLOAT_EQ(result.y, v1.y + v2.y);
}

TEST_P(Vec2fOperationFixture, Sub)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 - v2;
	EXPECT_FLOAT_EQ(result.x, v1.x - v2.x);
	EXPECT_FLOAT_EQ(result.y, v1.y - v2.y);

	const auto neg1 = -v1;
	const auto neg2 = -v2;
	EXPECT_FLOAT_EQ(neg1.x, -v1.x);
	EXPECT_FLOAT_EQ(neg1.y, -v1.y);
	EXPECT_FLOAT_EQ(neg2.x, -v2.x);
	EXPECT_FLOAT_EQ(neg2.y, -v2.y);
}

TEST_P(Vec2fOperationFixture, Dot)
{
	auto [v1, v2] = GetParam();
	const auto result = core::Vec2f::Dot(v1, v2);
	EXPECT_FLOAT_EQ(result, v1.x * v2.x + v1.y * v2.y);
}

TEST_P(Vec2fOperationFixture, Multi)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 * v2.x;
	const auto result2 = v1.x * v2;
	EXPECT_FLOAT_EQ(result.x, v1.x * v2.x);
	EXPECT_FLOAT_EQ(result.y, v1.y * v2.x);
	EXPECT_FLOAT_EQ(result2.x, v1.x * v2.x);
	EXPECT_FLOAT_EQ(result2.y, v1.x * v2.y);

}

TEST_P(Vec2fOperationFixture, Div)
{
	auto [v1, v2] = GetParam();
	if (v2.x != 0 || v2.y != 0)
	{
		const auto result1 = v1 / v2.x;
		const auto result2 = v1 / v2.y;
		const auto result3 = v2 / v2.x;
		const auto result4 = v2 / v2.y;
		
										 
		EXPECT_FLOAT_EQ(result1.x, v1.x / v2.x);
		EXPECT_FLOAT_EQ(result1.y, v1.y / v2.x);

		EXPECT_FLOAT_EQ(result2.x, v1.x / v2.y);
		EXPECT_FLOAT_EQ(result2.y, v1.y / v2.y);

		EXPECT_FLOAT_EQ(result3.x, v2.x / v2.x);
		EXPECT_FLOAT_EQ(result3.y, v2.y / v2.x);

		EXPECT_FLOAT_EQ(result4.x, v2.x / v2.y);
		EXPECT_FLOAT_EQ(result4.y, v2.y / v2.y);
	}
	else
	{
		std::cout << "Impossible" << std::endl;
	}
	if (v1.x != 0 || v1.y != 0)
	{
		const auto result1 = v2 / v1.x;
		const auto result2 = v2 / v1.y;
		const auto result3 = v1 / v1.x;
		const auto result4 = v1 / v1.y;

		EXPECT_FLOAT_EQ(result1.x, v2.x / v1.x);
		EXPECT_FLOAT_EQ(result1.y, v2.y / v1.x);

		EXPECT_FLOAT_EQ(result2.x, v2.x / v1.y);
		EXPECT_FLOAT_EQ(result2.y, v2.y / v1.y);

		EXPECT_FLOAT_EQ(result3.x, v1.x / v1.x);
		EXPECT_FLOAT_EQ(result3.y, v1.y / v1.x);

		EXPECT_FLOAT_EQ(result4.x, v1.x / v1.y);
		EXPECT_FLOAT_EQ(result4.y, v1.y / v1.y);
	}
	else
	{
		std::cout << "Impossible" << std::endl;
	}
}

TEST_P(Vec2fOperationFixture, Perpendicular)
{
	auto [v1, v2] = GetParam();
	const auto p1 = v1.Perpendicular();
	const auto p2 = v2.Perpendicular();
	EXPECT_FLOAT_EQ(core::Vec2f::Dot(v1, p1), 0);
	EXPECT_FLOAT_EQ(core::Vec2f::Dot(v2, p2), 0);

	const auto r1 = v1.Perpendicular2();
	const auto r2 = v2.Perpendicular2();
	EXPECT_FLOAT_EQ(core::Vec2f::Dot(v1, r1), 0);
	EXPECT_FLOAT_EQ(core::Vec2f::Dot(v2, r2), 0);
}

TEST_P(Vec2fOperationFixture, Lerp)
{
	auto [v1, v2] = GetParam();
	const auto result1 = core::Vec2f::Lerp(v1, v2.x);
	const auto result2 = core::Vec2f::Lerp(v1, v2.y);
	const auto result3 = core::Vec2f::Lerp(v2, v1.x);
	const auto result4 = core::Vec2f::Lerp(v2, v1.y);
	EXPECT_FLOAT_EQ(result1, v1.x * (1 - v2.x) + v1.y * v2.x);
	EXPECT_FLOAT_EQ(result2, v1.x * (1 - v2.y) + v1.y * v2.y);
	EXPECT_FLOAT_EQ(result3, v2.x * (1 - v1.x) + v2.y * v1.x);
	EXPECT_FLOAT_EQ(result4, v2.x * (1 - v1.y) + v2.y * v1.y);
	
}

TEST_P(Vec2fOperationFixture, Magnitude)
{
	auto [v1, v2] = GetParam();
	const auto resultv1 = v1.Magnitude();
	const auto resultv2 = v2.Magnitude();
	EXPECT_FLOAT_EQ(resultv1, v1.Magnitude());
	EXPECT_FLOAT_EQ(resultv2, v2.Magnitude());
}

TEST_P(Vec2fOperationFixture, SquMagnitude)
{
	auto [v1, v2] = GetParam();
	const auto resultv1 = v1.MagnitudeSqu();
	const auto resultv2 = v2.MagnitudeSqu();
	EXPECT_FLOAT_EQ(resultv1, v1.MagnitudeSqu());
	EXPECT_FLOAT_EQ(resultv2, v2.MagnitudeSqu());
}

TEST_P(Vec2fOperationFixture, Normalize)
{
	auto [v1, v2] = GetParam();
	auto resultv1 = v1.Normalize();
	auto resultv2 = v2.Normalize();
	if (v1.MagnitudeSqu() == 0)
	{
		EXPECT_FLOAT_EQ(resultv1.MagnitudeSqu(), 0);
	}
	else
	{
		EXPECT_FLOAT_EQ(resultv1.MagnitudeSqu(), 1);
	}
	if (v2.MagnitudeSqu() == 0)
	{
		EXPECT_FLOAT_EQ(resultv2.MagnitudeSqu(), 0);
	}
	else
	{
		EXPECT_FLOAT_EQ(resultv2.MagnitudeSqu(), 1);
	}
}

INSTANTIATE_TEST_SUITE_P(AllNumbers,
	Vec2fOperationFixture,
	testing::Values(
		std::pair{ core::Vec2f{1.5f,3.2f}, core::Vec2f{2.3f,-4.1f} },
		std::pair{ core::Vec2f{-10.2f, 15.2f}, core::Vec2f{-25.2f, -35.3f} },
		std::pair{ core::Vec2f{0.0f, 0.0f}, core::Vec2f{0.0f, 0.0f} },
		std::pair{ core::Vec2f{}, core::Vec2f{} },
		std::pair{ core::Vec2f{1.2f, 2.1f}, core::Vec2f{} },
		std::pair{ core::Vec2f{}, core::Vec2f{1.2f, 2.1f} }
	)
);
