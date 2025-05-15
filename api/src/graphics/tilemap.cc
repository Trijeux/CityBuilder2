#include <FastNoiseLite.h>
#include <random>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../../include/graphics/tilemap.h"
#include "../../include/graphics/resource_manager.h"

TileMap::TileMap()
{
	size_sprit_ = sf::Vector2u(sf::Texture("resources/sprit/ground.png").getSize());
}

void TileMap::Setup(const sf::Vector2u playground_size_u)
{
	playground_size_u_ = playground_size_u;
	playground_tile_offset_u_.x = size_sprit_.x;
	playground_tile_offset_u_.y = size_sprit_.y;
}

void TileMap::InitMap()
{
	tiles_.clear();

	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(8.0f, 20.0f);
	const int mean = uniform_dist(e1);
	std::uniform_int_distribution<int> uniform_dist2(8.0f, 20.0f);
	const int mean2 = uniform_dist2(e1);

	const float scale_x = mean;
	const float scale_y = mean2;


	for (int x = 0; x < playground_size_u_.x; x++)
	{
		for (int y = 0; y < playground_size_u_.y; y++)
		{
			const float noise_value = noise.GetNoise(x * scale_x, y * scale_y);

			if (noise_value > 0.2f)
			{
				if (noise_value > 0.5f)
				{
					tiles_.emplace_back(Tile::TileType::kStone,
						x * SpritSize().x, y * SpritSize().y, false);
				}
				else
				{
					tiles_.emplace_back(Tile::TileType::kForest,
						x * SpritSize().x, y * SpritSize().y, false);
				}
			}
			else
			{
				tiles_.emplace_back(Tile::TileType::kGround,
					x * SpritSize().x, y * SpritSize().y, true);
			}
		}
	}
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& tile : tiles_)
	{
		target.draw(tile, states);
	}
}
