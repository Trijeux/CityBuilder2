#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>

#include "ai/bt_node.h"
#include "ai/bt_selector.h"

using namespace core::ai::behaviour_tree;

class Npc : public sf::Drawable
{
	std::optional<sf::Sprite> sprite_;

	std::unique_ptr<Node> root_;
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	void Setup();
	void Update();

	Status Move();

	int  hunger_ = 0;
	bool resource_available_ = true;
};

#endif //NPC_H
