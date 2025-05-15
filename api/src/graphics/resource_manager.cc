#include "graphics/resource_sprit.h"

namespace ResourceManager
{
	namespace
	{
		ResourceSprit resource_sprit_;
	}

	void Setup()
	{
		resource_sprit_.Setup();
	}

	sf::Texture& Sprit(const ResourceSprit::Texture resource_id)
	{
		return resource_sprit_.GetTexture(resource_id);
	}
}
