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
		return general::resource_manager::Sprit(ResourceSprit::Texture::kForest);
	case TileType::kGround:
		return general::resource_manager::Sprit(ResourceSprit::Texture::kGround);
	case TileType::kStone:
		return general::resource_manager::Sprit(ResourceSprit::Texture::kStone);
		case TileType::kHome:
		return general::resource_manager::Sprit(ResourceSprit::Texture::kHome);
		case TileType::kLumberjack:
		return general::resource_manager::Sprit(ResourceSprit::Texture::kLumberjack);
	default:
		return general::resource_manager::Sprit(ResourceSprit::Texture::kMax);
	}
}

api::graphics::Tile::Tile(const TileType type, const float x, const float y, const bool is_walkable)
{
	#if TRACY_ENABLE
	ZoneNamedN(CreatTile, "Creat Tile", true);
	#endif
	type_ = type;

	sprite_ = sf::Sprite(GetFromType());
	sprite_->setPosition(sf::Vector2f(x, y));

	outline_.setSize(sf::Vector2f(sprite_->getTexture().getSize()));
	outline_.setPosition(sf::Vector2f(x, y));
	outline_.setFillColor(sf::Color(255, 255, 255, 0));  // Transparent fill color
	outline_.setOutlineColor(sf::Color::White);  // White outline color
	outline_.setOutlineThickness(-1);

	is_walkable_ = is_walkable;
}

void api::graphics::Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	#if TRACY_ENABLE
	ZoneNamedN(DrawTile, "Draw Tile", true);
	#endif
	target.draw(*sprite_, states);

	if (is_selected_) {
		target.draw(outline_, states);  // Draw the outline if the tile is selected
	}
}

void api::graphics::Tile::Select()
{
	is_selected_ = true;
}

void api::graphics::Tile::Unselect()
{
	is_selected_ = false;
}

void api::graphics::Tile::SetTileType(const TileType type)
{
	type_ = type;
}

// Update the sprite's texture based on the TileType
void api::graphics::Tile::SetTileSprite()
{
	sprite_->setTexture(GetFromType());
}

api::graphics::Tile::TileType api::graphics::Tile::type() const
{
	return type_;
}