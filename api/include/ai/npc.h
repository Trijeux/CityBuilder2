#ifndef API_AI_NPC_H
#define API_AI_NPC_H

#include <SFML/Graphics.hpp>

#include "ai/bt_node.h"
#include "ai/bt_selector.h"

class Npc : public sf::Drawable
{
	std::optional<sf::Sprite> sprite_;

	std::unique_ptr<core::ai::Node> root_;
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	void Setup();
	void Update();

	core::ai::Status Move();

	int  hunger_ = 0;
	bool resource_available_ = true;
};

#endif //API_AI_NPC_H
