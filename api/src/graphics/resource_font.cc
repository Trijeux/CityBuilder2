#include "graphics/resource_font.h"

#include <iostream>

#if TRACY_ENABLE
	#include <tracy/Tracy.hpp>
#endif

void api::graphics::ResourceFont::Setup()
{
	LoadAllFonts();
}

sf::Font& api::graphics::ResourceFont::font(Font resource_id)
{
	#if TRACY_ENABLE
	ZoneNamedN(GetFont, "Get Font", true);
	#endif
	if(static_cast<int>(resource_id) < fonts_.size())
	{
		return fonts_.at(static_cast<int>(resource_id));
	}
	return blank_font_;
}

void api::graphics::ResourceFont::LoadAllFonts()
{
	#if TRACY_ENABLE
	ZoneNamedN(LoadAllFont, "Load All Font", true);
	#endif
	blank_font_ = sf::Font();

	if(!fonts_.at(static_cast<int>(Font::kPixel)).openFromFile("resources/font/pixel.ttf"))
	{
		std::cout << "Error loading pixel font" << std::endl;
	}
}
