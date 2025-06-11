#ifndef CORE_AI_BT_NODE_H
#define CORE_AI_BT_NODE_H

namespace core::ai
{
	enum class Status
	{
		kFailure,
		kRunning,
		kSuccess
	};

	class Node
	{
	public:
		virtual void   Reset() = 0;
		virtual Status Tick() = 0;

	protected:
		Status status_ = Status::kFailure;
	};
}

#endif //CORE_AI_BT_NODE_H
