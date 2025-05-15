#ifndef API_GRAPHICS_TILEMAP_H
#define API_GRAPHICS_TILEMAP_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "tile.h"

class TileMap final : public sf::Drawable
{
private:

	sf::Vector2u playground_size_u_;
	sf::Vector2u playground_tile_offset_u_;

	[[nodiscard]] sf::Vector2u SpritSize() const { return size_sprit_; }

	std::vector<Tile> tiles_;
	sf::Vector2u size_sprit_;
protected:
public:
	TileMap();
	void Setup(sf::Vector2u playground_size_u);
	void InitMap();
	[[nodiscard]] sf::Vector2u SizeSprit() const { return size_sprit_; }

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif //API_GRAPHICS_TILEMAP_H
