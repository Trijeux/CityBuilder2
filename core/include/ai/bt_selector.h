#ifndef CORE_AI_BT_SELECTOR_H
#define CORE_AI_BT_SELECTOR_H

#include <memory>
#include <vector>

#include "bt_composite.h"
#include "bt_node.h"

namespace core::ai
{
	class Selector : public Composite
	{
	public:
		Status Tick() override;
	};
}

#endif //CORE_AI_BT_SELECTOR_H
