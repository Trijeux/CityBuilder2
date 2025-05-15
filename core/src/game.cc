#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <tracy/Tracy.hpp>

namespace Game
{
	namespace
	{
		sf::RenderWindow          window_;
		sf::Texture               texture_("ressources/image_test.jpg");
		std::optional<sf::Sprite> sprite_;
		sf::Music                 music_("ressources/music_test.ogg");
		sf::SoundBuffer           buffer_("ressources/song_test.ogg");
		std::optional<sf::Sound>  sound_;
		sf::Font                  font_("ressources/font_test.ttf");
		std::optional<sf::Text>   text_;
	}


	static void Setup()
	{
		ZoneScopedN("Setup");
		sprite_ = sf::Sprite(texture_);

		window_.create(sf::VideoMode(sf::Vector2u(sprite_->getGlobalBounds().size.x, sprite_->getGlobalBounds().size.y)), "SFML works!");

		music_.setLooping(true);
		music_.play();

		sound_ = sf::Sound(buffer_);

		text_ = sf::Text(font_);
		text_->setString("Hello World");
		text_->setCharacterSize(24);
		text_->setFillColor(sf::Color::White);
		text_->setOrigin(sf::Vector2f(text_->getGlobalBounds().size.x / 2, text_->getGlobalBounds().size.y / 2));
		text_->setPosition(sf::Vector2f(window_.getSize().x / 2, window_.getSize().y / 2));
	}

	void Run()
	{
		Setup();
		while(window_.isOpen())
		{
			ZoneScopedN("Run");

			if(isKeyPressed(sf::Keyboard::Key::Space))
			{
				if(sound_->getStatus() == sf::Sound::Status::Stopped)
				{
					sound_->play();
				}
			}

			while(const std::optional event = window_.pollEvent())
			{
				if(event->is<sf::Event::Closed>()) window_.close();
			}

			window_.clear();
			window_.draw(*sprite_);
			window_.draw(*text_);
			window_.display();
		}
	}
}