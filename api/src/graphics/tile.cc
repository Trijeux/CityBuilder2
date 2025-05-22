#include "graphics/tile.h"

#include <SFML/Graphics/RenderTarget.hpp>

#if TRACY_ENABLE
	#include <tracy/Tracy.hpp>
#endif

#include "general/resource_manager.h"

sf::Texture& api::graphics::Tile::GetFromType() const
{
	switch(type_)
	{
	case TileType::kForest:
		return general::ResourceManager::Sprit(ResourceSprit::Texture::kForest);
	case TileType::kGround:
		return general::ResourceManager::Sprit(ResourceSprit::Texture::kGround);
	case TileType::kStone:
		return general::ResourceManager::Sprit(ResourceSprit::Texture::kStone);
	default:
		return general::ResourceManager::Sprit(ResourceSprit::Texture::kMax);
	}
}

api::graphics::Tile::Tile(const TileType type, const float x, const float y, const bool is_walkable)
{
	#if TRACY_ENABLE
	ZoneScopedN("Creat Tile");
	#endif
	type_ = type;

	sprite_ = sf::Sprite(GetFromType());
	sprite_->setPosition(sf::Vector2f(x, y));

	is_walkable_ = is_walkable;
}

void api::graphics::Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	#if TRACY_ENABLE
	ZoneScopedN("Draw Tile");
	#endif
	target.draw(*sprite_, states);
}
