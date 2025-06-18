#ifndef CORE_MATHS_ANGLE_H
#define CORE_MATHS_ANGLE_H

#include <type_traits>
#include "maths/const.h"

namespace core::maths {

	template<typename R>
	requires std::is_floating_point_v<R>
	class Degree; // Forward declaration

	template<typename R>
	requires std::is_floating_point_v<R>
	class Radian {
	public:
		constexpr explicit Radian(R value) : value_(value) {}

		template<typename D>
		requires std::is_floating_point_v<D>
		Radian(const Degree<D>& degree);

		explicit constexpr operator R() const { return value_; }

		R Value() const { return value_; }

	private:
		R value_;
	};

	template<typename D>
	requires std::is_floating_point_v<D>
	class Degree {
	public:
		constexpr explicit Degree(D value) : value_(value) {}

		template<typename R>
		requires std::is_floating_point_v<R>
		Degree(const Radian<R>& radian)
			: value_(static_cast<D>(radian.Value() * static_cast<D>(180.0) / Pi<D>)) {}

		explicit constexpr operator D() const { return value_; }

		D Value() const { return value_; }

	private:
		D value_;
	};

	template<typename R>
	requires std::is_floating_point_v<R>
	template<typename D>
	requires std::is_floating_point_v<D>
	Radian<R>::Radian(const Degree<D>& degree)
		: value_(static_cast<R>(degree.Value()) * Pi<R> / static_cast<R>(180.0)) {}

} // namespace core

#endif // CORE_MATHS_ANGLE_H
