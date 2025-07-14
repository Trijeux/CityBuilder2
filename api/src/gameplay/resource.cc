#include "gameplay/resource.h"

#include <iostream>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "general/resource_manager.h"

void Resource::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*sprite_wood_, states);
	target.draw(*sprite_stone_, states);
	target.draw(*text_wood_, states);
	target.draw(*text_stone_, states);
}

void Resource::Setup()
{
	text_wood_ = sf::Text(api::general::resource_manager::font(api::graphics::ResourceFont::Font::kPixel));
	text_stone_ = sf::Text(api::general::resource_manager::font(api::graphics::ResourceFont::Font::kPixel));
	sprite_wood_ = sf::Sprite(api::general::resource_manager::texture(api::graphics::ResourceSprit::Texture::kIconWood));
	sprite_stone_ = sf::Sprite(api::general::resource_manager::texture(api::graphics::ResourceSprit::Texture::kIconStone));

	text_wood_->setPosition({ 50, 5 });
	text_stone_->setPosition({ 50, 50 });

	sprite_wood_->setScale({ 2.f, 2.f });
	sprite_stone_->setScale({ 2.f, 2.f });
	sprite_wood_->setPosition({ 10, 5 });
	sprite_stone_->setPosition({ 10, 50 });
}

void Resource::Update()
{
	if(wood_amount_ != last_wood_amount_)
	{
		text_wood_->setString(std::to_string(wood_amount_));
		last_wood_amount_ = wood_amount_;
	}
	if(stone_amount_ != last_stone_amount_)
	{
		text_stone_->setString(std::to_string(stone_amount_));
		last_stone_amount_ = stone_amount_;
	}
}

int Resource::wood_amount() const
{ return wood_amount_; }

int Resource::stone_amount() const
{ return stone_amount_; }

void Resource::add_wood(const int amount)
{
	wood_amount_ += amount;
}

void Resource::add_stone(const int amount)
{
	stone_amount_ += amount;
}

void Resource::sub_wood(int amount)
{
	wood_amount_ -= amount;
}

void Resource::sub_stone(int amount)
{
	stone_amount_ -= amount;
}
