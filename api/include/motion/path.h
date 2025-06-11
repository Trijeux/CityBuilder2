#ifndef API_MOTION_PATH_H
#define API_MOTION_PATH_H

#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace api::motion
{
	class Path
	{
		std::vector<sf::Vector2f> points_;

		const sf::Vector2f tile_size_ = sf::Vector2f(sf::Texture("resources/sprite/ground.png").getSize());
	public:
		void AddPoint(sf::Vector2f start);
		void AddPoints(const std::vector<sf::Vector2f>& points);

		const std::vector<sf::Vector2f>& Points() const { return points_; }

	};
}

#endif //API_MOTION_PATH_H
