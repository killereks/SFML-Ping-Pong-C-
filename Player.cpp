#include "Player.h"

sf::RectangleShape Player::GetShape() {
	return shape;
}

void Player::Move(sf::Vector2f dir) {
	position += dir;

	shape.setOrigin(position);
}

void Player::Restrict(sf::Vector2f min, sf::Vector2f max) {
	min.x -= scale.x;
	min.y -= scale.y;

	if (position.x < min.x) position.x = min.x;
	if (position.x > max.x) position.x = max.x;

	if (position.y < min.y) position.y = min.y;
	if (position.y > max.y) position.y = max.y;
}

void Player::IncreaseScore() {
	score++;
}

short Player::GetScore() {
	return score;
}

sf::Vector2f Player::GetPosition()
{
	return sf::Vector2f();
}

void Player::AI(sf::Vector2f ballPos, sf::Vector2f ballVel, float timeDelta) {
	float maxMoveSpeed = 500;

	float gradient = ballVel.y / ballVel.x;
	float yIntercept = -ballPos.x * gradient + ballPos.y;

	float targetY = gradient * position.x + yIntercept;

	if (targetY > position.y - scale.y/2) {
		Move(sf::Vector2f(0, maxMoveSpeed * timeDelta));
	}
	else {
		Move(sf::Vector2f(0, -maxMoveSpeed * timeDelta));
	}
}

sf::Vector2f Player::GetScale() {
	return scale;
}