#ifndef CORE_RESOURCE_MANAGER_H
#define CORE_RESOURCE_MANAGER_H

#include "resource_sprit.h"


namespace ResourceManager
{
	void Setup();
	sf::Texture& Sprit(ResourceSprit::Texture resource_id);
}

#endif //CORE_RESOURCE_MANAGER_H
