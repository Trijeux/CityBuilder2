#ifndef CORE_MATHS_CONST_H
#define CORE_MATHS_CONST_H
#include <numbers>

namespace core::maths
{
	template <typename R>
		requires std::is_floating_point_v<R>
	static constexpr R Pi = std::numbers::pi_v<R>;
}
#endif //CORE_MATHS_CONST_H
