#include "ai/npc.h"

#include <iostream>
#include <general/resource_manager.h>
#include <graphics/resource_sprit.h>
#include <ai/bt_action.h>


core::ai::Status Npc::Move()
{
	std::cout << "I'm moving 2" << std::endl;
	return core::ai::Status::kRunning;
}

void Npc::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*sprite_, states);
}

void Npc::Setup()
{

	sprite_ = sf::Sprite(api::general::resource_manager::Sprit(api::graphics::ResourceSprit::Texture::kBlue));

	auto selector = std::make_unique<core::ai::Selector>();
	selector->AddChild(std::make_unique<core::ai::Action>([this]()
	{
		if(hunger_ >= 100)
		{
			std::cout << "I'm hungry, eating........" << std::endl;
			hunger_ = 0;
			return core::ai::Status::kSuccess;
		}
		return core::ai::Status::kFailure;
	}));
	selector->AddChild(std::make_unique<core::ai::Action>([this]()
	{
		if(resource_available_)
		{
			std::cout << "Resource Available, working....." << std::endl;
			return core::ai::Status::kSuccess;
		}
		return core::ai::Status::kFailure;
	}));
	selector->AddChild(std::make_unique<core::ai::Action>([this]()
	{
		std::cout << "I'm sleeping" << std::endl;
		return core::ai::Status::kSuccess;
	}));


	root_ = std::move(selector);
}

void Npc::Update()
{
	hunger_++;
	std::cout << "Hunger : " << hunger_ << std::endl;
	root_->Tick();
}
