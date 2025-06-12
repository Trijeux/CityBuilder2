#include "ai/npc_manager.h"

void api::ai::NpcManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const auto& npc : npcs_) target.draw(npc, states);
}

void api::ai::NpcManager::Setup(const graphics::TileMap* tile_map)
{
	tile_map_ = tile_map;

	// path_.AddPoints({
	// 	{0, 0},
	// 	{16, 0},
	// 	{16, 16},
	// 	{16 * 2, 16},
	// 	{16 * 2, 16 * 2},
	// 	{16 * 3, 16 * 2},
	// 	{16 * 3, 16 * 3},
	// 	{16 * 4, 16 * 3},
	// 	{16 * 4, 16 * 4}});
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
		              return npc.IsDead();
	              });
}

void api::ai::NpcManager::Update(const float dt)
{
	for(auto& npc : npcs_)
	{
		if(!npc.IsMoving())
		{
			sf::Vector2f objectif = tile_map_->TilesWalkable()[15];
			path_ = motion::GetPath(npc.Position(), objectif, tile_map_->TilesWalkable());
			if(path_.IsValid()) npc.SetPath(path_);
		}
		npc.Update(dt);
	}
}
