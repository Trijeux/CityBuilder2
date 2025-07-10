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
	int                          scale_x = uniform_dist(e1);
	int                          scale_y = uniform_dist(e1);

	for(int x = 0; x < playground_size_u_.x; x++)
	{
		for(int y = 0; y < playground_size_u_.y; y++)
		{
			const float noise_value = noise.GetNoise(static_cast<float>(x * scale_x), static_cast<float>(y * scale_y));

			if(noise_value > 0.45f)
			{
				tiles_.emplace_back(Tile::TileType::kStone,
									(float)x * (float)size_sprit().x,
									(float)y * (float)size_sprit().y,
									false);
				tiles_stone_.emplace_back((float)x * (float)size_sprit().x, (float)y * (float)size_sprit().y);
			}
			else if(noise_value > 0.25f)
			{
				tiles_.emplace_back(Tile::TileType::kForest,
									(float)x * (float)size_sprit().x,
									(float)y * (float)size_sprit().y,
									false);
				tiles_forest_.emplace_back((float)x * (float)size_sprit().x, (float)y * (float)size_sprit().y);
			}
			else
			{
				tiles_.emplace_back(Tile::TileType::kGround,
				                    (float)x * (float)size_sprit().x,
				                    (float)y * (float)size_sprit().y,
				                    true);
				tiles_walkable_.emplace_back((float)x * (float)size_sprit().x, (float)y * (float)size_sprit().y);
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

bool positionsEqual(const sf::Vector2f& a, const sf::Vector2f& b, float epsilon = 0.1f)
{
    return (std::abs(a.x - b.x) < epsilon) && (std::abs(a.y - b.y) < epsilon);
}

void api::graphics::TileMap::Update(const float dt)
{
    timer_ += dt;
    if (timer_ >= cooldown_)
    {
        std::vector<sf::Vector2f> tiles_forest_positions;

        // Recueillir toutes les positions actuelles de forêt
        for (const auto& tile : tiles_)
        {
            if (tile.type() == Tile::TileType::kForest)
            {
                tiles_forest_positions.emplace_back(tile.position());
            }
        }

        std::vector<Tile> new_tiles;
        new_tiles.reserve(tiles_.size());

        // D'abord on collecte les positions des tiles qui vont devenir forêt
        std::vector<bool> to_be_forest(tiles_.size(), false);

        for (size_t i = 0; i < tiles_.size(); ++i)
        {
            const auto& tile = tiles_[i];
            if (tile.type() == Tile::TileType::kGround)
            {
                sf::Vector2f pos = tile.position();
                bool tree_adjacent = false;

                for (int dx = -1; dx <= 1 && !tree_adjacent; ++dx)
                {
                    for (int dy = -1; dy <= 1 && !tree_adjacent; ++dy)
                    {
                        if (dx == 0 && dy == 0) continue;

                        sf::Vector2f neighbor_pos = { pos.x + dx * 16.f, pos.y + dy * 16.f };

                        for (const auto& forest_pos : tiles_forest_positions)
                        {
                            if (positionsEqual(forest_pos, neighbor_pos))
                            {
                                tree_adjacent = true;
                                break;
                            }
                        }
                    }
                }

                if (tree_adjacent)
                {
                    to_be_forest[i] = true;
                }
            }
        }

        // Maintenant on crée la nouvelle liste de tiles, en appliquant les changements
        for (size_t i = 0; i < tiles_.size(); ++i)
        {
            Tile tile = tiles_[i]; // copie

            if (to_be_forest[i])
            {
                tile.set_tile_type(Tile::TileType::kForest);
                tile.set_walkable(false);
                tile.set_tile_sprite(); // IMPORTANT : mettre à jour le sprite
                tiles_forest_positions.emplace_back(tile.position());
            }

            new_tiles.emplace_back(std::move(tile));
        }

        tiles_ = std::move(new_tiles);
        tiles_forest_ = std::move(tiles_forest_positions);

        timer_ = 0.f;
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
