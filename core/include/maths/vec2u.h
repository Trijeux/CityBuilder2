#ifndef CORE_MATHS_VEC2U_H
#define CORE_MATHS_VEC2U_H

namespace core::maths
{
	struct Vec2u
	{
		unsigned int  x = 0, y = 0;

		constexpr Vec2u operator+(const Vec2u other) const
		{
			return { x + other.x, y + other.y };
		}

		constexpr Vec2u operator-(const Vec2u other) const
		{
			return { x - other.x, y - other.y };
		}

		constexpr Vec2u operator-() const
		{
			return { -x, -y };
		}
		static constexpr unsigned int Dot(const Vec2u v1, const Vec2u v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		constexpr Vec2u operator*(const unsigned int t) const
		{
			return { x * t,y * t };
		}

		friend constexpr Vec2u operator*(const unsigned int t, const Vec2u& vec) {
			return { t * vec.x, t * vec.y };
		}

		constexpr Vec2u operator/(const unsigned int t) const
		{
			return { x / t,y / t };
		}

		[[nodiscard]] constexpr Vec2u Perpendicular() const
		{
			return { -y, x };
		}
		[[nodiscard]] constexpr Vec2u Perpendicular2() const
		{
			return { y, -x };
		}
		static unsigned int Lerp(const Vec2u v1, const unsigned int t)
		{
			return v1.x * (1 - t) + v1.y * t;
		}
	}; // struct Vec2u

} // namespace core

#endif //CORE_MATHS_VEC2U_H
