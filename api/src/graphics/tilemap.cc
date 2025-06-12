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

	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

	std::random_device                 r;
	std::default_random_engine         e1(r());
	std::uniform_int_distribution<int> uniform_dist(8.0f, 20.0f);
	const int                          mean = uniform_dist(e1);
	std::uniform_int_distribution<int> uniform_dist2(8.0f, 20.0f);
	const int                          mean2 = uniform_dist2(e1);

	const float scale_x = mean;
	const float scale_y = mean2;

	for(int x = 0; x < playground_size_u_.x; x++)
	{
		for(int y = 0; y < playground_size_u_.y; y++)
		{
			const float noise_value = noise.GetNoise(x * scale_x, y * scale_y);

			if(noise_value > 0.2f)
			{
				if(noise_value > 0.5f)
				{
					tiles_.emplace_back(Tile::TileType::kStone,
					                    x * SizeSprit().x,
					                    y * SizeSprit().y,
					                    false);
				}
				else
				{
					tiles_.emplace_back(Tile::TileType::kForest,
					                    x * SizeSprit().x,
					                    y * SizeSprit().y,
					                    false);
				}
			}
			else
			{
				tiles_.emplace_back(Tile::TileType::kGround,
				                    x * SizeSprit().x,
				                    y * SizeSprit().y,
				                    true);
				tiles_walkable_.emplace_back(x * SizeSprit().x, y * SizeSprit().y);
			}
		}
	}
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
