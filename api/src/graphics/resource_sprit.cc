#include <iostream>

#include "graphics/resource_sprit.h"

void ResourceSprit::Setup()
{
	LoadAllTextures();
}

sf::Texture& ResourceSprit::GetTexture(Texture resource_id)
{
	if(static_cast<int>(resource_id) < textures_.size())
	{
		return textures_.at(static_cast<int>(resource_id));
	}
	return blank_texture_;
}

void ResourceSprit::LoadAllTextures()
{
	blank_texture_ = sf::Texture();

	blank_texture_ = sf::Texture();

	if(!textures_.at(static_cast<int>(Texture::kGround)).loadFromFile("resources/sprit/ground.png"))
	{
		std::cout << "Error loading ground texture" << std::endl;
	}
	if(!textures_.at(static_cast<int>(Texture::kStone)).loadFromFile("resources/sprit/stone.png"))
	{
		std::cout << "Error loading stone texture" << std::endl;
	}
	if(!textures_.at(static_cast<int>(Texture::kForest)).loadFromFile("resources/sprit/forest.png"))
	{
		std::cout << "Error loading forest texture" << std::endl;
	}
}
