#pragma once

#include <SFML/Graphics.hpp>

class Ball
{
private: 
	sf::Vector2f position;
	sf::Vector2f velocity;
	float radius;

	sf::CircleShape shape;


public:
	void Update(float timeDelta);
	sf::CircleShape GetShape();
	void Bounce(sf::Vector2f a, sf::Vector2f b);

	sf::Vector2f GetPosition();
	sf::Vector2f GetVelocity();

	void ResetPosition();

	void SetVelocitySign(bool positive);
	void MultiplySpeed(float amount);

	Ball(sf::Vector2f pos, float radius) {
		this->position = pos;
		this->radius = radius;

		shape = sf::CircleShape(radius);

		ResetPosition();
	}
};

