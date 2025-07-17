#ifndef API_GRAPHICS_RESOURCE_FONT_H
#define API_GRAPHICS_RESOURCE_FONT_H

#include <array>

#include <SFML/Graphics/Font.hpp>

namespace api::graphics
{
	class ResourceFont
	{
	public:
		enum class Font
		{
			kPixel,
			kMax
		};

		void Setup();

		sf::Font& font(Font resource_id);
	protected:
	private:
		const std::array<std::string, static_cast<int>(Font::kMax)> names_font_
			{
				"pixel"
			};

		std::string path_ = "resources/font/";

		std::array<sf::Font, static_cast<int>(Font::kMax)> fonts_;

		sf::Font blank_font_;

		void LoadAllFonts();
	};
}

#endif //API_GRAPHICS_RESOURCE_FONT_H
