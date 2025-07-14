#include "graphics/resource_sprit.h"

#include <iostream>

#if TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif

void api::graphics::ResourceSprit::Setup()
{
	LoadAllTextures();
}

sf::Texture& api::graphics::ResourceSprit::texture(Texture resource_id)
{
	#if TRACY_ENABLE
	ZoneNamedN(GetTexture, "Get Texture", true);
	#endif
	if(static_cast<int>(resource_id) < textures_.size())
	{
		return textures_.at(static_cast<int>(resource_id));
	}
	return blank_texture_;
}

void api::graphics::ResourceSprit::LoadAllTextures()
{
	#if TRACY_ENABLE
	ZoneNamedN(LoadAllTexture, "Load All Texture", true);
	#endif
	blank_texture_ = sf::Texture();

	if(!textures_.at(static_cast<int>(Texture::kGround)).loadFromFile("resources/sprite/ground.png"))
	{
		std::cout << "Error loading ground texture" << std::endl;
	}
	if(!textures_.at(static_cast<int>(Texture::kStone)).loadFromFile("resources/sprite/stone.png"))
	{
		std::cout << "Error loading stone texture" << std::endl;
	}
	if(!textures_.at(static_cast<int>(Texture::kForest)).loadFromFile("resources/sprite/forest.png"))
	{
		std::cout << "Error loading forest texture" << std::endl;
	}
	if(!textures_.at(static_cast<int>(Texture::kForestCut)).loadFromFile("resources/sprite/forest_cut.png"))
	{
		std::cout << "Error loading forest_cut texture" << std::endl;
	}
	if(!textures_.at(static_cast<int>(Texture::kBlue)).loadFromFile("resources/sprite/npc_blue.png"))
	{
		std::cout << "Error loading blue texture" << std::endl;
	}
	if(!textures_.at(static_cast<int>(Texture::kButton)).loadFromFile("resources/sprite/button.png"))
	{
		std::cout << "Error loading button texture" << std::endl;
	}
	if(!textures_.at(static_cast<int>(Texture::kHome)).loadFromFile("resources/sprite/home.png"))
	{
		std::cout << "Error loading home texture" << std::endl;
	}
	if(!textures_.at(static_cast<int>(Texture::kLumberjack)).loadFromFile("resources/sprite/lumberjack.png"))
	{
		std::cout << "Error loading lumberjack texture" << std::endl;
	}
	if(!textures_.at(static_cast<int>(Texture::kQuarry)).loadFromFile("resources/sprite/quarry.png"))
	{
		std::cout << "Error loading quarry texture" << std::endl;
	}
	if(!textures_.at(static_cast<int>(Texture::kIconWood)).loadFromFile("resources/sprite/wood_icon.png"))
	{
		std::cout << "Error loading icon Wood texture" << std::endl;
	}
	if(!textures_.at(static_cast<int>(Texture::kIconStone)).loadFromFile("resources/sprite/stone_icon.png"))
	{
		std::cout << "Error loading icon stone texture" << std::endl;
	}
}
