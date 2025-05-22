#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Text.hpp>

#if TRACY_ENABLE
	#include <tracy/Tracy.hpp>
#endif

#include "general/resource_manager.h"
#include "graphics/tilemap.h"

namespace game::MainGame
{
	namespace
	{
		sf::RenderWindow       window;
		std::optional<sf::Sound> sound;
		std::optional<sf::Text> text;
		api::graphics::TileMap tilemap;
	}

	void CreateTilemap()
	{
		tilemap.Setup(sf::Vector2u(window.getSize().x / tilemap.SizeSprit().x, window.getSize().y / tilemap.SizeSprit().y));
		tilemap.InitMap();
	}

	static void Setup()
	{
		#if TRACY_ENABLE
		ZoneScopedN("Game Setup");
		#endif
		window.create(sf::VideoMode({1600, 800}), "Game");
		api::general::ResourceManager::Setup();

		text = sf::Text(api::general::ResourceManager::Font(api::graphics::ResourceFont::Font::kPixel), "Hello World");
		text->setOrigin(text->getGlobalBounds().size / 2.f);
		text->setPosition(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));

		sound = sf::Sound(api::general::ResourceManager::Sound(api::sound::ResourceSound::Sound::kMusicBG));
		sound->setLooping(true);
		sound->setPitch(0.5f);
		sound->play();


		CreateTilemap();
	}

	void Run()
	{
		#if TRACY_ENABLE
		ZoneScopedN("Run Game");
		#endif
		Setup();
		while(window.isOpen())
		{
			while(const std::optional event = window.pollEvent())
			{
				if(event->is<sf::Event::Closed>()) window.close();
			}

			window.clear();
			window.draw(tilemap);
			window.draw(*text);
			window.display();
		}
	}
}
