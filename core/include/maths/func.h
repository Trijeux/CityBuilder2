#ifndef CORE_MATHS_FUNC_H
#define CORE_MATHS_FUNC_H

#include "angle.h"

#include <iostream>

namespace core
{
	inline float Cos(const Radian angle)
	{
		float val = 1;
		float somme = 0;
		for(int n = 1; n < 20; n++)
		{
			somme += val;
			val *= -(angle.Value() * angle.Value()) / (2 * n * (2 * n - 1));
		}
		return somme;
	}

	inline float Sin(const Radian angle)
	{
		float val = angle.Value();
		float somme = 0;
		for(int n = 1; n < 20; n++)
		{
			somme += val;
			val *= -(angle.Value() * angle.Value()) / (2 * n * (2 * n + 1));
		}
		return somme;
	}

	inline float Tan(const Radian angle)
	{
		return Sin(angle) / Cos(angle);
	}

	inline float Sec(const Radian angle)
	{

		const float cos = Cos(angle);

		if(constexpr float epsilon = 1e-10; std::abs(cos) < epsilon)
		{
			std::cerr << "Erreur : cos(x) est trop proche de zéro. Sécante indéfinie." << std::endl;
			return std::numeric_limits<float>::quiet_NaN(); // Retourne NaN
		}

		return 1.0f / cos;
	}

	inline float Pow(const float base, const float exponent)
	{
		float result = 1;
		for(int i = 0; i < exponent; i++)
		{
			result *= base;
		}
		return result;
	}

	inline float ASin(const float value)
	{
		float val = value;
		float somme = 0;
		for(int n = 1; n < 100000; n++)
		{
			somme += val;
			val *= (2* n - 1) * (2 * n - 1) * (value * value) / (2 * n * (2 * n + 1));
		}
		return somme;
	}

	inline float Acos(const float value)
	{
		return Pi / 2 - ASin(value);
	}

	inline float Atan(const float x)
	{
		if (std::abs(x) > 1.0f)
		{
			return (x > 0 ? Pi / 2 : -Pi / 2) - Atan(1 / x);
		}

		float result = 0.0f;
		for (int n = 0; n < 20; ++n)
		{
			float term = Pow(-1.f, n) * Pow(x, 2 * n + 1) / (2 * n + 1);
			result += term;
		}
		return result;
	}

	inline float Atan2(const float y, const float x)
	{
		if (x > 0) return Atan(y / x);
		if (x < 0 && y >= 0) return Atan(y / x) + Pi;
		if (x < 0 && y < 0) return Atan(y / x) - Pi;
		if (x == 0 && y > 0) return Pi / 2;
		if (x == 0 && y < 0) return -Pi / 2;
		return 0.0f;
	}
}

#endif //CORE_MATHS_FUNC_H