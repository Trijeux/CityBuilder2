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

void api::motion::Path::Fill(std::vector<sf::Vector2f>& pathPoints){
	if (!pathPoints.empty())
		points_ = pathPoints;
}

bool api::motion::Path::IsValid() const{
	return !points_.empty();
}