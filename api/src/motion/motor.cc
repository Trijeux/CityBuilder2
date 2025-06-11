#include "motion/motor.h"

#include <iostream>

bool api::motion::Motor::Update(const float dt)
{
	const sf::Vector2f distance = destination_ - position_;

	if(distance.length() < speed_ * dt)
	{
		position_ = destination_;
		return true;
	}

	position_ += distance.normalized() * dt * speed_;
	return false;
}
