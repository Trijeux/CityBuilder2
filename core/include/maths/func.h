#ifndef CORE_MATHS_FUNC_H
#define CORE_MATHS_FUNC_H
#include <cmath>

#include "angle.h"

namespace core {
	inline float Cos(const Radian angle) {
		return std::cos(static_cast<float>(angle));
	}

	inline float Sin(const Radian angle) {
		return std::sin(static_cast<float>(angle));
	}

	inline float Tan(const Radian angle) {
		return std::tan(static_cast<float>(angle));
	}

}

#endif //CORE_MATHS_FUNC_H