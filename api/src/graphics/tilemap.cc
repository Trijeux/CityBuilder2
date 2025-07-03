#include "graphics/tilemap.h"

#include <random>

#include <SFML/Graphics/RenderTarget.hpp>
#if TRACY_ENABLE
  #include <tracy/Tracy.hpp>
#endif

#include "FastNoiseLite.h"
#include "general/resource_manager.h"

api::graphics::TileMap::TileMap()
{
	#if TRACY_ENABLE
	ZoneNamedN(CreatTilemap, "Creat Tilemap", true);
	#endif
	size_sprit_ = sf::Vector2u(sf::Texture("resources/sprite/ground.png").getSize());
}

void api::graphics::TileMap::Setup(const sf::Vector2u playground_size_u)
{
	#if TRACY_ENABLE
	ZoneNamedN(SetupTilemap, "Setup Tilemap", true);
	#endif
	playground_size_u_ = playground_size_u;
	tiles_.reserve(playground_size_u_.x * playground_size_u_.y);
}

void api::graphics::TileMap::InitMap()
{
	#if TRACY_ENABLE
	ZoneNamedN(InitMap, "InitMap", true);
	#endif

	tiles_.clear();
	tiles_walkable_.clear();

	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

	std::random_device                 r;
	std::default_random_engine         e1(r());
	std::uniform_int_distribution<int> uniform_dist(8.0f, 20.0f);
	const int                          scale_x = uniform_dist(e1);
	const int                          scale_y = uniform_dist(e1);

	for(int x = 0; x < playground_size_u_.x; x++)
	{
		for(int y = 0; y < playground_size_u_.y; y++)
		{
			const float noise_value = noise.GetNoise(static_cast<float>(x * scale_x), static_cast<float>(y * scale_y));

			if(noise_value > 0.2f)
			{
				if(noise_value > 0.5f)
				{
					tiles_.emplace_back(Tile::TileType::kStone,
					                    x * size_sprit().x,
					                    y * size_sprit().y,
					                    false);
					tiles_stone_.emplace_back(x * size_sprit().x, y * size_sprit().y);
				}
				else
				{
					tiles_.emplace_back(Tile::TileType::kForest,
					                    x * size_sprit().x,
					                    y * size_sprit().y,
					                    false);
					tiles_forest_.emplace_back(x * size_sprit().x, y * size_sprit().y);
				}
			}
			else
			{
				tiles_.emplace_back(Tile::TileType::kGround,
				                    x * size_sprit().x,
				                    y * size_sprit().y,
				                    true);
				tiles_walkable_.emplace_back(x * size_sprit().x, y * size_sprit().y);
			}
		}
	}
}

void api::graphics::TileMap::HandleEvent(const sf::RenderWindow& window, const sf::View& view)
{
	if(sf::Mouse::getPosition(window) != mouse_last_position_)
	{
		// Convert mouse position to world coordinates
		const sf::Vector2f mouse_world_position = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);

		// Adjust mouse position based on tile size
		auto adjusted_mouse_position = sf::Vector2f(
			std::floor(mouse_world_position.x / size_sprit_.x) * size_sprit_.x,
			std::floor(mouse_world_position.y / size_sprit_.y) * size_sprit_.y
		);

		// Unselect previously selected tile
		if(tile_selected_ != nullptr)
		{
			tile_selected_->Unselect();
		}

		// Find the tile under the adjusted mouse position
		if(const auto tile_found = std::ranges::find_if(tiles_,
		                                                [&adjusted_mouse_position](const Tile& t)
		                                                {
			                                                return t.position() == adjusted_mouse_position;
		                                                }); tile_found != tiles_.end())
		{
			tile_selected_ = &(*tile_found); // Select the found tile
			tile_selected_->Select();
		}

		mouse_last_position_ = sf::Mouse::getPosition(window);
	}

	bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

	if(was_pressed_ && !pressed)
	{
		if(clicked_tile_ && tile_selected_ != nullptr)
		{
			clicked_tile_(*tile_selected_); // Handle click on the selected tile
		}
	}
	was_pressed_ = pressed;
}


void api::graphics::TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	#if TRACY_ENABLE
	ZoneNamedN(DrawTilemap, "Draw Tilemap", true);
	#endif
	for(const auto& tile : tiles_)
	{
		target.draw(tile, states);
	}
}
