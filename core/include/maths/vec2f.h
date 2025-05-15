#ifndef CORE_MATHS_VEC2F_H_
#define CORE_MATHS_VEC2F_H_
#include <complex>
#include <iostream>

namespace core
{
	/**
	 * \brief Vec2f is a mathematical object represented
	 */

	 //Add constructor template

	struct Vec2f
	{
		float x = 0, y = 0;

		constexpr Vec2f operator+(Vec2f other) const
		{
			return { x + other.x, y + other.y };
		}

		constexpr Vec2f operator-(Vec2f other) const
		{
			return { x - other.x, y - other.y };
		}

		constexpr Vec2f operator-() const
		{
			return { -x, -y };
		}
		static constexpr float Dot(Vec2f v1, Vec2f v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		constexpr Vec2f operator*(float t) const
		{
			return { x * t,y * t };
		}

		friend constexpr Vec2f operator*(float t, const Vec2f& vec) {
			return { t * vec.x, t * vec.y };
		}

		constexpr Vec2f operator/(float t) const
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
		static constexpr float Lerp(Vec2f v1, float t)
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

		Vec2f Normalize() const
		{
			const float man = Magnitude();
			if (man == 0.0f)
			{
				return Vec2f(0, 0);
			}
			return *this / man;
		}

	}; // struct Vec2i

	//Other Solve
	//Operator overload for multiplication
	/*constexpr Vec2f operator*(float scalar, const Vec2f& vec)
	{
		return { scalar * vec.x, scalar * vec.y };
	}*/

} // namespace core





#endif  //CORE_MATHS_VEC2F.H_