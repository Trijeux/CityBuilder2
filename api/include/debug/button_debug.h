#ifndef API_DEBUG_BUTTON_GENERATOR_H
#define API_DEBUG_BUTTON_GENERATOR_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace api::debug
{
	class ButtonDebug final : public sf::Drawable
	{
	private:
		sf::RectangleShape button_;
		std::optional<sf::Text> text_;
		sf::Vector2f scale_text_;
	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		void Setup(sf::Vector2f position, sf::Vector2f size, std::string name_button);
		bool ActivateButton(const sf::Event& event, const sf::RenderWindow& window);
	};
}

#endif //API_DEBUG_BUTTON_GENERATOR_H
