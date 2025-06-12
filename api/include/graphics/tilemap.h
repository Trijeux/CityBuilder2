#ifndef API_GRAPHICS_TILEMAP_H
#define API_GRAPHICS_TILEMAP_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "tile.h"

namespace api::graphics
{
	class TileMap final : public sf::Drawable
	{
	private:
		sf::Vector2u playground_size_u_;

		std::vector<Tile>         tiles_;
		std::vector<sf::Vector2f> tiles_walkable_;
		sf::Vector2u              size_sprit_;
	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		TileMap();
		void Setup(sf::Vector2u playground_size_u);
		void InitMap();
		[[nodiscard]] std::vector<sf::Vector2f> TilesWalkable() const { return tiles_walkable_; }
		[[nodiscard]] sf::Vector2u SizeSprit() const { return size_sprit_; }
	};
}
#endif //API_GRAPHICS_TILEMAP_H
