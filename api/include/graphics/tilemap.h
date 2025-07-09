#ifndef API_GRAPHICS_TILEMAP_H
#define API_GRAPHICS_TILEMAP_H

#include <functional>
#include <SFML/Graphics/RenderWindow.hpp>

#include "tile.h"

namespace api::graphics
{
	class TileMap final : public sf::Drawable
	{
	private:
		bool was_pressed_ = false;

		sf::Vector2u              playground_size_u_;
		Tile*                     tile_selected_;
		sf::Vector2i              mouse_last_position_;
		std::vector<Tile>         tiles_;
		std::vector<sf::Vector2f> tiles_forest_;
		std::vector<sf::Vector2f> tiles_stone_;
		std::vector<sf::Vector2f> tiles_walkable_;
		sf::Vector2u              size_sprit_;

		float timer_ = 0.f;
		float cooldown_ = 10.f;

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:
		TileMap();
		std::function<void(Tile&)> clicked_tile_;
		void                       Setup(sf::Vector2u playground_size_u);
		void                       InitMap();
		void                       HandleEvent(const sf::RenderWindow& window, const sf::View& view);

		//void Update(float dt);

		[[nodiscard]] std::vector<sf::Vector2f> tiles_walkable() const
		{
			return tiles_walkable_;
		}

		[[nodiscard]] sf::Vector2u size_sprit() const
		{
			return size_sprit_;
		}
	};
}
#endif //API_GRAPHICS_TILEMAP_H
