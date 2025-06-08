#ifndef CORE_MATHS_VEC2_H
#define CORE_MATHS_VEC2_H

#include <cmath>
#include <concepts>

#include "angle.h"
#include "func.h"

namespace core::maths
{
	template<typename Vector2T, typename T>
	concept IsVector2 = requires(Vector2T v)
	{
		{v.x} -> std::same_as<T&>;
		{v.y} -> std::same_as<T&>;
	};


	template<typename Vector2T, typename T>
		concept IsConvertibleVector2 = requires(Vector2T v)
	{
		{v.x} -> std::convertible_to<T&>;
		{v.y} -> std::convertible_to<T&>;
	};

	template<typename T>
	requires std::is_arithmetic_v<T>
	struct Vec2
	{
		T x{}, y{};
		constexpr Vec2() = default;
		constexpr Vec2(T x, T y) : x(x), y(y) {}

		template <typename VectorT>
			requires IsVector2<VectorT, T>
		  constexpr explicit Vec2(VectorT v) : x(v.x), y(v.y) {}

		template <typename VectorT>
			requires IsConvertibleVector2<VectorT, T> && !IsVector2<VectorT, T>
		  constexpr explicit Vec2(VectorT v)
			  : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}

		[[nodiscard]] constexpr Vec2 operator+(const Vec2 other) const
		{
			return { x + other.x, y + other.y };
		}

		[[nodiscard]] constexpr Vec2 operator-(const Vec2 other) const
		{
			return { x - other.x, y - other.y };
		}

		[[nodiscard]] constexpr Vec2 operator-() const
		{
			return { -x, -y };
		}

		[[nodiscard]] constexpr Vec2 operator*(const Vec2& vec2) const
		{
			return { x * vec2.x, y * vec2.y };
		}

		[[nodiscard]] constexpr Vec2 operator*(const T t) const
		{
			return { x * t,y * t };
		}

		friend constexpr Vec2 operator*(const T t, const Vec2& vec) {
			return { t * vec.x, t * vec.y };
		}

		[[nodiscard]] constexpr T Dot(const Vec2& other) const
		{
			return x * other.x + y * other.y;
		}

		[[nodiscard]] static constexpr T Dot(const Vec2 v1,const Vec2 v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		[[nodiscard]] constexpr Vec2 operator/(const Vec2& vec2) const
		{
			return { x / vec2.x, y / vec2.y };
		}

		[[nodiscard]] constexpr Vec2 operator/(const T t) const
		{
			return { x / t,y / t };
		}

		[[nodiscard]] constexpr Vec2 Perpendicular() const
		{
			return { -y, x };
		}

		[[nodiscard]] constexpr Vec2 Perpendicular2() const
		{
			return { y, -x };
		}

		[[nodiscard]] static constexpr T Lerp(const Vec2 v1, const float t) requires std::is_floating_point_v<T>
		{
			return v1.x * (1 - t) + v1.y * t;
		}

		[[nodiscard]] T MagnitudeSqu() const requires std::is_floating_point_v<T>
		{
			return  x * x + y * y;
		}

		[[nodiscard]] T Magnitude() const requires std::is_floating_point_v<T>
		{
			return std::sqrt(MagnitudeSqu());
		}

		[[nodiscard]] Vec2 Normalize() const requires std::is_floating_point_v<T>
		{
			const float man = Magnitude();
			if (man == 0.0f)
			{
				return Vec2(0, 0);
			}
			return *this / man;
		}

		[[nodiscard]] Vec2 Rotate(const Radian angle) const requires std::is_floating_point_v<T>
		{
			const float c = Cos(angle);
			const float s = Sin(angle);
			const float new_x = c * x - s * y;
			const float new_y = s * x + c * y;
			return Vec2(new_x, new_y);
		}

		[[nodiscard]] T AngleBetween(const Vec2& other) const requires std::is_floating_point_v<T>
		{
			return Atan2(other.y, other.x) - Atan2(y, x);
		}
	};
}

#endif //CORE_MATHS_VEC2_H
