#ifndef API_GRAPHICS_TILE_H
#define API_GRAPHICS_TILE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Tile final : public sf::Drawable
{
public:
	enum class TileType
	{
		kGround,
		kForest,
		kStone
	};

	Tile(TileType type, float x, float y, bool is_walkable);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::optional<sf::Sprite> sprite_;

	bool is_walkable_;

	TileType type_;

	sf::Texture& GetFromType() const;
};

#endif //API_GRAPHICS_TILE_H