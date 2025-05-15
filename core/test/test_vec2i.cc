#include <maths/vec2i.h>
#include <gtest/gtest.h>


struct Vec2iOperationFixture :
	public ::testing::TestWithParam<std::pair<core::Vec2i, core::Vec2i>>
{

};

TEST_P(Vec2iOperationFixture, Add)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 + v2;
	EXPECT_EQ(result.x, v1.x + v2.x);
	EXPECT_EQ(result.y, v1.y + v2.y);
}

TEST_P(Vec2iOperationFixture, Sub)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 - v2;
	EXPECT_EQ(result.x, v1.x - v2.x);
	EXPECT_EQ(result.y, v1.y - v2.y);

	const auto neg1 = -v1;
	const auto neg2 = -v2;
	EXPECT_EQ(neg1.x, -v1.x);
	EXPECT_EQ(neg1.y, -v1.y);
	EXPECT_EQ(neg2.x, -v2.x);
	EXPECT_EQ(neg2.y, -v2.y);
}

TEST_P(Vec2iOperationFixture, Dot)
{
	auto [v1, v2] = GetParam();
	const auto result = core::Vec2i::Dot(v1, v2);
	EXPECT_EQ(result, v1.x * v2.x + v1.y * v2.y);
}

TEST_P(Vec2iOperationFixture, Multi)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 * v2.x;
	const auto result2 = v1.x * v2;
	EXPECT_FLOAT_EQ(result.x, v1.x * v2.x);
	EXPECT_FLOAT_EQ(result.y, v1.y * v2.x);
	EXPECT_FLOAT_EQ(result2.x, v1.x * v2.x);
	EXPECT_FLOAT_EQ(result2.y, v1.x * v2.y);
}

TEST_P(Vec2iOperationFixture, Div)
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

TEST_P(Vec2iOperationFixture, Perpendicular)
{
	auto [v1, v2] = GetParam();
	const auto p1 = v1.Perpendicular();
	const auto p2 = v2.Perpendicular();
	EXPECT_EQ(core::Vec2i::Dot(v1, p1), 0);
	EXPECT_EQ(core::Vec2i::Dot(v2, p2), 0);

	const auto r1 = v1.Perpendicular2();
	const auto r2 = v2.Perpendicular2();
	EXPECT_EQ(core::Vec2i::Dot(v1, r1), 0);
	EXPECT_EQ(core::Vec2i::Dot(v2, r2), 0);
}

TEST_P(Vec2iOperationFixture, Lerp)
{
	auto [v1, t] = GetParam();
	const auto result = core::Vec2i::Lerp(v1, t.x);
	EXPECT_FLOAT_EQ(result, v1.x * (1 - t.x) + v1.y * t.x);
}

INSTANTIATE_TEST_SUITE_P(AllNumbers,
	Vec2iOperationFixture,
	testing::Values(
		std::pair{ core::Vec2i{1,3}, core::Vec2i{2,-4} },
		std::pair{ core::Vec2i{-10, 15}, core::Vec2i{-25, -35} },
		std::pair{ core::Vec2i{0, 0}, core::Vec2i{0, 0} },
		std::pair{ core::Vec2i{}, core::Vec2i{} },
		std::pair{ core::Vec2i{1, 2}, core::Vec2i{} },
		std::pair{ core::Vec2i{}, core::Vec2i{1, 2} }
	)
);
