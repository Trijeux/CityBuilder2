#include "motion/path.h"

void api::motion::Path::AddPoint(sf::Vector2f start)
{
	points_.push_back(start);
}

void api::motion::Path::AddPoints(const std::vector<sf::Vector2f>& points)
{
	for (auto& point : points)
	{
		points_.push_back(point);
	}
}