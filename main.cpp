#include <SFML/Graphics.hpp>

#include <stdio.h>
#include <iostream>
#include <direct.h>

#include "Player.h"
#include "Ball.h"

// both go on heap
// new -> delete
// malloc -> free

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Ping Pong Application");

	sf::Clock clock;

	unsigned int time_ui = unsigned int(time(NULL));
	srand(time_ui);

	Player player = Player(sf::Vector2f(-50, -250), sf::Vector2f(10,100));
	Player enemy = Player(sf::Vector2f(-750, -250), sf::Vector2f(10, 100));

	Ball ball = Ball(sf::Vector2f(-400,-300), 10);

	sf::RectangleShape midline = sf::RectangleShape(sf::Vector2f(6, 600));
	midline.setOrigin(sf::Vector2f(-403, 0));

	sf::Text playerScore;
	sf::Text enemyScore;

	sf::Font font;

	font.loadFromFile("OpenSans-Regular.ttf");

	playerScore.setFont(font);
	playerScore.setFillColor(sf::Color::White);
	playerScore.setCharacterSize(60);
	playerScore.setOrigin(sf::Vector2f(-300, -50));

	enemyScore.setFont(font);
	enemyScore.setFillColor(sf::Color::White);
	enemyScore.setCharacterSize(60);
	enemyScore.setOrigin(sf::Vector2f(-500, -50));

	float yInput = 0.0f;

	while (window.isOpen()) {
		sf::Event event;

		// float yInput = 0.0f;

		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::W) {
						yInput = 1.0f;
					}
					else if (event.key.code == sf::Keyboard::S) {
						yInput = -1.0f;
					}
					break;
				case sf::Event::KeyReleased:
					if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S) {
						yInput = 0;
					}
					break;
			}
		}

		playerScore.setString(sf::String(std::to_string(player.GetScore())));
		enemyScore.setString(sf::String(std::to_string(enemy.GetScore())));

		sf::Time elapsedTime = clock.restart();
		float timeDelta = elapsedTime.asSeconds();

		player.Move(sf::Vector2f(0, yInput * 500 * timeDelta));
		player.Restrict(sf::Vector2f(-800, -400), sf::Vector2f(0, 0));

		ball.Update(timeDelta);
		ball.Bounce(sf::Vector2f(-800, -600), sf::Vector2f(0, 0));

		enemy.AI(ball.GetPosition(), ball.GetVelocity(), timeDelta);
		enemy.Restrict(sf::Vector2f(-800, -400), sf::Vector2f(0, 0));

		if (ball.GetPosition().x > 0) {
			enemy.IncreaseScore();
			ball.ResetPosition();
		}
		if (ball.GetPosition().x < -800) {
			player.IncreaseScore();
			ball.ResetPosition();
		}

		if (ball.GetShape().getGlobalBounds().intersects(player.GetShape().getGlobalBounds())) {
			ball.SetVelocitySign(false);
			ball.MultiplySpeed(1.2f);
		}
		if (ball.GetShape().getGlobalBounds().intersects(enemy.GetShape().getGlobalBounds())) {
			ball.SetVelocitySign(true);
			ball.MultiplySpeed(1.2f);
		}

		window.clear();
		window.draw(playerScore);
		window.draw(enemyScore);

		window.draw(player.GetShape());
		window.draw(enemy.GetShape());

		window.draw(midline);

		window.draw(ball.GetShape());
		window.display();
	}

	return 0;
}