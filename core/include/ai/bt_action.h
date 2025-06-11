#ifndef CORE_AI_BT_ACTION_H
#define CORE_AI_BT_ACTION_H

#include <functional>
#include <utility>

#include "bt_node.h"

namespace core::ai
{
	//template<typename Callable>
	class Action : public Node
	{
	private:
		std::function<Status()> action_;

	public:
		explicit Action(std::function<Status()> action) : action_(std::move(action))
		{
		}

		void Reset() override
		{
		};

		Status Tick() override
		{
			// Faire des trucs ---------------
			return action_();
		}
	};
}


#endif //CORE_AI_BT_ACTION_H
