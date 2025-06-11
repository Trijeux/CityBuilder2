#ifndef CORE_AI_BT_SELECTOR_H
#define CORE_AI_BT_SELECTOR_H

#include <memory>
#include <vector>

#include "bt_node.h"

namespace core::ai
{
	class Selector : public Node
	{
		std::vector<std::unique_ptr<Node>> children_;
		int                                childIdx_ = 0;

	public:
		void   Reset() override;
		Status Tick() override;

		void AddChild(std::unique_ptr<Node> child);
	};
}

#endif //CORE_AI_BT_SELECTOR_H
