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
		std::array<sf::SoundBuffer, static_cast<int>(Sound::kMax)> sounds_;

		sf::SoundBuffer blank_sound_;

		void LoadAllSounds();
	};
}

#endif //API_SOUND_RESOURCE_SOUND_H
