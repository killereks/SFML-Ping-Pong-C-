#include "Ball.h"

void Ball::Update(float timeDelta){
    position.x += velocity.x * timeDelta;
    position.y += velocity.y * timeDelta;

    shape.setOrigin(position);
}

sf::CircleShape Ball::GetShape(){
    return shape;
}

void Ball::Bounce(sf::Vector2f a, sf::Vector2f b) {
    if (position.y - radius < a.y) {
        velocity.y = abs(velocity.y);
    }
    if (position.y > b.y) {
        velocity.y = -abs(velocity.y);
    }
}

sf::Vector2f Ball::GetPosition() {
    return position;
}

void Ball::ResetPosition() {
    this->position = sf::Vector2f(-400, -300);

    shape.setOrigin(position);

    float angle = ((float)rand() / (float)RAND_MAX) * 3.14159265 * 2;

    this->velocity.x = cos(angle) * 350;
    this->velocity.y = sin(angle) * 350;

    if (abs(this->velocity.x) < 50) {
        this->velocity.x *= 10;
    }
}

void Ball::SetVelocitySign(bool positive) {
    if (positive) {
        this->velocity.x = abs(velocity.x);
    }
    else {
        this->velocity.x = -abs(velocity.x);
    }
}

void Ball::MultiplySpeed(float amount){
    this->velocity.x *= amount;
    this->velocity.y *= amount;
}

sf::Vector2f Ball::GetVelocity() {
    return velocity;
}
