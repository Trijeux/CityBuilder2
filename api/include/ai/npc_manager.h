#ifndef API_AI_NPC_MANAGER_H
#define API_AI_NPC_MANAGER_H

#include <vector>

#include "npc.h"
#include "graphics/tilemap.h"
#include "motion/astar.h"

namespace api::ai
{
	class NpcManager : public sf::Drawable
	{
		motion::Path       path_;
		std::vector<Npc>   npcs_;
		const graphics::TileMap* tile_map_ = nullptr;

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:
		void Setup(const graphics::TileMap* tile_map);
		void AddNpc();
		void RemoveNpc(const Npc& npc);
		void RemoveAllNpc();
		void RemoveLastNpc();
		void Update(float dt);
	};
}

#endif //API_AI_NPC_MANAGER_H
