#ifndef API_AI_NPC_MANAGER_H
#define API_AI_NPC_MANAGER_H

#include <vector>

#include "npc.h"

namespace api::ai
{
	class NpcManager : public sf::Drawable
	{
		motion::Path     path_;
		std::vector<Npc> npcs_;

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:
		void Setup();
		void AddNpc();
		void RemoveNpc(const Npc& npc);
		void RemoveAllNpc();
		void RemoveLastNpc();
		void Update(float dt);
	};
}

#endif //API_AI_NPC_MANAGER_H
