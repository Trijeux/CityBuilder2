#include "ai/npc_manager.h"

void api::ai::NpcManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const auto& npc : npcs_) target.draw(*npc, states);
}

void api::ai::NpcManager::AddNpc(gameplay::Building* building)
{
	npcs_.emplace_back(std::make_unique<Npc>());
	npcs_.back()->Setup(building);
}

// void api::ai::NpcManager::RemoveAllNpc()
// {
// 	npcs_.clear();
// }

// void api::ai::NpcManager::RemoveLastNpc()
// {
// 	if(npcs_.empty()) return;
// 	npcs_.erase(npcs_.begin());
// }

// void api::ai::NpcManager::RemoveNpc(const Npc& npc)
// {
// 	std::erase_if(npcs_,
// 	              [&](const Npc& n)
// 	              {
// 		              return npc.is_dead();
// 	              });
// }

void api::ai::NpcManager::Update(const float dt, const graphics::TileMap& tile_map)
{
	for(auto& npc : npcs_)
	{
		if(!npc->have_work() && !building_manager_->works().empty())
		{
			for(auto& work : building_manager_->works())
			{
				if(!work.is_occupied())
				{
					npc->set_work(&work);
					work.set_occupied();
				}
			}
		}

		if(!npc->is_moving())
		{
			const sf::Vector2f objectif = npc->objectif();
			path_ = motion::path(npc->Position(), objectif, tile_map.tiles_walkable());
			if(path_.is_valid()) npc->set_path(path_);
		}
		npc->Update(dt);
	}
}
