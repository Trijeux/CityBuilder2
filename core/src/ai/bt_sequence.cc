#include "ai/bt_sequence.h"

core::ai::Status core::ai::Sequence::Tick(){

	while (childIdx_ < children_.size()) {
		const Status status = children_[childIdx_]->Tick();

		if (status == Status::kFailure) {
			Reset();
			return Status::kFailure;
		}

		if (status == Status::kRunning) {
			return Status::kRunning;
		}

		childIdx_++;
	}

	Reset();
	return Status::kSuccess;

}