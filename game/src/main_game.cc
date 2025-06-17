#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Text.hpp>

#if TRACY_ENABLE
	#include <tracy/Tracy.hpp>
#endif

#if DEBUG_ENABLE
#include "debug/button_debug.h"
#endif

#include <iostream>

#include "ai/npc_manager.h"
#include "gameplay/building.h"
#include "gameplay/building_manager.h"
#include "general/resource_manager.h"
#include "graphics/tilemap.h"
#include "ui/ui_button.h"

namespace game::main_game
{
	namespace
	{
		sf::Clock                      clock;
		sf::RenderWindow               window;
		std::optional<sf::Sound>       sound;
		std::optional<sf::Text>        text;
		api::graphics::TileMap         tilemap;
		api::ai::NpcManager            npc_manager;
		api::gameplay::BuildingManager building_manager;
		auto                           build = api::gameplay::Build::kHome;

		float delta_time = 0;

		#if DEBUG_ENABLE
		api::debug::ButtonDebug button_generator;
		api::debug::ButtonDebug button_add_npc;
		api::debug::ButtonDebug button_remove_last_npc;
		api::debug::ButtonDebug button_remove_all_npc;
		#endif
	}

	void CreateTilemap()
	{
		tilemap.Setup(sf::Vector2u(window.getSize().x / tilemap.SizeSprit().x, window.getSize().y / tilemap.SizeSprit().y));
		tilemap.InitMap();
	}

	static void Setup()
	{
		#if TRACY_ENABLE
		ZoneNamedN(GameSetup, "Game Setup", true);
		#endif
		window.create(sf::VideoMode({1600, 800}), "Game");
		api::general::resource_manager::Setup();

		text = sf::Text(api::general::resource_manager::Font(api::graphics::ResourceFont::Font::kPixel), "City Builder 2");
		text->setFillColor(sf::Color::Red);
		text->setOrigin(text->getGlobalBounds().size / 2.f);
		text->setScale(sf::Vector2f(2.f, 2.f));
		text->setPosition(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 15.f));

		sound = sf::Sound(api::general::resource_manager::Sound(api::sound::ResourceSound::Sound::kMusicBg));
		sound->setLooping(true);
		sound->setPitch(0.5f);
		sound->play();

		//button_manager.Setup(&tilemap);

		CreateTilemap();
		tilemap.clicked_tile_ = [](api::graphics::Tile& tile)
		{
			building_manager.AddBuilding(tile, build);
		};

		#if DEBUG_ENABLE
		button_generator.Setup(sf::Vector2f(window.getSize().x - 100, 30), sf::Vector2f(150.f, 25.f), "Generate");
		button_add_npc.Setup(sf::Vector2f(window.getSize().x - 100, 60), sf::Vector2f(150.f, 25.f), "Add Npc");
		button_remove_last_npc.Setup(sf::Vector2f(window.getSize().x - 100, 90), sf::Vector2f(150.f, 25.f), "Remove Last Npc");
		button_remove_all_npc.Setup(sf::Vector2f(window.getSize().x - 100, 120), sf::Vector2f(150.f, 25.f), "Remove All Npc");
		#endif
	}

	void Run()
	{
		Setup();
		while(window.isOpen())
		{
			delta_time = clock.restart().asSeconds();

			while(const std::optional event = window.pollEvent())
			{
				if(event->is<sf::Event::Closed>()) window.close();

				#if DEBUG_ENABLE
				if(button_generator.ActivateButton(*event, window)) tilemap.InitMap();
				if(button_add_npc.ActivateButton(*event, window)) npc_manager.AddNpc();
				if(button_remove_last_npc.ActivateButton(*event, window)) npc_manager.RemoveLastNpc();
				if(button_remove_all_npc.ActivateButton(*event, window)) npc_manager.RemoveAllNpc();
				#endif
			}

			npc_manager.Update(delta_time, tilemap);

			tilemap.HandleEvent(window, window.getView());

			window.clear();
			window.draw(tilemap);
			window.draw(npc_manager);
			window.draw(*text);

			#if DEBUG_ENABLE
			window.draw(button_generator);
			window.draw(button_add_npc);
			window.draw(button_remove_last_npc);
			window.draw(button_remove_all_npc);
			#endif

			window.display();

			#if TRACY_ENABLE
			FrameMark();
			#endif
		}
	}
}
