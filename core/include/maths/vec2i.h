#ifndef CORE_MATHS_VEC2I_H_
#define CORE_MATHS_VEC2I_H_
#include <complex>

namespace core
{
	/**
	 * \brief Vec2i is a mathematical object represented
	 */

	 //Add constructor template

	struct Vec2i
	{
		int x = 0, y = 0;

		constexpr Vec2i operator+(Vec2i other) const
		{
			return { x + other.x, y + other.y };
		}

		constexpr Vec2i operator-(Vec2i other) const
		{
			return { x - other.x, y - other.y };
		}

		constexpr Vec2i operator-() const
		{
			return { -x, -y };
		}
		static constexpr int Dot(Vec2i v1, Vec2i v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		constexpr Vec2i operator*(int t)
		{
			return { x * t,y * t };
		}

		friend constexpr Vec2i operator*(int t, const Vec2i& vec) {
			return { t * vec.x, t * vec.y };
		}

		constexpr Vec2i operator/(int t)
		{
			return { x / t,y / t };
		}

		constexpr Vec2i Perpendicular() const
		{
			return { -y, x };
		}
		constexpr Vec2i Perpendicular2() const
		{
			return { y, -x };
		}
		static int Lerp(Vec2i v1, int t)
		{
			return v1.x * (1 - t) + v1.y * t;
		}

	}; // struct Vec2i

	//Other Solve
	//Operator overload for multiplication
	/*constexpr Vec2i operator*(int scalar, const Vec2i& vec)
	{
		return { scalar * vec.x, scalar * vec.y };
	}*/

} // namespace core





#endif  //CORE_MATHS_VEC2I.H_