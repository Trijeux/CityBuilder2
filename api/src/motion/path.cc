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
	idx_point_ = 0;
}

sf::Vector2f api::motion::Path::GetNextPoint()
{
	if(!is_valid())
	{
		return {0, 0,};
	}

	if(!IsDone())
	{
		++idx_point_;
	}

	return points_[idx_point_];
}

bool api::motion::Path::is_valid() const{
	return !points_.empty();
}

bool api::motion::Path::IsDone() const
{
	return idx_point_ == points_.size() - 1;
}

sf::Vector2f api::motion::Path::StartPoint() const{
	if (is_valid()) {
		return points_[0];
	}
	return {0, 0,};
}
