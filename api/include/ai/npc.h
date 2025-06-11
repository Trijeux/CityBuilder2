#ifndef API_AI_NPC_H
#define API_AI_NPC_H

#include <SFML/Graphics.hpp>

#include "ai/bt_node.h"
#include "ai/bt_selector.h"
#include "motion/motor.h"
#include "motion/path.h"

namespace api::ai
{
	class Npc : public sf::Drawable
	{
		bool is_dead_ = false;

		std::optional<sf::Sprite> sprite_;

		std::unique_ptr<core::ai::Node> root_;

		std::vector<sf::Vector2f> points_;
		int                       index_point_ = 0;


		static constexpr float hunger_rate_ = 0.1f;
		static constexpr float moving_speed_ = 0.5f;

		motion::Motor motor_;

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:

		bool IsDead() const { return is_dead_; }

		void Setup(motion::Path& path);
		void Update(float dt);

		core::ai::Status Move();
		core::ai::Status Eat();

		void SetupBehaviourTree();

		float hunger_ = 0;
		bool  resource_available_ = true;
		bool  target_reachable_ = true;
		float target_distance_ = 20;
	};
}
#endif //API_AI_NPC_H
