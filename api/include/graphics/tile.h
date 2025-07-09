#ifndef API_GRAPHICS_TILE_H
#define API_GRAPHICS_TILE_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace api::graphics
{
	class Tile final : public sf::Drawable
	{
	public:
		enum class TileType
		{
			kGround,
			kForest,
			kStone,
			kHome,
			kLumberjack,
			kQuarry
		};

		Tile(TileType type, float x, float y, bool is_walkable);

		bool is_walkable() const { return is_walkable_; }
		sf::Vector2f position() const { return sprite_->getPosition(); }

		void Select();

		void Unselect();

		void set_tile_type(TileType);

		void set_tile_sprite();

		void set_walkable(bool is_walkable) { is_walkable_ = is_walkable; }

		TileType type() const;

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::RectangleShape outline_;

		bool is_selected_ = false;

		std::optional<sf::Sprite> sprite_;

		bool is_walkable_;

		TileType type_;

		sf::Texture& GetFromType() const;
	};
}

#endif //API_GRAPHICS_TILE_H