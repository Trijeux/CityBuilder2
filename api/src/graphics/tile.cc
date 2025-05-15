#include <SFML/Graphics/RenderTarget.hpp>

#include "graphics/tile.h"
#include "graphics/resource_manager.h"

sf::Texture& Tile::GetFromType() const
{
	switch (type_)
	{
	case TileType::kForest:
		return ResourceManager::Sprit(ResourceSprit::Texture::kForest);
	case TileType::kGround:
		return ResourceManager::Sprit(ResourceSprit::Texture::kGround);
	case TileType::kStone:
		return ResourceManager::Sprit(ResourceSprit::Texture::kStone);
	default:
		return ResourceManager::Sprit(ResourceSprit::Texture::kMax);
	}
}

Tile::Tile(const TileType type, const float x, const float y, const bool is_walkable)
{
	type_ = type;

	sprite_ = sf::Sprite(GetFromType());
	sprite_->setPosition(sf::Vector2f(x, y));

	is_walkable_ = is_walkable;
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*sprite_, states);
}


