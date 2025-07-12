#ifndef API_AI_NPC_H
#define API_AI_NPC_H

#include <SFML/Graphics.hpp>
#include <utility>

#include "ai/bt_node.h"
#include "ai/bt_selector.h"
#include "gameplay/building.h"
#include "gameplay/resource.h"
#include "graphics/tilemap.h"
#include "motion/motor.h"
#include "motion/path.h"

namespace api::ai
{
	enum class Job
	{
		kNothing,
		kWood,
		kStone
	};

	class Npc : public sf::Drawable
	{
		std::optional<gameplay::Building> home_;
		std::optional<gameplay::Building> work_;
		graphics::TileMap*                tile_map_ = nullptr;
		Resource*               resource_ = nullptr;
		float timer_add_resource_ = 0;
		float cool_down_add_resource_ = 5.f;

		int resource_number_ = 0;

		bool have_work_ = false;

		bool new_path_ = false;

		bool is_moving_ = false;

		bool is_dead_ = false;

		bool resource_good_ = false;

		bool is_working_ = false;

		std::optional<sf::Sprite> sprite_;

		std::unique_ptr<core::ai::Node> root_;

		motion::Path path_;
		int          index_point_ = 0;

		sf::Vector2f           objectif_;
		static constexpr float hunger_rate_ = 0.1f;
		static constexpr float moving_speed_ = 0.5f;

		motion::Motor motor_;

		Job job_ = Job::kNothing;

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:
		void have_new_path()
		{
			new_path_ = false;
		}

		bool have_work() const
		{
			return have_work_;
		}

		sf::Vector2f objectif() const
		{
			return objectif_;
		}

		sf::Vector2f Position() const
		{
			return sprite_->getPosition();
		}

		bool new_path() const
		{
			return new_path_;
		}

		bool is_dead() const
		{
			return is_dead_;
		}

		void             Setup(gameplay::Building building, graphics::TileMap* tile_map, Resource* resource);
		core::ai::Status CheckEat();
		core::ai::Status CheckWork();
		void             Update(float dt);

		core::ai::Status Move();
		core::ai::Status Eat(float foodQty);

		void set_path(const motion::Path& path)
		{
			path_ = path;
		}

		core::ai::Status Work();
		core::ai::Status Idle();
		void             SetupBehaviourTree();

		void set_work(gameplay::Building& work, const Job job)
		{
			job_ = job;
			work_ = work;
			have_work_ = true;
		}

		float hunger_ = 0;
		bool  resource_available_ = true;
		bool  target_reachable_ = true;
		float target_distance_ = 20;
	};
}
#endif //API_AI_NPC_H
