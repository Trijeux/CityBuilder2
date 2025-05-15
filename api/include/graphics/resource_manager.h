#ifndef API_GRAPHICS_RESOURCE_MANAGER_H
#define API_GRAPHICS_RESOURCE_MANAGER_H

#include "resource_sprit.h"


namespace ResourceManager
{
	void Setup();
	sf::Texture& Sprit(ResourceSprit::Texture resource_id);
}

#endif //API_GRAPHICS_RESOURCE_MANAGER_H
