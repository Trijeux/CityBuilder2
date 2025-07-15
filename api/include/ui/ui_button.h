#ifndef API_UI_UI_BUTTON_H
#define API_UI_UI_BUTTON_H

#include <functional> // Include for std::function
#include <string> // Include for std::string
#include <SFML/Graphics.hpp> // Include SFML graphics library

namespace api::ui
{
    class UiButton final : public sf::Drawable, public sf::Transformable
    {
    private:
        bool was_pressed_ = false;// Font for the button text
        std::optional<sf::Sprite> sprite_; // Sprite for the button
        std::optional<sf::Text> button_text_; // Text displayed on the button// Texture for the button (not used in current implementation)
        sf::Color color_text_;

        // Private method to draw the button
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        bool ContainsMouse(const sf::Event& event, const sf::RenderWindow& window);

        // Private method to check if mouse cursor is within the button area

        bool have_prize_wood_ = false;
        bool have_prize_stone_ = false;
        std::optional<sf::Text> have_prize_wood_text_;
        std::optional<sf::Text> have_prize_stone_text_;
        std::optional<sf::Sprite> have_prize_wood_sprite_;
        std::optional<sf::Sprite> have_prize_stone_sprite_;

    public:
        // Public method to set the color of the button sprite
        void set_color_sprite(const sf::Color color) { sprite_->setColor(color); }

        void set_scale(const sf::Vector2f& scale) { sprite_->setScale(scale); button_text_->setScale(scale); }
        // Public method to handle SFML events related to the button


        bool HandleEvent(const sf::Event& event, const sf::RenderWindow& window);
        // Public method to create the button
        void CreateButton(sf::Vector2f pos, const std::string& text, int character_size, sf::Color color_text, const std::string& have_prize_wood, const std::string& have_prize_stone);
        void CreateButton(sf::Vector2f pos, const std::string& text, int character_size, sf::Color color_text);
        void CreateButton(sf::Vector2f pos, const std::string& text, int character_size, sf::Color color_text, const std::string& have_prize_, char SorW);

        // Public boolean indicating if building is on (purpose unclear from provided context)
        bool build_on_;

        // Public std::function callback for button click event
        std::function<void()> call_back_;
    };
}
#endif // API_UI_UI_BUTTON_H
