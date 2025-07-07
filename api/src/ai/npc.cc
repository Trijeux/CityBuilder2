#include "ai/npc.h"

#include <iostream>
#include <random>
#include <general/resource_manager.h>
#include <graphics/resource_sprit.h>
#include <ai/bt_action.h>

#include "ai/bt_sequence.h"

// core::ai::Status api::ai::Npc::Move()
// {
// 	// if destination not reachable, return failure
// 	if(!target_reachable_)
// 	{
// 		std::cout << "Not reachable" << target_reachable_ << std::endl;
// 		return core::ai::Status::kFailure;
// 	}
// 	else
// 	{
// 		std::cout << "I'm moving (distance = " << target_distance_ << ")" << std::endl;
// 		if(target_distance_ >= 0.15f)
// 		{
// 			// still arriving, return running
// 			//objectif = work_.position();
// 			objectif_ = sf::Vector2f(0, 0);
// 			target_distance_ -= moving_speed_;
// 			return core::ai::Status::kRunning;
// 		}
// 		else
// 		{
// 			objectif() = sprite_->getPosition();
// 			// if destination reached, return success
// 			return core::ai::Status::kSuccess;
// 		}
// 	}
// }

// core::ai::Status api::ai::Npc::Eat()
// {
// 	// No failure, until we have food storage system
// 	if(home_.position() == sprite_->getPosition())
// 	{
// 		hunger_ -= hunger_rate_;
// 		objectif_ = sprite_->getPosition();
// 	}
// 	else
// 	{
// 		objectif_ = home_.position();
// 	}
// 	if(hunger_ > 0)
// 	{
// 		return core::ai::Status::kRunning;
// 	}
// 	else
// 	{
// 		return core::ai::Status::kSuccess;
// 	}
// }

// void api::ai::Npc::SetupBehaviourTree()
// {
// 	std::unique_ptr<core::ai::Selector> selector;
//
// 	auto feedSequence = std::make_unique<core::ai::Sequence>();
// 	feedSequence->AddChild(std::make_unique<core::ai::Action>([this]()
// 	{
// 		if(hunger_ >= 100)
// 		{
// 			std::cout << "I'm hungry, wanna eat........" << std::endl;
// 			return core::ai::Status::kSuccess;
// 		}
// 		else
// 		{
// 			std::cout << "I'm not hungry, thanks........" << std::endl;
// 			return core::ai::Status::kFailure;
// 		}
//
// 	}));
//
// 	feedSequence->AddChild(std::make_unique<core::ai::Action>(std::bind(&Npc::Move, this)));
// 	feedSequence->AddChild(std::make_unique<core::ai::Action>(std::bind(&Npc::Eat, this)));
//
//
// 	selector = std::make_unique<core::ai::Selector>();
// 	// Attach the sequence to the selector
// 	selector->AddChild(std::move(feedSequence));
// 	// Work sequence
// 	selector->AddChild(std::make_unique<core::ai::Action>([this]()
// 	{
// 		hunger_ -= hunger_rate_ * 5;
// 		if(resource_available_)
// 		{
// 			std::cout << "Resource Available, working....." << std::endl;
// 			return core::ai::Status::kSuccess;
// 		}
// 		return core::ai::Status::kFailure;
// 	}));
// 	// Idle sequence
// 	selector->AddChild(std::make_unique<core::ai::Action>([this]()
// 	{
// 		hunger_ += hunger_rate_ * 5;
// 		std::cout << "I'm sleeping" << std::endl;
// 		return core::ai::Status::kSuccess;
// 	}));
//
// 	root_ = std::move(selector);
// }

void api::ai::Npc::Setup(gameplay::Building building)
{
	home_ = building;
	sprite_ = sf::Sprite(api::general::resource_manager::texture(api::graphics::ResourceSprit::Texture::kBlue));
	sprite_->setPosition(home_->position());
	SetupBehaviourTree();
	motor_.set_speed(25);
	motor_.set_position(sprite_->getPosition());
	motor_.set_destination(sprite_->getPosition());
}

core::ai::Status api::ai::Npc::CheckEat()
{
	// std::cout << "this ? = " << this << "\n";
	//std::cout << "Am I hungry ? " << std::to_string(hunger_) << std::endl;
	if(hunger_ >= 100 && home_->position() != sprite_->getPosition())
	{
		new_path_ = true;
		is_moving_ = true;
		objectif_ = home_->position();
	}

	return core::ai::Status::kSuccess;

}

core::ai::Status api::ai::Npc::CheckWork()
{
	// std::cout << "this ? = " << this << "\n";
	//std::cout << "Am I hungry ? " << std::to_string(hunger_) << std::endl;
	// std::cout << " : No, I can wait\n";
	if(have_work_ && hunger_ <= 0 && work_->position() != sprite_->getPosition())
	{
		new_path_ = true;
		is_moving_ = true;
		objectif_ = work_->position();
	}
		return core::ai::Status::kSuccess;
}

core::ai::Status api::ai::Npc::Move()
{
	// if destination not reachable, return failure
	if(!path_.is_valid())
	{
		// std::cout << "Not reachable" << path_->IsValid() << "\n";
		return core::ai::Status::kFailure;
	}
	else
	{
		//std::cout << "I'm moving" << "\n";
		if(!path_.IsDone())
		{
			// still arriving, return running
			if(motor_.remaining_distance() <= 0.001f)
			{
				motor_.set_destination(path_.GetNextPoint());
			}
			return core::ai::Status::kRunning;
		}
		else
		{
			// if destination reached, return success
			is_moving_ = false;
			return core::ai::Status::kSuccess;
		}
	}
}

core::ai::Status api::ai::Npc::Eat(float foodQty)
{
	// No failure, until we have food storage system
	if(!is_moving_ && sprite_->getPosition() == home_->position())
	{
		std::cout << "I'm Eat" << hunger_ << "\n";
		hunger_ -= foodQty;
		if(hunger_ <= 0)
		{
			hunger_ = 0;
			return core::ai::Status::kFailure;
		}
		return core::ai::Status::kRunning;
	}
	if(hunger_ >= 100)
	{
		return core::ai::Status::kSuccess;
	}
	//std::cout << "I'm eating " << hunger_ << "\n";
	return core::ai::Status::kFailure;

}

core::ai::Status api::ai::Npc::Work()
{
	if(have_work_)
	{
		if(!is_moving_ && sprite_->getPosition() == work_->position())
		{
			hunger_ += hunger_rate_ * 2;
			std::cout << "I'm working" << hunger_ << "\n";

			if(resource_available_)
			{
				//std::cout << "Resource Available, working....." << "\n";
				return core::ai::Status::kSuccess;
			}
		}
	}
	return core::ai::Status::kFailure;
}

core::ai::Status api::ai::Npc::Idle()
{
	//hunger_ += hunger_rate_;
	//std::cout << "I'm sleeping" << "\n";
	return core::ai::Status::kSuccess;
}

void api::ai::Npc::SetupBehaviourTree()
{
	//std::cout << "Setup Behaviour Tree\n";

	hunger_ = 0;

	sf::Vector2f start = {0, 0};

	auto feedSequence = std::make_unique<core::ai::Sequence>();
	feedSequence->AddChild(std::make_unique<core::ai::Action>([this]()
	{
		return CheckEat();
	}));
	feedSequence->AddChild(std::make_unique<core::ai::Action>([this]()
	{
		return Move();
	}));
	feedSequence->AddChild(std::make_unique<core::ai::Action>([this]()
	{
		return Eat(hunger_rate_);
	}));

	auto workSequence = std::make_unique<core::ai::Sequence>();
	workSequence->AddChild(std::make_unique<core::ai::Action>([this]()
	{
		return CheckWork();
	}));
	workSequence->AddChild(std::make_unique<core::ai::Action>([this]()
	{
		return Move();
	}));
	workSequence->AddChild(std::make_unique<core::ai::Action>([this]()
	{
		return Work();
	}));

	auto selector = std::make_unique<core::ai::Selector>();
	// Attach the sequence to the selector
	selector->AddChild(std::move(feedSequence));
	selector->AddChild(std::move(workSequence));
	selector->AddChild(std::make_unique<core::ai::Action>([this]()
	{
		return Idle();
	}));

	root_ = std::move(selector);
}

void api::ai::Npc::Update(float dt)
{
	root_->Tick();
	if(path_.is_valid())
	{
		motor_.Update(dt);
		sprite_->setPosition(motor_.position());
	}
	// std::cout << "this ? = " << this << "\n";
}

void api::ai::Npc::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*sprite_, states);
}