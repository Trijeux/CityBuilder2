#include "gameplay/building_manager.h" // Include the header file for BuildingManager

#include <random> // Include for random number generation

void api::gameplay::BuildingManager::set_active(const bool active)
{
	is_active_ = active; // Set the active state of the BuildingManager
}

void api::gameplay::BuildingManager::build(sf::RenderWindow& window)
{
	if(is_active())
	{
		set_active(false); // Deactivate building mode
		//ChangeCursor::BasicCursor(window); // Change cursor to basic mode
	}
	else
	{
		set_active(true); // Activate building mode
		//ChangeCursor::BuildingCursor(window); // Change cursor to building mode
	}
}

void api::gameplay::BuildingManager::CreateFirstBuildingHome(std::vector<graphics::Tile>& tiles)
{
	bool                       homeNotPlace = true; // Flag to control the placement loop
	std::random_device         r; // Random device for seeding
	std::default_random_engine e1(r()); // Random engine using the random device

	do
	{
		std::uniform_int_distribution<int> uniform_dist(tiles.size() / 4, tiles.size() / 1.2); // Uniform distribution for selecting a tile

		if(const int mean = uniform_dist(e1); tiles[mean].type() == graphics::Tile::TileType::kGround)
		{
			// Place the first home building on a randomly selected ground tile
			homes_.emplace_back(tiles[mean].position().x, tiles[mean].position().y, Build::kHome);
			//resource->AddBuilding(Build::kHome);
			tiles[mean].set_tile_type(graphics::Tile::TileType::kHome);
			tiles[mean].set_tile_sprite();
			homeNotPlace = false; // Exit the loop after placing the home building
		}
	}
	while(homeNotPlace);
}

void api::gameplay::BuildingManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const auto& home : homes_)
	{
		target.draw(home, states);// Draw each home building on the render target
	}

	for(const auto& work : works_)
	{
		target.draw(work, states); // Draw each lumberjack building on the render target
	}
}

api::gameplay::Building api::gameplay::BuildingManager::AddBuilding(graphics::Tile& tile, const Build building)
{
	// if (!is_a
	// ctive_)
	// {
	// 	return; // Exit if building mode is not active
	// }

	if(tile.type() == graphics::Tile::TileType::kGround)
	{
		bool                     build_ok = false;
		graphics::Tile::TileType type;

		std::optional<Building> building_return;

		switch(building)
		{
		case Build::kHome:
			{
				building_return = homes_.emplace_back(tile.position().x, tile.position().y, Build::kHome);
				//resource.AddBuilding(Build::kHome);
				//resource.PayBuilding(Build::kHome);
				type = graphics::Tile::TileType::kHome;
				build_ok = true;
			}
			break;
		case Build::kLumberjack:
			{
				building_return = works_.emplace_back(tile.position().x, tile.position().y, Build::kLumberjack);
				//resource.AddBuilding(Build::kFarm);
				//resource.PayBuilding(Build::kFarm);
				type = graphics::Tile::TileType::kLumberjack;
				build_ok = true;
			}
			break;
			case Build::kQuarry:
			{
				building_return = works_.emplace_back(tile.position().x, tile.position().y, Build::kQuarry);
				//resource.AddBuilding(Build::kFarm);
				//resource.PayBuilding(Build::kFarm);
				type = graphics::Tile::TileType::kQuarry;
				build_ok = true;
			}
			break;
		case Build::kNothing:
			break;
		default: ;
			break;
		}


		if(build_ok)
		{
			tile.set_tile_type(type); // Set the tile type to the newly added building type
			tile.set_tile_sprite(); // Set the tile sprite to match the building type
			return building_return.value();
		}
	}
}

void api::gameplay::BuildingManager::SubBuilding(graphics::Tile& tile)
{
	if(!is_active_)
	{
		return; // Exit if building mode is not active
	}

	// Check if the tile contains a building that can be removed
	if(tile.type() == graphics::Tile::TileType::kHome || tile.type() == graphics::Tile::TileType::kLumberjack)
	{
		const auto it_home = std::ranges::find_if(homes_,
		                                          [&tile](Building& b)
		                                          {
			                                          return b.position() == tile.position();
		                                          });

		const auto it_lumberjack = std::ranges::find_if(works_,
		                                                [&tile](Building& b)
		                                                {
			                                                return b.position() == tile.position();
		                                                });

		switch(tile.type())
		{
		case graphics::Tile::TileType::kHome:
			homes_.erase(it_home);
			break;
		case graphics::Tile::TileType::kLumberjack:
			works_.erase(it_lumberjack);
			break;
		default: ;
		}
	}

	tile.set_tile_type(graphics::Tile::TileType::kGround); // Set the tile type back to ground
	tile.set_tile_sprite(); // Set the tile sprite to match the ground type
}

void api::gameplay::BuildingManager::ClearMap()
{
	homes_.clear(); // Clear all buildings from the map
	works_.clear();
}
