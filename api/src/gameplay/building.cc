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
	case Build::kQuarry:
		sprite_ = sf::Sprite(general::resource_manager::texture(graphics::ResourceSprit::Texture::kQuarry));
		break;
	default: ;
	}
	// Set the position of the building
	type_ = build;
	position_ = sf::Vector2f(x, y);
	sprite_->setPosition(position_); // Set position of the sprite shape

	// 5 = nombre de tiles en largeur et en longeur (5*5)
	if(build != Build::kHome)
	{
		detection_zone_debug_.setSize(sf::Vector2f(sprite_->getTexture().getSize()) * numbers_tiles_);
		detection_zone_debug_.setOrigin(sf::Vector2f(detection_zone_debug_.getSize() / 2.f));
		detection_zone_debug_.setPosition(position_ + sf::Vector2f(sprite_->getTexture().getSize()) / 2.f);

		detection_zone_.setRadius(sprite_->getTexture().getSize().x * 2.5f);
		detection_zone_.setOrigin(sf::Vector2f(detection_zone_.getRadius(), detection_zone_.getRadius()));
		detection_zone_.setPosition(detection_zone_debug_.getPosition());

		if(build == Build::kLumberjack)
		{
			detection_zone_.setFillColor(sf::Color(200, 147, 141, 45)); // Transparent fill color
			detection_zone_.setOutlineColor(sf::Color(200, 147, 141, 255)); // White outline color
		}
		if(build == Build::kQuarry)
		{
			detection_zone_.setFillColor(sf::Color(141, 147, 200, 45)); // Transparent fill color
			detection_zone_.setOutlineColor(sf::Color(141, 147, 200, 255)); // White outline color
		}

		detection_zone_debug_.setFillColor(sf::Color(141, 147, 200, 45)); // Transparent fill color
		detection_zone_debug_.setOutlineColor(sf::Color(141, 147, 200, 255)); // White outline color

		detection_zone_.setOutlineThickness(-1);
	}

	CreateNeighbor(sprite_->getPosition(), 2, sprite_->getTexture().getSize().x);
}

void api::gameplay::Building::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	if(type_ == Build::kNothing) return;
	if(type_ != Build::kHome) target.draw(detection_zone_, states); // Draw the building's detection_zone_ on the render target
	//if(type_ != Build::kHome) target.draw(detection_zone_debug_, states);
	target.draw(*sprite_, states); // Draw the building's sprite on the render target
}

void api::gameplay::Building::CreateNeighbor(const sf::Vector2f& center_pos, int radius, float tile_size)
{
	neighbors_.clear();

	for(int dx = -radius; dx <= radius; dx++)
	{
		for(int dy = -radius; dy <= radius; dy++)
		{
			if(dx == 0 && dy == 0) continue;

			// Ajoute une position autour du centre
			sf::Vector2f pos(center_pos.x + dx * tile_size, center_pos.y + dy * tile_size);
			neighbors_.push_back(pos);
		}
	}
}
