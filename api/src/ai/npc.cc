#include "ai/npc.h"

#include <iostream>
#include <general/resource_manager.h>
#include <graphics/resource_sprit.h>
#include <ai/bt_action.h>


Status Npc::Move()
{
	std::cout << "I'm moving 2" << std::endl;
	return Status::kRunning;
}

void Npc::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*sprite_, states);
}

void Npc::Setup()
{

	sprite_ = sf::Sprite(api::general::resource_manager::Sprit(api::graphics::ResourceSprit::Texture::kBlue));

	auto selector = std::make_unique<Selector>();
	selector->AddChild(std::make_unique<Action>([this]()
	{
		if(hunger_ >= 100)
		{
			std::cout << "I'm hungry, eating........" << std::endl;
			hunger_ = 0;
			return Status::kSuccess;
		}
		return Status::kFailure;
	}));
	selector->AddChild(std::make_unique<Action>([this]()
	{
		if(resource_available_)
		{
			std::cout << "Resource Available, working....." << std::endl;
			return Status::kSuccess;
		}
		return Status::kFailure;
	}));
	selector->AddChild(std::make_unique<Action>([this]()
	{
		std::cout << "I'm sleeping" << std::endl;
		return Status::kSuccess;
	}));


	root_ = std::move(selector);
}

void Npc::Update()
{
	hunger_++;
	std::cout << "Hunger : " << hunger_ << std::endl;
	root_->Tick();
}
