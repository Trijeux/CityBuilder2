#include <SFML/Graphics.hpp>

#include "../../api/include/graphics/resource_manager.h"
#include "../../api/include/graphics/tilemap.h"

namespace Game
{
	namespace
	{
		sf::RenderWindow          window_;
		TileMap                   tilemap_;
	}

	void CreateTilemap()
	{
		tilemap_.Setup(sf::Vector2u(window_.getSize().x / tilemap_.SizeSprit().x, window_.getSize().y / tilemap_.SizeSprit().y));

		tilemap_.InitMap();
	}

	static void Setup()
	{
		window_.create(sf::VideoMode({1600, 800}), "Game");
		ResourceManager::Setup();
		CreateTilemap();
	}

	void Run()
	{
		Setup();
		while(window_.isOpen())
		{
			while(const std::optional event = window_.pollEvent())
			{
				if(event->is<sf::Event::Closed>()) window_.close();
			}

			window_.clear();
			window_.draw(tilemap_);
			window_.display();
		}
	}
}
