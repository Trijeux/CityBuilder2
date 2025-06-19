#include "gameplay/building.h"// Include header file for Building class

#include "general/resource_manager.h"

api::gameplay::Building::Building(const float x, const float y, const Build build)
{
	// Constructor: Initializes a Building object with specified position (x, y) and type (build)

	switch(build)
	{
	case Build::kHome:
		// If building type is home, set its texture to the corresponding texture from ResourceManager
		sprite_ = sf::Sprite(general::resource_manager::texture(graphics::ResourceSprit::Texture::kHome));
		break;
	case Build::kLumberjack:
		// If building type is mine, set its texture to the corresponding texture from ResourceManager
		sprite_ = sf::Sprite(general::resource_manager::texture(graphics::ResourceSprit::Texture::kLumberjack));
		break;
	default: ;
	}
	// Set the position of the building
	type_ = build;
	position_ = sf::Vector2f(x, y);
	sprite_->setPosition(position_); // Set position of the sprite shape

	// 5 = nombre de tiles en largeur et en longeur (5*5)
	detection_zone_.setSize(sf::Vector2f(sprite_->getTexture().getSize()) * 5.f);
	detection_zone_.setOrigin(sf::Vector2f(detection_zone_.getSize() / 2.f));
	detection_zone_.setPosition(position_ + sf::Vector2f(sprite_->getTexture().getSize()) / 2.f);
	detection_zone_.setFillColor(sf::Color(200, 147, 141, 65)); // Transparent fill color
	detection_zone_.setOutlineColor(sf::Color(200, 147, 141, 255)); // White outline color
	detection_zone_.setOutlineThickness(-1);
}

void api::gameplay::Building::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	if(type_ == Build::kNothing) return;
	if(type_ != Build::kHome) target.draw(detection_zone_, states); // Draw the building's detection_zone_ on the render target
	target.draw(*sprite_, states); // Draw the building's sprite on the render target
}
