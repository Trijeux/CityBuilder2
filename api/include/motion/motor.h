#ifndef API_MOTION_MOTOR_H
#define API_MOTION_MOTOR_H

#include <SFML/System/Vector2.hpp>

namespace api::motion {

	class Motor {
		sf::Vector2f position_;
		sf::Vector2f destination_;
		float speed_ = 0;

	public:
		// choix 2
		bool Update(float dt);

		// getter / setter
		void SetSpeed(const float speed){speed_ = speed;}
		void SetDestination(const sf::Vector2f destination){destination_ = destination;};
		void SetPosition(const sf::Vector2f position){position_ = position;}
		[[nodiscard]] const sf::Vector2f& GetPosition() const{return position_;}

	};

}

#endif //API_MOTION_MOTOR_H
