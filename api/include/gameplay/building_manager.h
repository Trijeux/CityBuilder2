#ifndef BUILDING_MANAGER_H
#define BUILDING_MANAGER_H

#include <vector>
#include "building.h" // Assuming Building class is defined in "building.h"
#include "graphics/tile.h"

namespace api::gameplay
{
    class BuildingManager
    {
    private:
        bool is_active_ = false; // Flag indicating if the building manager is active

        std::vector<sf::Vector2f> homes_;// Vector to store instances of Building
        std::vector<sf::Vector2f> lumberjacks_;

        // Private methods
        void SetActive(bool active); // Method to set the activity status of the manager
        [[nodiscard]] bool GetActive() const; // Method to retrieve the activity status of the manager

    public:
        // Public methods

        // Method to add a new building to a tile using game resources
        void AddBuilding(api::graphics::Tile& tile, api::gameplay::Build build);

        // Method to remove a building from a tile using game resources
        void SubBuilding(api::graphics::Tile& tile);

        // Method to clear all buildings from the manager
        void ClearMap();

        // Method to create the first building (presumably a home) on a vector of tiles using game resources
        void CreateFirstBuildingHome(std::vector<api::graphics::Tile>& tiles);

        // Method to build/render all buildings managed by this manager
        void build(sf::RenderWindow& window);
    };
}
#endif // BUILDING_MANAGER_H
