#ifndef API_MOTION_MOTOR_H
#define API_MOTION_MOTOR_H

#include <SFML/System/Vector2.hpp>

namespace api::motion {

	class Motor {
		sf::Vector2f position_;
		sf::Vector2f destination_;
		float speed_ = 0;
		float remaining_distance_ = 0;;

	public:
		// choix 2
		bool Update(float dt);

		// getter / setter
		float remaining_distance() const {return remaining_distance_;}
		void set_speed(const float speed){speed_ = speed;}
		void set_destination(const sf::Vector2f destination){destination_ = destination;};
		void set_position(const sf::Vector2f position){position_ = position;}
		[[nodiscard]] const sf::Vector2f& position() const{return position_;}

	};

}

#endif //API_MOTION_MOTOR_H
