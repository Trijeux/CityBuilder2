#include "ai/bt_composite.h"

void core::ai::Composite::Reset(){
	childIdx_ = 0;
}

void core::ai::Composite::AddChild(std::unique_ptr<Node> child){
	children_.push_back(std::move(child));
}