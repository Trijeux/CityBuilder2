#include "graphics/resource_font.h"
#include "graphics/resource_sprit.h"
#include "sound/resource_sound.h"

namespace api::general::resource_manager
{
	namespace
	{
		graphics::ResourceSprit resource_sprit;
		sound::ResourceSound resource_sound;
		graphics::ResourceFont resource_font;
	}

	void Setup()
	{
		resource_sprit.Setup();
		resource_sound.Setup();
		resource_font.Setup();
	}

	sf::Texture& Sprit(const graphics::ResourceSprit::Texture resource_id)
	{
		return resource_sprit.GetTexture(resource_id);
	}

	sf::SoundBuffer& Sound(const sound::ResourceSound::Sound resource_id)
	{
		return resource_sound.GetSound(resource_id);
	}

	sf::Font& Font(const graphics::ResourceFont::Font resource_id)
	{
		return resource_font.GetFont(resource_id);
	}
}
