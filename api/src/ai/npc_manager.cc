#include "ai/npc_manager.h"

void api::ai::NpcManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const auto& npc : npcs_) target.draw(npc, states);
}

void api::ai::NpcManager::AddNpc()
{
	Npc npc;
	npc.Setup();
	npcs_.emplace_back(std::move(npc));
}

void api::ai::NpcManager::RemoveAllNpc()
{
	npcs_.clear();
}

void api::ai::NpcManager::RemoveLastNpc()
{
	if(npcs_.empty()) return;
	npcs_.erase(npcs_.begin());
}

void api::ai::NpcManager::RemoveNpc(const Npc& npc)
{
	std::erase_if(npcs_,
	              [&](const Npc& n)
	              {
		              return npc.is_dead();
	              });
}

void api::ai::NpcManager::Update(const float dt, const graphics::TileMap& tile_map)
{
	for(auto& npc : npcs_)
	{
		if(!npc.is_moving())
		{
			sf::Vector2f objectif = tile_map.tiles_walkable()[15];
			path_ = motion::path(npc.Position(), objectif, tile_map.tiles_walkable());
			if(path_.is_valid()) npc.set_path(path_);
		}
		npc.Update(dt);
	}
}
