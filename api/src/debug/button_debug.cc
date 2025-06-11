#include "debug/button_debug.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "general/resource_manager.h"

namespace api::debug
{
	void ButtonDebug::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(button_, states);
		target.draw(*text_, states);
	}

	void ButtonDebug::Setup(const sf::Vector2f position, const sf::Vector2f size, std::string name_button)
	{
		text_ = sf::Text(general::resource_manager::Font(graphics::ResourceFont::Font::kPixel));
		text_->setString(name_button);
		text_->setOrigin(sf::Vector2f(text_->getGlobalBounds().position.x + text_->getGlobalBounds().size.x / 2.f,
		                              text_->getGlobalBounds().position.y + text_->getGlobalBounds().size.y / 2.f));
		button_.setSize(size);
		button_.setFillColor(sf::Color::Blue);
		button_.setOrigin(button_.getGlobalBounds().size / 2.f);
		button_.setPosition(position);
		text_->setScale(sf::Vector2f(button_.getSize().x / text_->getGlobalBounds().size.x * 0.8f,
		                             button_.getSize().y / text_->getGlobalBounds().size.y * 0.8f));
		text_->setPosition(button_.getPosition());
		scale_text_ = text_->getScale();
	}

	bool ButtonDebug::ActivateButton(const sf::Event& event, const sf::RenderWindow& window)
	{
		const sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		const sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
		if(button_.getGlobalBounds().contains(worldPos))
		{
			text_->setFillColor(sf::Color::Green);
			button_.setScale(sf::Vector2f(0.9f,0.9f));
			text_->setScale(sf::Vector2f(scale_text_.x * 0.9f, scale_text_.y * 0.9f));
		}
		else
		{
			text_->setFillColor(sf::Color::White);
			button_.setScale(sf::Vector2f(1.f,1.f));
			text_->setScale(sf::Vector2f(scale_text_.x * 1.f, scale_text_.y * 1.f));

		}

		if (const auto* mouseButtonEvent = event.getIf<sf::Event::MouseButtonPressed>())
		{
			if (mouseButtonEvent->button == sf::Mouse::Button::Left)
			{
				if(const sf::Vector2f worldPosClick = window.mapPixelToCoords(mouseButtonEvent->position); button_.getGlobalBounds().contains(worldPosClick))
				{
					text_->setFillColor(sf::Color::Red);
					return true;
				}
			}
		}

		return false;
	}
}
