#ifndef RESOURCE_FONT_H
#define RESOURCE_FONT_H

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

		sf::Font& GetFont(Font resource_id);
	protected:
	private:
		std::array<sf::Font, static_cast<int>(Font::kMax)> fonts_;

		sf::Font blank_font_;

		void LoadAllFonts();
	};
}

#endif //RESOURCE_FONT_H
