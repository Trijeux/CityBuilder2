#ifndef API_GRAPHICS_RESOURCE_SPRIT_H
#define API_GRAPHICS_RESOURCE_SPRIT_H

#include <array>

#include <SFML/Graphics/Texture.hpp>

namespace api::graphics
{
	class ResourceSprit
	{
	public:
		enum class Texture
		{
			kGround, kStone, kForest, kNpc, kButton,
			kHome, kLumberjack, kQuarry, kIconWood,
			kIconStone, kIconFood, kMax
		};

		void Setup();

		sf::Texture& texture(Texture resource_id);
	protected:
	private:
		const std::array<std::string, static_cast<int>(Texture::kMax)> names_textures_
					{
						"ground", "stone", "forest", "npc",
						"button", "home", "lumberjack","quarry", "wood_icon",
						"stone_icon", "food"
					};

		std::array<sf::Texture, static_cast<int>(Texture::kMax)> textures_;

		std::string path_ = "resources/sprite/";

		sf::Texture blank_texture_;

		void LoadAllTextures();
	};
}

#endif //API_GRAPHICS_RESOURCE_SPRIT_H
