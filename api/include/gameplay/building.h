#ifndef API_GAMEPLAY_BUILDING_H
#define API_GAMEPLAY_BUILDING_H

#include <SFML/Graphics.hpp>

namespace api::gameplay
{
    // Enum defining different types of buildings
    enum class Build
    {
        kHome,
        kLumberjack,
        kNothing
    };

    // Class representing a Building that inherits from sf::Drawable
    class Building final : public sf::Drawable {
    public:
        // Constructor to initialize a Building object
        Building(float x, float y, Build build);

        // Function to retrieve the position of the building
        sf::Vector2f Position() const { return position_; }

    protected:
        // Overridden draw function from sf::Drawable to draw the building
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        std::optional<sf::Sprite> shape_;      // Sprite representing the visual shape of the building
        sf::Vector2f position_; // Position of the building
    };
}

#endif //API_GAMEPLAY_BUILDING_H
