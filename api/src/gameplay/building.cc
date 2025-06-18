#include "gameplay/building.h"// Include header file for Building class

#include "general/resource_manager.h"

api::gameplay::Building::Building(const float x, const float y, const Build build)
{
    // Constructor: Initializes a Building object with specified position (x, y) and type (build)

    switch (build)
    {
    case Build::kHome:
        // If building type is home, set its texture to the corresponding texture from ResourceManager
        shape_ = sf::Sprite(general::resource_manager::texture(graphics::ResourceSprit::Texture::kHome));
        break;
    case Build::kLumberjack:
        // If building type is mine, set its texture to the corresponding texture from ResourceManager
        shape_ = sf::Sprite(general::resource_manager::texture(graphics::ResourceSprit::Texture::kLumberjack));
        break;
    default: ;
    }
    // Set the position of the building
    position_ = sf::Vector2f(x, y);
    shape_ -> setPosition(position_); // Set position of the sprite shape
}

void api::gameplay::Building::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
    // Draw method: Renders the building on the specified render target
    target.draw(*shape_, states); // Draw the building's sprite shape on the render target
}
