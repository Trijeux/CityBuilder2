#include "gameplay/resource.h"

#include <iostream>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "general/resource_manager.h"

void Resource::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*sprite_wood_, states);
	target.draw(*sprite_stone_, states);
	target.draw(*sprite_food_, states);
	target.draw(*text_wood_, states);
	target.draw(*text_stone_, states);
	target.draw(*text_food_, states);
}

void Resource::Setup()
{
	text_wood_ = sf::Text(api::general::resource_manager::font(api::graphics::ResourceFont::Font::kPixel));
	text_stone_ = sf::Text(api::general::resource_manager::font(api::graphics::ResourceFont::Font::kPixel));
	text_food_ = sf::Text(api::general::resource_manager::font(api::graphics::ResourceFont::Font::kPixel));
	sprite_wood_ = sf::Sprite(api::general::resource_manager::texture(api::graphics::ResourceSprit::Texture::kIconWood));
	sprite_stone_ = sf::Sprite(api::general::resource_manager::texture(api::graphics::ResourceSprit::Texture::kIconStone));
	sprite_food_ = sf::Sprite(api::general::resource_manager::texture(api::graphics::ResourceSprit::Texture::kIconFood));

	text_wood_->setPosition({ 50, 5 });
	text_stone_->setPosition({ 50, 50 });
	text_food_->setPosition({ 50, 90 });

	sprite_wood_->setScale({ 2.f, 2.f });
	sprite_stone_->setScale({ 2.f, 2.f });
	sprite_food_->setScale({ 2.f, 2.f });
	sprite_wood_->setPosition({ 10, 5 });
	sprite_stone_->setPosition({ 10, 50 });
	sprite_food_->setPosition({ 10, 90 });
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
	if(food_amount_ != last_food_amount_)
	{
		text_food_->setString(std::to_string(food_amount_));
		last_food_amount_ = food_amount_;
	}
}

int Resource::wood_amount() const
{ return wood_amount_; }

int Resource::stone_amount() const
{ return stone_amount_; }

int Resource::food_amount() const
{ return food_amount_; }

void Resource::add_wood(const int amount)
{
	wood_amount_ += amount;
}

void Resource::add_stone(const int amount)
{
	stone_amount_ += amount;
}

void Resource::add_food(int amount)
{
	food_amount_ += amount;
}

void Resource::sub_wood(int amount)
{
	wood_amount_ -= amount;
}

void Resource::sub_stone(int amount)
{
	stone_amount_ -= amount;
}

void Resource::sub_food(int amount)
{
	food_amount_ -= amount;
}
