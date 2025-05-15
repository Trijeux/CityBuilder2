#ifndef API_GRAPHICS_RESOURCE_SPRIT_H
#define API_GRAPHICS_RESOURCE_SPRIT_H

#include <array>
#include <SFML/Graphics/Texture.hpp>

class ResourceSprit
{
public:
	enum class Texture
	{
		kGround,
		kStone,
		kForest,
		kMax
	};

	void Setup();

	sf::Texture& GetTexture(Texture resource_id);
protected:
private:
	std::array<sf::Texture, static_cast<int>(Texture::kMax)> textures_;

	sf::Texture blank_texture_;

	void LoadAllTextures();
};

#endif //API_GRAPHICS_RESOURCE_SPRIT_H
