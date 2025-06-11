#include "ai/bt_selector.h"

core::ai::Status core::ai::Selector::Tick(){

    while (childIdx_ < children_.size()) {
        Status status = children_[childIdx_]->Tick();

        if (status == Status::kSuccess) {
            Reset();
            return Status::kSuccess;
        }

        if (status == Status::kRunning) {
            return Status::kRunning;
        }
        childIdx_++;
    }

    return Status::kFailure;

}