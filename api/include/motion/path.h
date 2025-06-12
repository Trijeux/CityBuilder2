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

	public:
		void AddPoint(sf::Vector2f start);
		void AddPoints(const std::vector<sf::Vector2f>& points);

		void Fill(std::vector<sf::Vector2f>& pathPoints);
		
		[[nodiscard]] bool IsValid() const;
		[[nodiscard]] const std::vector<sf::Vector2f>& Points() const { return points_; }

	};
}

#endif //API_MOTION_PATH_H
