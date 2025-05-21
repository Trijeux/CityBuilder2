#ifndef CORE_MATHS_VEC2I_H_
#define CORE_MATHS_VEC2I_H_
#include <complex>

namespace core::maths
{
	struct Vec2i
	{
		int x = 0, y = 0;

		constexpr Vec2i operator+(const Vec2i other) const
		{
			return { x + other.x, y + other.y };
		}

		constexpr Vec2i operator-(const Vec2i other) const
		{
			return { x - other.x, y - other.y };
		}

		constexpr Vec2i operator-() const
		{
			return { -x, -y };
		}
		static constexpr int Dot(const Vec2i v1, const Vec2i v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		constexpr Vec2i operator*(const int t) const
		{
			return { x * t,y * t };
		}

		friend constexpr Vec2i operator*(const int t, const Vec2i& vec) {
			return { t * vec.x, t * vec.y };
		}

		constexpr Vec2i operator/(const int t) const
		{
			return { x / t,y / t };
		}

		[[nodiscard]] constexpr Vec2i Perpendicular() const
		{
			return { -y, x };
		}
		[[nodiscard]] constexpr Vec2i Perpendicular2() const
		{
			return { y, -x };
		}
		static int Lerp(const Vec2i v1, const int t)
		{
			return v1.x * (1 - t) + v1.y * t;
		}

	}; // struct Vec2i

} // namespace core


#endif  //CORE_MATHS_VEC2I_H_