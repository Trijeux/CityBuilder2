#include "maths/vec2.h"

#include <gtest/gtest.h>
#include <SFML/System/Vector2.hpp>

using namespace core::maths;

TEST(Vec2, Constructor)
{
	constexpr Vec2I vec(1, 2);
	EXPECT_EQ(vec.x, 1);
	EXPECT_EQ(vec.y, 2);
	constexpr Vec2F vec_f(1.5f, 2.5f);
	EXPECT_EQ(vec_f.x, 1.5f);
	EXPECT_EQ(vec_f.y, 2.5f);
	constexpr Vec2D vec_d(1.5f, 2.5f);
	EXPECT_EQ(vec_d.x, 1.5);
	EXPECT_EQ(vec_d.y, 2.5);
	constexpr sf::Vector2f  vec_sfml_1(1.5f, 2.5f);
	constexpr Vec2F vec_sfml_2 {vec_sfml_1};
	EXPECT_EQ(vec_sfml_2.x, 1.5);
	EXPECT_EQ(vec_sfml_2.y, 2.5);
}

TEST(Vec2, add)
{
	constexpr Vec2I vec1(1, 2);
	constexpr Vec2I vec2(3, 4);
	constexpr Vec2I vec3 = vec1 + vec2;
	EXPECT_EQ(vec3.x, 4);
	EXPECT_EQ(vec3.y, 6);
	constexpr Vec2F vec_f1(1.2f, 2.2f);
	constexpr Vec2F vec_f2(3.3f, 4.3f);
	constexpr Vec2F vec_f3 = vec_f1 + vec_f2;
	EXPECT_NEAR(vec_f3.x, 4.5f, 0.0001f);
	EXPECT_NEAR(vec_f3.y,  6.5f, 0.0001f);
}

TEST(Vec2, Sub)
{
	constexpr Vec2I vec1(3, 4);
	constexpr Vec2I vec2(1, 2);
	constexpr Vec2I vec3 = vec1 - vec2;
	EXPECT_EQ(vec3.x, 2);
	EXPECT_EQ(vec3.y, 2);

	constexpr Vec2F vec_f1(3.3f, 4.3f);
	constexpr Vec2F vec_f2(1.2f, 2.2f);
	constexpr Vec2F vec_f3 = vec_f1 - vec_f2;
	EXPECT_NEAR(vec_f3.x, 2.1f, 0.0001f);
	EXPECT_NEAR(vec_f3.y, 2.1f, 0.0001f);
}

TEST(Vec2, Muli)
{
	constexpr Vec2I vec1(3, 4);

	constexpr auto result_int = vec1 * 2;
	EXPECT_EQ(result_int.x, 3*2);
	EXPECT_EQ(result_int.y, 4*2);

	constexpr Vec2I vec2(1, 2);
	constexpr Vec2I vec3 = vec1 * vec2;
	EXPECT_EQ(vec3.x, 3);
	EXPECT_EQ(vec3.y, 8);
	constexpr Vec2F vec_f1(3.3f, 4.3f);

	constexpr auto result_float = vec_f1 * 2;
	EXPECT_EQ(result_float.x, 3.3f*2);
	EXPECT_EQ(result_float.y, 4.3f*2);

	constexpr Vec2F vec_f2(1.2f, 2.2f);
	constexpr Vec2F vec_f3 = vec_f1 * vec_f2;
	EXPECT_EQ(vec_f3.x, 3.3f * 1.2f);
	EXPECT_EQ(vec_f3.y, 4.3f * 2.2f);
}

TEST(Vec2, Dot)
{
	constexpr Vec2I vec1(3, 4);
	constexpr Vec2I vec2(1, 2);
	EXPECT_EQ(Vec2I::Dot(vec1, vec2), 3 * 1 + 4 * 2);


	constexpr Vec2F vec_f1(3.3f, 4.3f);
	constexpr Vec2F vec_f2(1.2f, 2.2f);
	EXPECT_EQ(Vec2F::Dot(vec_f1, vec_f2), 3.3f * 1.2f + 4.3f * 2.2f);
}

TEST(Vec2, Div)
{
	constexpr Vec2I vec1(3, 4);

	constexpr auto result_int = vec1 / 2;
	EXPECT_EQ(result_int.x, 3/2);
	EXPECT_EQ(result_int.y, 4/2);

	constexpr Vec2I vec2(1, 2);
	constexpr Vec2I vec3 = vec1 / vec2;
	EXPECT_EQ(vec3.x, 3/1);
	EXPECT_EQ(vec3.y, 4/2);

	constexpr Vec2F vec_f1(3.3f, 4.3f);

	constexpr auto result_float = vec_f1 / 2;
	EXPECT_EQ(result_float.x, 3.3f/2);
	EXPECT_EQ(result_float.y, 4.3f/2);

	constexpr Vec2F vec_f2(1.2f, 2.2f);
	constexpr Vec2F vec_f3 = vec_f1 - vec_f2;
	EXPECT_NEAR(vec_f3.x, 2.1f, 0.0001f);
	EXPECT_NEAR(vec_f3.y, 2.1f, 0.0001f);
}

TEST(Vec2, Perpendicular)
{
	constexpr Vec2I vec_1(3, 4);
	constexpr auto result_int1 = vec_1.Perpendicular();
	EXPECT_EQ(result_int1.x, -vec_1.y);
	EXPECT_EQ(result_int1.y, vec_1.x);
	constexpr auto result_int2 = vec_1.Perpendicular2();
	EXPECT_EQ(result_int2.x, vec_1.y);
	EXPECT_EQ(result_int2.y, -vec_1.x);

	constexpr Vec2F vec_f1(3.3f, 4.3f);
	constexpr auto result_float1 = vec_f1.Perpendicular();
	EXPECT_EQ(result_float1.x, -vec_f1.y);
	EXPECT_EQ(result_float1.y, vec_f1.x);
	constexpr auto result_float2 = vec_f1.Perpendicular2();
	EXPECT_EQ(result_float2.x, vec_f1.y);
	EXPECT_EQ(result_float2.y, -vec_f1.x);
}

TEST(Vec2, Lerp)
{
	constexpr Vec2F vec_1(3.3f, 4.3f);
	constexpr auto result_float = Vec2F::Lerp(vec_1, 0.5f);
	EXPECT_EQ(result_float, vec_1.x * (1 - 0.5f) + vec_1.y * 0.5f);
	EXPECT_EQ(result_float, vec_1.x * (1 - 0.5f) + vec_1.y * 0.5f);
}

TEST(Vec2, MagnitudeSqu)
{
	constexpr Vec2F vec_1(3.3f, 4.3f);
	const auto result_float = vec_1.MagnitudeSqr();
	EXPECT_EQ(result_float, vec_1.x * vec_1.x + vec_1.y * vec_1.y);
}

TEST(Vec2, Magnitude)
{
	constexpr Vec2F vec_1(3.3f, 4.3f);
	const auto result_float = vec_1.Magnitude();
	EXPECT_EQ(result_float, std::sqrt(vec_1.MagnitudeSqr()));
}

TEST(Vec2, Normalize)
{
	constexpr Vec2F vec_1(3.3f, 4.3f);
	const auto result_float = vec_1.Normalize();

	const float result_test = vec_1.Magnitude();
	Vec2F vec_1_test(0, 0);
	if (result_test != 0.0f)
	{
		vec_1_test = vec_1 / result_test;
	}

	EXPECT_EQ(result_float.x, vec_1_test.x);
	EXPECT_EQ(result_float.y, vec_1_test.y);
}

TEST(Vec2, Rotate)
{
	constexpr Vec2F vec_1(3.3f, 4.3f);
	const auto result_float = vec_1.Rotate(Radian<float>(Degree<float>(90)));

	const auto c = Cos<float>(Radian<float>(Degree<float>(90)));
	const auto s = Sin<float>(Radian<float>(Degree<float>(90)));
	const float new_x = c * vec_1.x - s * vec_1.y;
	const float new_y = s * vec_1.x + c * vec_1.y;
	const Vec2F result_test(new_x, new_y);

	EXPECT_EQ(result_float.x, result_test.x);
	EXPECT_EQ(result_float.y, result_test.y);
}

TEST(Vec2, AngleBetweena)
{
	constexpr Vec2F vec_1(3.3f, 4.3f);
	constexpr Vec2F vec_2(3.2f, 4.2f);
	const auto result_float = vec_1.AngleBetween<float>(vec_2);

	const auto result_test = Atan2<float>(vec_2.y, vec_2.x).Value() - Atan2<float>(vec_1.y, vec_1.x).Value();

	EXPECT_EQ(result_float.Value(), result_test);
}