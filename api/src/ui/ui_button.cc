#include "ui/ui_button.h"  // Include the UiButton header file

#include <iostream>

#include "general/resource_manager.h"
#include "graphics/resource_font.h"

// Draw function to render the UiButton
void api::ui::UiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform(); // Apply the button's transform to the render states

	target.draw(*sprite_, states); // Draw the button's sprite
	target.draw(*button_text_, states); // Draw the button's text
}

// Check if the mouse click event is inside the button's bounds
bool api::ui::UiButton::ContainsMouse(const sf::Event& event) const
{
	float mouse_x = 0.f;
	float mouse_y = 0.f;
	if(const auto* mouse_button_pressed = event.getIf<sf::Event::MouseButtonPressed>())
	{
		// Calculate mouse position relative to button's position
		mouse_x = static_cast<float>(mouse_button_pressed->position.x) - getPosition().x;
		mouse_y = static_cast<float>(mouse_button_pressed->position.y) - getPosition().y;
	}

	// Check if the mouse position is inside the button's global bounds
	if(sprite_->getGlobalBounds().contains(sf::Vector2f(mouse_x, mouse_y)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Handle events for the UiButton
bool api::ui::UiButton::HandleEvent(const sf::Event& event)
{
	// Check for mouse button released event
	if(const auto* mouse_button_pressed = event.getIf<sf::Event::MouseButtonReleased>())
	{
		// If the mouse click is inside the button
		if(ContainsMouse(event))
		{
			// Scale down the button slightly
			setScale(sf::Vector2f(getScale().x / 0.9f, getScale().y / 0.9f));

			if(mouse_button_pressed->button == sf::Mouse::Button::Left)
			{
				if(call_back_)
				{
					call_back_();
				}

			}
		}
	}

	// Check for mouse button pressed event
	if(event.is<sf::Event::MouseButtonPressed>())
	{
		// If the mouse click is inside the button
		if(ContainsMouse(event))
		{
			// Scale down the button slightly and set build_on flag
			setScale(sf::Vector2f(0.9f * getScale().x, 0.9f * getScale().y));
			build_on_ = true;
		}
	}

	// Check if the mouse is currently inside the button
	if(ContainsMouse(event))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Create a new UiButton with specified parameters
void api::ui::UiButton::CreateButton(const sf::Vector2f pos, const std::string& text, const int character_size, const sf::Color color_text)
{
	button_text_ = sf::Text(api::general::resource_manager::Font(api::graphics::ResourceFont::Font::kPixel)); // Set the font for the button text
	button_text_->setString(text); // Set the text content
	setPosition(pos); // Set the button's position
	button_text_->setCharacterSize(character_size); // Set the character size of the text
	button_text_->setFillColor(color_text); // Set the color of the text

	sprite_ = sf::Sprite(api::general::resource_manager::Sprit(api::graphics::ResourceSprit::Texture::kButton)); // Set the texture for the button's sprite
	sprite_->setOrigin(sf::Vector2f(sprite_->getGlobalBounds().size.x / 2.0f, sprite_->getGlobalBounds().size.y / 2.0f));
	// Set the origin of the sprite to its center
	sprite_->setColor(sf::Color::White); // Set the color of the sprite

	// Set the origin of the text to its center
	const sf::FloatRect text_rect = button_text_->getLocalBounds();
	const sf::FloatRect shape_rect = sprite_->getGlobalBounds();
	button_text_->setOrigin(sf::Vector2f(text_rect.position.x + text_rect.size.x / 2.0f, text_rect.position.y + text_rect.size.y / 2.0f));
	button_text_->setPosition(sf::Vector2f(shape_rect.position.x + shape_rect.size.x / 2.0f, shape_rect.position.y + shape_rect.size.y / 2.0f));

	// Load the button's textur

	setScale(sf::Vector2f(1, 1)); // Set the initial scale of the button

	build_on_ = false; // Initialize the build_on flag
}
