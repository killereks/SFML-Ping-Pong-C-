#pragma once

#include <SFML/Graphics.hpp>

class Player {
private:
	sf::Vector2f position;
	sf::Vector2f scale;

	sf::RectangleShape shape;

	unsigned int score;

public:

	Player(sf::Vector2f position, sf::Vector2f scale) {
		shape = sf::RectangleShape(scale);
		this->position = position;
		this->scale = scale;

		shape.setOrigin(position);

		score = 0;
	}

	sf::RectangleShape GetShape();
	void Move(sf::Vector2f dir);
	void Restrict(sf::Vector2f min, sf::Vector2f max);
	void IncreaseScore();
	short GetScore();

	sf::Vector2f GetPosition();
	sf::Vector2f GetScale();

	void AI(sf::Vector2f ballPos, sf::Vector2f ballVel, float timeDelta);
};

