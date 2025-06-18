#ifndef CORE_MATHS_FUNC_H
#define CORE_MATHS_FUNC_H

#include "angle.h"

#include <iostream>

namespace core::maths
{
	template<typename T>
	requires std::is_floating_point_v<T>
	T Cos(const Radian<T> angle)
	{
		T val = 1;
		T somme = 0;
		for(int n = 1; n < 20; n++)
		{
			somme += val;
			val *= -(angle.Value() * angle.Value()) / (2 * n * (2 * n - 1));
		}
		return somme;
	}

	template<typename T>
	requires std::is_floating_point_v<T>
	T Sin(const Radian<T>& angle)
	{
		T val = angle.Value();
		T somme = 0;
		for(int n = 1; n < 20; n++)
		{
			somme += val;
			val *= -(angle.Value() * angle.Value()) / (2 * n * (2 * n + 1));
		}
		return somme;
	}

	template<typename T>
	requires std::is_floating_point_v<T>
	T Tan(const Radian<T> angle)
	{
		return Sin(angle) / Cos(angle);
	}

	template<typename T>
	requires std::is_floating_point_v<T>
	T Sec(const Radian<T> angle)
	{

		const T cos = Cos(angle);

		if(constexpr T epsilon = 1e-10; std::abs(cos) < epsilon)
		{
			std::cerr << "Erreur : cos(x) est trop proche de zéro. Sécante indéfinie." << std::endl;
			return std::numeric_limits<float>::quiet_NaN(); // Retourne NaN
		}

		return 1.0f / cos;
	}

	template<typename T>
	requires std::is_floating_point_v<T>
	T Pow(T base, T exponent)
	{
		T result = 1;
		for(int i = 0; i < exponent; i++)
		{
			result *= base;
		}
		return result;
	}

	template<typename T>
	requires std::is_floating_point_v<T>
	Radian<T> ASin(const T value)
	{
		T val = value;
		T somme = 0;
		for(int n = 1; n < 100000; n++)
		{
			somme += val;
			val *= (2* n - 1) * (2 * n - 1) * (value * value) / (2 * n * (2 * n + 1));
		}
		return Radian<T>(somme);
	}

	template<typename T>
	requires std::is_floating_point_v<T>
	Radian<T> Acos(const T value)
	{
		return Radian<T>(Pi<T> / 2 - ASin(value).Value());
	}

	template<typename T>
	requires std::is_floating_point_v<T>
	Radian<T> Atan(const T x)
	{
		if (std::abs(x) > 1.0f)
		{
			return Radian<T>((x > 0 ? Pi<T> / 2 : -Pi<T> / 2) - Atan(1 / x).Value());
		}

		T result = 0.0f;
		for (int n = 0; n < 20; ++n)
		{
			T term = Pow<T>(-1.f, n) * Pow<T>(x, 2 * n + 1) / (2 * n + 1);
			result += term;
		}
		return Radian<T>(result);
	}

	template<typename T>
	requires std::is_floating_point_v<T>
	Radian<T> Atan2(const T y, const T x)
	{
		if (x > 0) return Radian<T>(Atan(y / x).Value());
		if (x < 0 && y >= 0) return Radian<T>(Atan(y / x).Value() + Pi<T>);
		if (x < 0 && y < 0) return Radian<T>(Atan(y / x).Value() - Pi<T>);
		if (x == 0 && y > 0) return Radian<T>(Pi<T> / 2);
		if (x == 0 && y < 0) return Radian<T>(-Pi<T> / 2);
		return Radian<T>(0.0f);
	}
}

#endif //CORE_MATHS_FUNC_H