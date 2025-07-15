#include "ui/ui_button.h"  // Include the UiButton header file

#include <iostream>

#include "general/resource_manager.h"
#include "graphics/resource_font.h"

// Draw function to render the UiButton
void api::ui::UiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform(); // Apply the button's transform to the render states
	target.draw(*sprite_, states); // Draw the button's sprite
	target.draw(*button_text_, states);
	if(have_prize_wood_)
	{
		target.draw(*have_prize_wood_text_, states);
		target.draw(*have_prize_wood_sprite_, states);
	}
	if(have_prize_stone_)
	{
		target.draw(*have_prize_stone_text_, states);
		target.draw(*have_prize_stone_sprite_, states);
	}
}

// Check if the mouse click event is inside the button's bounds
bool api::ui::UiButton::ContainsMouse(const sf::Event& event, const sf::RenderWindow& window)
{
	const sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
	auto               pixel_pos_in_float = sf::Vector2f(pixel_pos);
	if(const auto* mouse_button_pressed = event.getIf<sf::Event::MouseButtonPressed>())
	{
		// Calculate mouse position relative to button's position
		pixel_pos_in_float.x = static_cast<float>(mouse_button_pressed->position.x) - getPosition().x;
		pixel_pos_in_float.y = static_cast<float>(mouse_button_pressed->position.y) - getPosition().y;
	}

	if(event.getIf<sf::Event::MouseButtonReleased>() && was_pressed_)
	{
		was_pressed_ = false;
		return true;
	}

	// Check if the mouse position is inside the button's global bounds
	if(sprite_->getGlobalBounds().contains(pixel_pos_in_float))
	{
		was_pressed_ = true;
		return true;
	}
	return false;
}

// Handle events for the UiButton
bool api::ui::UiButton::HandleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
	// Check for mouse button released event
	if(const auto* mouse_button_pressed = event.getIf<sf::Event::MouseButtonReleased>())
	{
		// If the mouse click is inside the button
		if(ContainsMouse(event, window))
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
		if(ContainsMouse(event, window))
		{
			// Scale down the button slightly and set build_on flag
			setScale(sf::Vector2f(0.9f * getScale().x, 0.9f * getScale().y));
			build_on_ = true;
		}
	}

	const sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
	auto               pixel_pos_in_float = sf::Vector2f(pixel_pos) - getPosition();
	if(sprite_->getGlobalBounds().contains(pixel_pos_in_float))
	{
		button_text_->setFillColor(sf::Color::Green);
		return true;
	}
	button_text_->setFillColor(color_text_);
	return false;
}

void api::ui::UiButton::CreateButton(const sf::Vector2f pos, const std::string&             text, const int character_size, const sf::Color color_text,
                                     const std::string& have_prize_wood, const std::string& have_prize_stone)
{
	button_text_ = sf::Text(api::general::resource_manager::font(api::graphics::ResourceFont::Font::kPixel)); // Set the font for the button text
	button_text_->setString(text); // Set the text content
	setPosition(pos); // Set the button's position
	button_text_->setCharacterSize(character_size); // Set the character size of the text
	button_text_->setFillColor(color_text); // Set the color of the text
	color_text_ = color_text;

	sprite_ = sf::Sprite(api::general::resource_manager::texture(api::graphics::ResourceSprit::Texture::kButton)); // Set the texture for the button's sprite
	sprite_->setOrigin(sf::Vector2f(sprite_->getGlobalBounds().size.x / 2.0f, sprite_->getGlobalBounds().size.y / 2.0f));
	// Set the origin of the sprite to its center
	sprite_->setColor(sf::Color::White); // Set the color of the sprite

	// Set the origin of the text to its center
	const sf::FloatRect text_rect = button_text_->getLocalBounds();
	const sf::FloatRect shape_rect = sprite_->getGlobalBounds();
	button_text_->setOrigin(sf::Vector2f(text_rect.position.x + text_rect.size.x / 2.0f, text_rect.position.y + text_rect.size.y / 2.0f));
	button_text_->setPosition(sf::Vector2f(shape_rect.position.x + shape_rect.size.x / 2.0f, shape_rect.position.y + shape_rect.size.y / 2.0f));


	if(have_prize_wood != "")
	{
		have_prize_wood_text_ = sf::Text(api::general::resource_manager::font(api::graphics::ResourceFont::Font::kPixel));
		// Set the font for the button text
		have_prize_wood_text_->setString(have_prize_wood);
		have_prize_wood_text_->setFillColor(sf::Color::Black);
		have_prize_wood_text_->setCharacterSize(character_size - 10);
		const sf::FloatRect text_prize_rect = have_prize_wood_text_->getLocalBounds();
		have_prize_wood_text_->setOrigin(sf::Vector2f(text_prize_rect.position.x + text_prize_rect.size.x / 2.0f,
		                                               text_prize_rect.position.y + text_prize_rect.size.y / 2.0f));
		have_prize_wood_sprite_ = sf::Sprite(api::general::resource_manager::texture(api::graphics::ResourceSprit::Texture::kIconWood));
		have_prize_wood_sprite_->setOrigin(sf::Vector2f(have_prize_wood_sprite_->getGlobalBounds().size.x / 2.0f, have_prize_wood_sprite_->getGlobalBounds().size.y / 2.0f));
		if(have_prize_stone != "")
		{
			have_prize_wood_text_->setPosition(sf::Vector2f(shape_rect.position.x + shape_rect.size.x / 2.0f +15,
			                                                 shape_rect.position.y + shape_rect.size.y / 2.0f - 60));

			have_prize_wood_sprite_->setPosition(sf::Vector2f(shape_rect.position.x + shape_rect.size.x / 2.0f -15,
			                                                  shape_rect.position.y + shape_rect.size.y / 2.0f - 60));
		}
		else
		{
			have_prize_wood_text_->setPosition(sf::Vector2f(shape_rect.position.x + shape_rect.size.x / 2.0f +15,
			                                                 shape_rect.position.y + shape_rect.size.y / 2.0f - 40));

			have_prize_wood_sprite_->setPosition(sf::Vector2f(shape_rect.position.x + shape_rect.size.x / 2.0f -15,
															  shape_rect.position.y + shape_rect.size.y / 2.0f - 40));
		}
		have_prize_wood_ = true;
	}

	if(have_prize_stone != "")
	{
		have_prize_stone_text_ = sf::Text(api::general::resource_manager::font(api::graphics::ResourceFont::Font::kPixel));
		// Set the font for the button text
		have_prize_stone_text_->setString(have_prize_stone);
		have_prize_stone_text_->setFillColor(sf::Color::Black);
		have_prize_stone_text_->setCharacterSize(character_size - 10);
		const sf::FloatRect text_prize_rect = have_prize_stone_text_->getLocalBounds();
		have_prize_stone_text_->setOrigin(sf::Vector2f(text_prize_rect.position.x + text_prize_rect.size.x / 2.0f,
		                                               text_prize_rect.position.y + text_prize_rect.size.y / 2.0f));
		have_prize_stone_sprite_ = sf::Sprite(api::general::resource_manager::texture(api::graphics::ResourceSprit::Texture::kIconStone));
		have_prize_stone_sprite_->setOrigin(sf::Vector2f(have_prize_stone_sprite_->getGlobalBounds().size.x / 2.0f, have_prize_stone_sprite_->getGlobalBounds().size.y / 2.0f));
		have_prize_stone_text_->setPosition(
			sf::Vector2f(shape_rect.position.x + shape_rect.size.x / 2.0f +15, shape_rect.position.y + shape_rect.size.y / 2.0f - 40));

		have_prize_stone_sprite_->setPosition(sf::Vector2f(shape_rect.position.x + shape_rect.size.x / 2.0f -15,
															  shape_rect.position.y + shape_rect.size.y / 2.0f - 40));
		have_prize_stone_ = true;
	}

	build_on_ = false; // Initialize the build_on flag
}

void api::ui::UiButton::CreateButton(const sf::Vector2f pos, const std::string& text, const int character_size, const sf::Color color_text)
{
	CreateButton(pos, text, character_size, color_text, "", "");
}

void api::ui::UiButton::CreateButton(const sf::Vector2f pos, const std::string& text, const int character_size, const sf::Color color_text,
                                     const std::string& have_prize_, const char SorW)
{
	if(SorW == 'S' || SorW == 's') CreateButton(pos, text, character_size, color_text, "", have_prize_);
	else if(SorW == 'W' || SorW == 'w') CreateButton(pos, text, character_size, color_text, have_prize_, "");
	else CreateButton(pos, text, character_size, color_text, "Error", "Error");
}
