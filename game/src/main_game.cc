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
#include "gameplay/resource.h"
#include "general/resource_manager.h"
#include "graphics/tilemap.h"
#include "ui/ui_button.h"

namespace game::main_game
{
	namespace
	{
		sf::Clock                            clock;
		sf::RenderWindow                     window;
		std::optional<sf::Sound>             sound;
		std::optional<sf::Text>              text;
		api::graphics::TileMap               tilemap;
		api::ai::NpcManager                  npc_manager;
		api::gameplay::BuildingManager       building_manager;
		auto                                 build = api::gameplay::Build::kHome;
		std::vector<api::gameplay::Building> work = {};

		bool in_button = false;
		bool build_active = false;

		api::ui::UiButton btn_activate_building;
		api::ui::UiButton btn_building_home;
		api::ui::UiButton btn_building_lumberjack;
		api::ui::UiButton btn_building_quarry;

		Resource resource;

		float delta_time = 0;

		#if DEBUG_ENABLE
		api::debug::ButtonDebug button_generator;
		//api::debug::ButtonDebug button_add_npc;
		//api::debug::ButtonDebug button_remove_last_npc;
		//api::debug::ButtonDebug button_remove_all_npc;
		#endif
	}

	void CreateButtonActiveBuilding(const int x, const int y, const std::string& text, const int size, const sf::Color color_text)
	{
		btn_activate_building.CreateButton(sf::Vector2f(x, y), text, size, color_text);
		btn_activate_building.set_scale({0.8f, 0.8f});
		btn_activate_building.call_back_ = []()
		{
			building_manager.build(window);
			if(build_active == false)
			{
				build_active = true;
			}
			else if(build_active == true)
			{
				build_active = false;
			}
		};
	}

	void CreateButtonBuildHome(const int x, const int y, const std::string& text, const int size, const sf::Color color_text)
	{
		btn_building_home.CreateButton(sf::Vector2f(x, y), text, size, color_text, "Wood x50");
		btn_building_home.set_scale({0.8f, 0.8f});
		btn_building_home.call_back_ = []()
		{
			btn_building_home.set_scale({0.8f, 0.8f});
			if (resource.wood_amount() >= 50)
			{
				build = api::gameplay::Build::kHome;
			}
			else
			{
				build = api::gameplay::Build::kNothing;
			}
			btn_building_lumberjack.build_on_ = false;
			btn_building_lumberjack.set_scale({0.5f, 0.5f});
			btn_building_quarry.build_on_ = false;
			btn_building_quarry.set_scale({0.5f, 0.5f});
		};
	}

	void CreateButtonBuildLumberjack(const int x, const int y, const std::string& text, const int size, const sf::Color color_text)
	{
		btn_building_lumberjack.CreateButton(sf::Vector2f(x, y), text, size, color_text, "Wood x50");
		btn_building_lumberjack.set_scale({0.5f, 0.5f});
		btn_building_lumberjack.call_back_ = []()
		{
			btn_building_lumberjack.set_scale({0.8f, 0.8f});
			if (resource.wood_amount() >= 50)
			{
				build = api::gameplay::Build::kLumberjack;
			}
			else
			{
				build = api::gameplay::Build::kNothing;
			}
			btn_building_home.build_on_ = false;
			btn_building_home.set_scale({0.5f, 0.5f});
			btn_building_quarry.build_on_ = false;
			btn_building_quarry.set_scale({0.5f, 0.5f});
		};
	}

	void CreateButtonBuildQuarry(const int x, const int y, const std::string& text, const int size, const sf::Color color_text)
	{
		btn_building_quarry.CreateButton(sf::Vector2f(x, y), text, size, color_text, "Wood x150 \n Stone x50");
		btn_building_quarry.set_scale({0.5f, 0.5f});
		btn_building_quarry.call_back_ = []()
		{
			btn_building_quarry.set_scale({0.8f, 0.8f});
			if (resource.wood_amount() >= 150 && resource.stone_amount() >= 50)
			{
				build = api::gameplay::Build::kQuarry;
			}
			else
			{
				build = api::gameplay::Build::kNothing;
			}
			btn_building_lumberjack.build_on_ = false;
			btn_building_lumberjack.set_scale({0.5f, 0.5f});
			btn_building_home.build_on_ = false;
			btn_building_home.set_scale({0.5f, 0.5f});
		};
	}

	void CreateTilemap()
	{
		tilemap.Setup(sf::Vector2u(window.getSize().x / tilemap.size_sprit().x, window.getSize().y / tilemap.size_sprit().y));
		building_manager.ClearMap();
		tilemap.InitMap();
	}

	static void Setup()
	{
		#if TRACY_ENABLE
		ZoneNamedN(GameSetup, "Game Setup", true);
		#endif
		window.create(sf::VideoMode({1600, 800}), "Game");
		api::general::resource_manager::Setup();
		resource.Setup();
		text = sf::Text(api::general::resource_manager::font(api::graphics::ResourceFont::Font::kPixel), "City Builder 2");
		text->setFillColor(sf::Color::Red);
		text->setOrigin(text->getGlobalBounds().size / 2.f);
		text->setScale(sf::Vector2f(2.f, 2.f));
		text->setPosition(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 15.f));

		sound = sf::Sound(api::general::resource_manager::sound(api::sound::ResourceSound::Sound::kMusicBg));
		sound->setLooping(true);
		sound->setPitch(0.5f);
		sound->play();

		npc_manager.Setup(&tilemap, &resource);

		CreateTilemap();
		tilemap.clicked_tile_ = [](api::graphics::Tile& tile)
		{
			if(tile.type() == api::graphics::Tile::TileType::kGround)
			{
				auto home = building_manager.AddBuilding(tile, build);
				switch(build)
				{
				case api::gameplay::Build::kHome:
				case api::gameplay::Build::kLumberjack:
					resource.sub_wood(50);
					break;
				case api::gameplay::Build::kQuarry:
					resource.sub_wood(150);
					resource.sub_stone(50);
					break;
				}
				if(build == api::gameplay::Build::kHome)
				{
					if(home->type() == api::gameplay::Build::kHome)
					{
						npc_manager.AddNpc(std::move(*home));
					}
				}
				build = api::gameplay::Build::kNothing;
				btn_building_home.build_on_ = false;
				btn_building_home.set_scale({0.5f, 0.5f});
				btn_building_lumberjack.build_on_ = false;
				btn_building_lumberjack.set_scale({0.5f, 0.5f});
				btn_building_quarry.build_on_ = false;
				btn_building_quarry.set_scale({0.5f, 0.5f});
			}
		};

		npc_manager.set_building_manager(&building_manager);

		#if DEBUG_ENABLE
		button_generator.Setup(sf::Vector2f(window.getSize().x - 100, 30), sf::Vector2f(150.f, 25.f), "Generate");
		//button_add_npc.Setup(sf::Vector2f(window.getSize().x - 100, 60), sf::Vector2f(150.f, 25.f), "Add Npc");
		//button_remove_last_npc.Setup(sf::Vector2f(window.getSize().x - 100, 90), sf::Vector2f(150.f, 25.f), "Remove Last Npc");
		//button_remove_all_npc.Setup(sf::Vector2f(window.getSize().x - 100, 120), sf::Vector2f(150.f, 25.f), "Remove All Npc");
		#endif

		CreateButtonActiveBuilding(100, 760, "Build", 20, sf::Color::Yellow);
		CreateButtonBuildHome(100, 700, "Home", 20, sf::Color::Yellow);
		CreateButtonBuildLumberjack(250, 700, "Lumberjack", 20, sf::Color::Yellow);
		CreateButtonBuildQuarry(400, 700, "Quarry", 20, sf::Color::Yellow);
	}

	bool ButtonEvent(const sf::Event& event, const sf::RenderWindow& window)
	{
		bool in_button_return = btn_activate_building.HandleEvent(event, window);
		in_button_return |= btn_building_home.HandleEvent(event, window);
		in_button_return |= btn_building_lumberjack.HandleEvent(event, window);
		in_button_return |= btn_building_quarry.HandleEvent(event, window);
		return in_button_return;
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
				if(button_generator.ActivateButton(*event, window))
				{
					tilemap.InitMap();
					building_manager.ClearMap();
				}
				//if(button_add_npc.ActivateButton(*event, window)) npc_manager.AddNpc();
				//if(button_remove_last_npc.ActivateButton(*event, window)) npc_manager.RemoveLastNpc();
				//if(button_remove_all_npc.ActivateButton(*event, window)) npc_manager.RemoveAllNpc();
				#endif

				in_button = ButtonEvent(*event, window);
			}

			resource.Update();
			npc_manager.Update(delta_time, tilemap);
			if(!in_button && build_active)
			{
				tilemap.HandleEvent(window, window.getView());
				if(build == api::gameplay::Build::kNothing)
				{
					tilemap.set_color_outilne(sf::Color::Red);
				}
				else
				{
					tilemap.set_color_outilne(sf::Color::Green);
				}
			}

			//tilemap.Update(delta_time);

			window.clear();
			window.draw(tilemap);
			window.draw(building_manager);
			window.draw(npc_manager);
			window.draw(*text);


			window.draw(resource);
			window.draw(btn_activate_building);
			if(build_active)
			{
				window.draw(btn_building_home);
				window.draw(btn_building_lumberjack);
				window.draw(btn_building_quarry);
			}

			#if DEBUG_ENABLE
			window.draw(button_generator);
			//window.draw(button_add_npc);
			//window.draw(button_remove_last_npc);
			//window.draw(button_remove_all_npc);
			#endif

			window.display();

			#if TRACY_ENABLE
			FrameMark;
			#endif
		}
	}
}
