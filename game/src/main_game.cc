#include <SFML/Graphics.hpp>

#include "graphics/resource_manager.h"
#include "graphics/tilemap.h"

namespace game::MainGame
{
	namespace
	{
		sf::RenderWindow          window;
		api::graphics::TileMap                   tilemap;
	}

	void CreateTilemap()
	{
		tilemap.Setup(sf::Vector2u(window.getSize().x / tilemap.SizeSprit().x, window.getSize().y / tilemap.SizeSprit().y));

		tilemap.InitMap();
	}

	static void Setup()
	{
		window.create(sf::VideoMode({1600, 800}), "Game");
		api::graphics::ResourceManager::Setup();
		CreateTilemap();
	}

	void Run()
	{
		Setup();
		while(window.isOpen())
		{
			while(const std::optional event = window.pollEvent())
			{
				if(event->is<sf::Event::Closed>()) window.close();
			}

			window.clear();
			window.draw(tilemap);
			window.display();
		}
	}
}
