#ifndef API_DEBUG_BUTTON_GENERATOR_H
#define API_DEBUG_BUTTON_GENERATOR_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace api::debug
{
	class ButtonGenerator final : public sf::Drawable
	{
	private:
		sf::RectangleShape button_;
		std::optional<sf::Text> text_;
	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		void Setup(sf::Vector2f position, sf::Vector2f size);
	};
}

#endif //API_DEBUG_BUTTON_GENERATOR_H
