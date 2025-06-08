#ifndef CORE_MATHS_ANGLE_H
#define CORE_MATHS_ANGLE_H

#include "maths/const.h"

namespace core {
	class Degree;
	class Radian {
	public:
		constexpr explicit Radian(const float value): value_(value){}
		constexpr Radian(const Degree& degree);

		explicit constexpr operator float() const { return value_; }

		float Value() const { return value_; }

	private:
		float value_;
	};

	class Degree {
	public:
		constexpr explicit Degree(const float value): value_(value){}
		constexpr Degree(const Radian& radian): value_(static_cast<float>(radian) * 180.0f / Pi) {}

		explicit constexpr operator float() const { return value_; }

		float Value() const { return value_; }

	private:
		float value_;
	};


	constexpr Radian::Radian(const Degree& degree)
		: value_(static_cast<float>(degree) * Pi / 180.0f) {}
}
#endif //CORE_MATHS_ANGLE_H