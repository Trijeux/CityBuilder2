#include "sound/resource_sound.h"

#include <iostream>

#if TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif

void api::sound::ResourceSound::Setup()
{
	LoadAllSounds();
}

sf::SoundBuffer& api::sound::ResourceSound::GetSound(Sound resource_id)
{
	#if TRACY_ENABLE
	ZoneNamedN(GetSound, "Get Sound", true);
	#endif
	if(static_cast<int>(resource_id) < sounds_.size())
	{
		return sounds_.at(static_cast<int>(resource_id));
	}
	return blank_sound_;
}

void api::sound::ResourceSound::LoadAllSounds()
{
	#if TRACY_ENABLE
	ZoneNamedN(LoadAllSound, "LoadAllSound", true);
	#endif
	blank_sound_ = sf::SoundBuffer();

	if(!sounds_.at(static_cast<int>(Sound::kMusicBg)).loadFromFile("resources/sound/music_bg.ogg"))
	{
		std::cout << "Error loading music bg sound" << std::endl;
	}
}
