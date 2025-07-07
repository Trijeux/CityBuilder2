#ifndef API_AI_NPC_MANAGER_H
#define API_AI_NPC_MANAGER_H

#include <vector>

#include "npc.h"
#include "gameplay/building_manager.h"
#include "graphics/tilemap.h"
#include "motion/astar.h"

namespace api::ai
{
	class NpcManager : public sf::Drawable
	{
		motion::Path                      path_;
		std::vector<std::unique_ptr<Npc>> npcs_;
		gameplay::BuildingManager*         building_manager_;

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:
		void set_building_manager(gameplay::BuildingManager* building){ building_manager_ = building; }

		void AddNpc(gameplay::Building building);
		//void RemoveNpc(const Npc& npc);
		//void RemoveAllNpc();
		//void RemoveLastNpc();
		void Update(float dt, const graphics::TileMap& tile_map);
	};
}

#endif //API_AI_NPC_MANAGER_H
