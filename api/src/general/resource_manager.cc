#include "graphics/resource_font.h"
#include "graphics/resource_sprit.h"
#include "sound/resource_sound.h"

namespace api::general::ResourceManager
{
	namespace
	{
		graphics::ResourceSprit resource_sprit_;
		sound::ResourceSound resource_sound_;
		graphics::ResourceFont resource_font_;
	}

	void Setup()
	{
		resource_sprit_.Setup();
		resource_sound_.Setup();
		resource_font_.Setup();
	}

	sf::Texture& Sprit(const graphics::ResourceSprit::Texture resource_id)
	{
		return resource_sprit_.GetTexture(resource_id);
	}

	sf::SoundBuffer& Sound(const sound::ResourceSound::Sound resource_id)
	{
		return resource_sound_.GetSound(resource_id);
	}

	sf::Font& Font(const graphics::ResourceFont::Font resource_id)
	{
		return resource_font_.GetFont(resource_id);
	}
}
