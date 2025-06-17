#include "gameplay/building_manager.h" // Include the header file for BuildingManager

#include <random> // Include for random number generation

void api::gameplay::BuildingManager::SetActive(const bool active)
{
	is_active_ = active; // Set the active state of the BuildingManager
}

bool api::gameplay::BuildingManager::GetActive() const
{
	return is_active_; // Get the current active state of the BuildingManager
}

void api::gameplay::BuildingManager::build(sf::RenderWindow& window)
{
	if (GetActive())
	{
		SetActive(false); // Deactivate building mode
		//ChangeCursor::BasicCursor(window); // Change cursor to basic mode
	}
	else
	{
		SetActive(true); // Activate building mode
		//ChangeCursor::BuildingCursor(window); // Change cursor to building mode
	}
}

void api::gameplay::BuildingManager::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	for (const auto& b : buildings_)
	{
		target.draw(b, states); // Draw each building in the BuildingManager
	}
}

void api::gameplay::BuildingManager::CreateFirstBuildingHome(std::vector<graphics::Tile>& tiles)
{
	bool homeNotPlace = true; // Flag to control the placement loop
	std::random_device r; // Random device for seeding
	std::default_random_engine e1(r()); // Random engine using the random device

	do
	{
		std::uniform_int_distribution<int> uniform_dist(tiles.size() / 4, tiles.size() / 1.2); // Uniform distribution for selecting a tile

		if (const int mean = uniform_dist(e1); tiles[mean].type() == graphics::Tile::TileType::kGround)
		{
			// Place the first home building on a randomly selected ground tile
			buildings_.emplace_back(tiles[mean].Position().x, tiles[mean].Position().y, Build::kHome);
			//resource->AddBuilding(Build::kHome);
			tiles[mean].SetTileType(graphics::Tile::TileType::kHome);
			tiles[mean].SetTileSprite();
			homeNotPlace = false; // Exit the loop after placing the home building
		}
	} while (homeNotPlace);
}

void api::gameplay::BuildingManager::AddBuilding(graphics::Tile& tile, const Build building)
{
	// if (!is_active_)
	// {
	// 	return; // Exit if building mode is not active
	// }

	if (tile.type() == graphics::Tile::TileType::kGround)
	{
		bool                     build_ok = false;
		graphics::Tile::TileType type;

		switch (building)
		{
		case Build::kHome:
		{
			buildings_.emplace_back(tile.Position().x, tile.Position().y, Build::kHome);
			//resource.AddBuilding(Build::kHome);
			//resource.PayBuilding(Build::kHome);
			type = graphics::Tile::TileType::kHome;
			build_ok = true;
		}
		break;
		case Build::kLumberjack:
		{
			buildings_.emplace_back(tile.Position().x, tile.Position().y, Build::kLumberjack);
			//resource.AddBuilding(Build::kFarm);
			//resource.PayBuilding(Build::kFarm);
			type = graphics::Tile::TileType::kLumberjack;
			build_ok = true;
		}
		break;
		case Build::kNothing:
			break;
		default:;
			break;
		}


		if (build_ok)
		{
			tile.SetTileType(type); // Set the tile type to the newly added building type
			tile.SetTileSprite(); // Set the tile sprite to match the building type
		}
	}
}

void api::gameplay::BuildingManager::SubBuilding(graphics::Tile& tile)
{
	if (!is_active_)
	{
		return; // Exit if building mode is not active
	}

	// Check if the tile contains a building that can be removed
	if (tile.type() == graphics::Tile::TileType::kHome || tile.type() == graphics::Tile::TileType::kLumberjack)
	{
		// Find the building in the list of buildings and remove it
		const auto it = std::ranges::find_if(buildings_, [&tile](Building& b) {
			return b.Position() == tile.Position(); });

		buildings_.erase(it); // Erase the building from the list
		//resource.SubBuilding(tile.Type()); // Subtract the building type from the resources
	}

	tile.SetTileType(graphics::Tile::TileType::kGround); // Set the tile type back to ground
	tile.SetTileSprite(); // Set the tile sprite to match the ground type
}

void api::gameplay::BuildingManager::ClearMap()
{
	buildings_.clear(); // Clear all buildings from the map
}
