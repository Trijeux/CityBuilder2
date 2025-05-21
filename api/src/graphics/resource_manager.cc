#include "graphics/resource_sprit.h"

namespace api::graphics::ResourceManager
{
	namespace
	{
		api::graphics::ResourceSprit resource_sprit_;
	}

	void Setup()
	{
		resource_sprit_.Setup();
	}

	sf::Texture& Sprit(const api::graphics::ResourceSprit::Texture resource_id)
	{
		return resource_sprit_.GetTexture(resource_id);
	}
}
