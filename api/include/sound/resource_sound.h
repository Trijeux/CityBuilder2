#ifndef API_SOUND_RESOURCE_SOUND_H
#define API_SOUND_RESOURCE_SOUND_H

#include <array>

#include <SFML/Audio/SoundBuffer.hpp>

namespace api::sound
{
	class ResourceSound
	{
	public:
		enum class Sound
		{
			kMusicBg,
			kMax
		};

		void Setup();

		sf::SoundBuffer& sound(Sound resource_id);
	protected:
	private:
		const std::array<std::string, static_cast<int>(Sound::kMax)> names_sound_
			{
				"music_bg"
			};

		std::string path_ = "resources/sound/";

		std::array<sf::SoundBuffer, static_cast<int>(Sound::kMax)> sounds_;

		sf::SoundBuffer blank_sound_;

		void LoadAllSounds();
	};
}

#endif //API_SOUND_RESOURCE_SOUND_H
