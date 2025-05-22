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
	ZoneScopedN("Get Sound");
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
	ZoneScopedN("Load All Sound");
	#endif
	blank_sound_ = sf::SoundBuffer();

	if(!sounds_.at(static_cast<int>(Sound::kMusicBG)).loadFromFile("resources/sound/music_bg.ogg"))
	{
		std::cout << "Error loading music bg sound" << std::endl;
	}
}
