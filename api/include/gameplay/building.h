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

        Build type() const { return type_; }

        // Function to retrieve the position of the building
        sf::Vector2f position() const { return position_; }

        bool is_occupied() const { return is_occupied_; }

        std::vector<sf::Vector2f> neighbor() const { return neighbor_; }
    protected:
        // Overridden draw function from sf::Drawable to draw the building
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        std::vector<sf::Vector2f> neighbor_;
        sf::RectangleShape detection_zone_;
        Build type_ = Build::kNothing;
        std::optional<sf::Sprite> sprite_;      // Sprite representing the visual shape of the building
        sf::Vector2f position_; // Position of the building
        bool is_occupied_ = false;
        // 5 = nombre de tiles en largeur et en longeur (5*5)
        float numbers_tiles_ = 5.f;

        void CreateNeighbor(const sf::Vector2f& center_pos, int radius, float tile_size);
    };
}

#endif //API_GAMEPLAY_BUILDING_H