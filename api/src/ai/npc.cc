#include "ai/npc.h"

#include <general/resource_manager.h>
#include <graphics/resource_sprit.h>
#include <ai/bt_action.h>

#include "ai/bt_sequence.h"


core::ai::Status api::ai::Npc::Move()
{
	// if destination not reachable, return failure
	if(!target_reachable_)
	{
		//std::cout << "Not reachable" << target_reachable_ << std::endl;
		return core::ai::Status::kFailure;
	}
	else
	{
		//std::cout << "I'm moving (distance = " << target_distance_ << ")" << std::endl;
		if(target_distance_ >= 0.15f)
		{
			// still arriving, return running
			target_distance_ -= moving_speed_;
			return core::ai::Status::kRunning;
		}
		else
		{
			// if destination reached, return success
			return core::ai::Status::kSuccess;
		}
	}
}

core::ai::Status api::ai::Npc::Eat()
{
	// No failure, until we have food storage system
	hunger_ -= hunger_rate_;
	if(hunger_ > 0)
	{
		return core::ai::Status::kRunning;
	}
	else
	{
		return core::ai::Status::kSuccess;
	}
}

void api::ai::Npc::SetupBehaviourTree()
{
	std::unique_ptr<core::ai::Selector> selector;

	auto feedSequence = std::make_unique<core::ai::Sequence>();
	feedSequence->AddChild(std::make_unique<core::ai::Action>([this]()
	{
		if(hunger_ >= 100)
		{
			//std::cout << "I'm hungry, wanna eat........" << std::endl;
			return core::ai::Status::kSuccess;
		}
		else
		{
			//std::cout << "I'm not hungry, thanks........" << std::endl;
			return core::ai::Status::kFailure;
		}

	}));
	feedSequence->AddChild(std::make_unique<core::ai::Action>(std::bind(&Npc::Move, this)));
	feedSequence->AddChild(std::make_unique<core::ai::Action>(std::bind(&Npc::Eat, this)));


	selector = std::make_unique<core::ai::Selector>();
	// Attach the sequence to the selector
	selector->AddChild(std::move(feedSequence));
	// Work sequence
	selector->AddChild(std::make_unique<core::ai::Action>([this]()
	{
		hunger_ += hunger_rate_ * 5;
		if(resource_available_)
		{
			//std::cout << "Resource Available, working....." << std::endl;
			return core::ai::Status::kSuccess;
		}
		return core::ai::Status::kFailure;
	}));
	// Idle sequence
	selector->AddChild(std::make_unique<core::ai::Action>([this]()
	{
		hunger_ += hunger_rate_ * 5;
		//std::cout << "I'm sleeping" << std::endl;
		return core::ai::Status::kSuccess;
	}));

	root_ = std::move(selector);
}

void api::ai::Npc::Setup()
{
	sprite_ = sf::Sprite(api::general::resource_manager::texture(api::graphics::ResourceSprit::Texture::kBlue));

	SetupBehaviourTree();
	motor_.set_seed(50);
}

void api::ai::Npc::Update(const float dt)
{
	if(!points_.empty())
	{
		motor_.set_destination(points_[index_point_]);
	}

	root_->Tick();

	if(motor_.Update(dt))
	{
		is_moving_ = true;
		if(points_.size() - 1 > index_point_)
			index_point_++;
	}
	if(points_.size() - 1 <= index_point_)
	{
		index_point_ = 0;
		is_moving_ = false;
	}

	sprite_->setPosition(motor_.position());
}

void api::ai::Npc::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*sprite_, states);
}
