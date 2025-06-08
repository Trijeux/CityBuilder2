#ifndef CORE_MATHS_VEC2F_H_
#define CORE_MATHS_VEC2F_H_

#include <complex>
#include <iostream>

#include "func.h"

namespace core::maths
{
	struct Vec2f
	{
		float x = 0, y = 0;

		[[nodiscard]] constexpr Vec2f operator+(const Vec2f other) const
		{
			return { x + other.x, y + other.y };
		}

		[[nodiscard]] constexpr Vec2f operator-(const Vec2f other) const
		{
			return { x - other.x, y - other.y };
		}

		[[nodiscard]] constexpr Vec2f operator-() const
		{
			return { -x, -y };
		}

		[[nodiscard]] constexpr float Dot(const Vec2f& other) const
		{
			return x * other.x + y * other.y;
		}

		[[nodiscard]] static constexpr float Dot(const Vec2f v1,const Vec2f v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		[[nodiscard]] constexpr Vec2f operator*(const float t) const
		{
			return { x * t,y * t };
		}

		friend constexpr Vec2f operator*(const float t, const Vec2f& vec) {
			return { t * vec.x, t * vec.y };
		}

		[[nodiscard]] constexpr Vec2f operator/(const float t) const
		{
			return { x / t,y / t };
		}


		[[nodiscard]] constexpr Vec2f Perpendicular() const
		{
			return { -y, x };
		}

		[[nodiscard]] constexpr Vec2f Perpendicular2() const
		{
			return { y, -x };
		}

		[[nodiscard]] static constexpr float Lerp(const Vec2f v1, const float t)
		{
			return v1.x * (1 - t) + v1.y * t;
		}

		[[nodiscard]] float MagnitudeSqu() const
		{
			return  x * x + y * y;
		}

		[[nodiscard]] float Magnitude() const
		{
			return std::sqrt(MagnitudeSqu());
		}

		[[nodiscard]] Vec2f Normalize() const
		{
			const float man = Magnitude();
			if (man == 0.0f)
			{
				return Vec2f(0, 0);
			}
			return *this / man;
		}

		[[nodiscard]] Vec2f Rotate(const Radian angle) const
		{
			const float c = Cos(angle);
			const float s = Sin(angle);
			const float new_x = c * x - s * y;
			const float new_y = s * x + c * y;
			return Vec2f(new_x, new_y);
		}

		[[nodiscard]] float AngleBetween(const Vec2f& other) const
		{
			return std::atan2(other.y, other.x) - std::atan2(y, x);
		}
	}; // struct Vec2i
} // namespace core





#endif  //CORE_MATHS_VEC2F_H_