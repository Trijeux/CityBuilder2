#include "debug/button_generator.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "general/resource_manager.h"

namespace api::debug
{
	void ButtonGenerator::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(button_, states);
		target.draw(*text_, states);
	}

	void ButtonGenerator::Setup(const sf::Vector2f position, const sf::Vector2f size)
	{
		text_ = sf::Text(general::ResourceManager::Font(graphics::ResourceFont::Font::kPixel));
		text_->setString("Generate");
		text_->setOrigin(sf::Vector2f(text_->getGlobalBounds().position.x + text_->getGlobalBounds().size.x / 2.f,
		                              text_->getGlobalBounds().position.y + text_->getGlobalBounds().size.y / 2.f));
		button_.setSize(size);
		button_.setFillColor(sf::Color::Blue);
		button_.setOrigin(button_.getGlobalBounds().size / 2.f);
		button_.setPosition(position);
		text_->setScale(sf::Vector2f(button_.getSize().x / text_->getGlobalBounds().size.x * 0.8f,
		                             button_.getSize().y / text_->getGlobalBounds().size.y * 0.8f));
		text_->setPosition(button_.getPosition());
	}
}
