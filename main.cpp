#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <cmath>

sf::Vector2f movePointOnTheCircle(sf::Vector2f center, sf::Vector2f startPoint, short angle)
{
	angle += 180;
	float rx, ry;
	rx = startPoint.x - center.x;
	ry = startPoint.y - center.y;
	
	float alpha = -angle * M_PI / 180;

	sf::Vector2f finishPoint;

	finishPoint.x = center.x + rx * (cos(alpha)) - ry * (sin(alpha));
	finishPoint.y = center.y + rx * (sin(alpha)) - ry * (cos(alpha));

	return finishPoint;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!");

	window.setFramerateLimit(60);
	
	sf::RectangleShape bossBody(sf::Vector2f(200.f, 300.f));
	sf::RectangleShape bossLeftHandUp(sf::Vector2f(40.f, 150.f));
	sf::RectangleShape bossLeftHandDown(sf::Vector2f(36.f, 160.f));
	sf::RectangleShape bossRightHandUp(sf::Vector2f(40.f, 150.f));
	sf::RectangleShape bossRightHandDown(sf::Vector2f(36.f, 160.f));
	sf::RectangleShape bossLeftLegUp(sf::Vector2f(80.f, 160.f));
	sf::RectangleShape bossLeftLegDown(sf::Vector2f(70.f, 180.f));
	sf::RectangleShape bossRightLegUp(sf::Vector2f(80.f, 160.f));
	sf::RectangleShape bossRightLegDown(sf::Vector2f(70.f, 180.f));

	bossBody.setFillColor(sf::Color::Cyan);
	bossBody.setOrigin(bossBody.getSize().x / 2.f, bossBody.getSize().y - bossBody.getSize().y / 6.f);
	bossBody.setPosition(200, 350);

	bossLeftHandUp.setFillColor(sf::Color::Red);
	bossLeftHandUp.setOrigin(bossLeftHandUp.getSize().x / 2.f, bossLeftHandUp.getSize().x / 2.f);
	bossLeftHandUp.setPosition(80, 120);

	bossLeftHandDown.setFillColor(sf::Color::Green);
	bossLeftHandDown.setOrigin(bossLeftHandDown.getSize().x / 2.f, bossLeftHandDown.getSize().x / 2.f);
	bossLeftHandDown.setPosition(80, 260);

	bossRightHandUp.setFillColor(sf::Color::Red);
	bossRightHandUp.setOrigin(bossRightHandUp.getSize().x / 2.f, bossRightHandUp.getSize().x / 2.f);
	bossRightHandUp.setPosition(320, 120);

	bossRightHandDown.setFillColor(sf::Color::Green);
	bossRightHandDown.setOrigin(bossRightHandDown.getSize().x / 2.f, bossRightHandDown.getSize().x / 2.f);
	bossRightHandDown.setPosition(320, 260);

	bossLeftLegUp.setFillColor(sf::Color::Magenta);
	bossLeftLegUp.setOrigin(bossLeftLegUp.getSize().x / 2.f, bossLeftLegUp.getSize().x / 2.f);
	bossLeftLegUp.setPosition(140, 400);

	bossLeftLegDown.setFillColor(sf::Color::Blue);
	bossLeftLegDown.setOrigin(bossLeftLegDown.getSize().x / 2.f, bossLeftLegDown.getSize().x / 2.f);
	bossLeftLegDown.setPosition(140, 520);

	bossRightLegUp.setFillColor(sf::Color::Magenta);
	bossRightLegUp.setOrigin(bossRightLegUp.getSize().x / 2.f, bossRightLegUp.getSize().x / 2.f);
	bossRightLegUp.setPosition(260, 400);
	
	bossRightLegDown.setFillColor(sf::Color::Blue);
	bossRightLegDown.setOrigin(bossRightLegDown.getSize().x / 2.f, bossRightLegDown.getSize().x / 2.f);
	bossRightLegDown.setPosition(260, 520);

	while (window.isOpen())
	{
		//Events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		//Update
		bossRightHandUp.rotate(-1);
		bossLeftHandUp.rotate(1);
		bossRightLegUp.rotate(-1);
		bossLeftLegUp.rotate(1);
				
		bossLeftHandDown.setPosition(movePointOnTheCircle(bossLeftHandUp.getPosition(), { bossLeftHandUp.getPosition().x, bossLeftHandUp.getPosition().y + bossLeftHandUp.getSize().y - bossLeftHandUp.getSize().x / 2.f * 2 }, bossLeftHandUp.getRotation()));
		bossLeftLegDown.setPosition(movePointOnTheCircle(bossLeftLegUp.getPosition(), { bossLeftLegUp.getPosition().x, bossLeftLegUp.getPosition().y + bossLeftLegUp.getSize().y - bossLeftLegUp.getSize().x / 2.f * 2 }, bossLeftLegUp.getRotation()));
		bossRightHandDown.setPosition(movePointOnTheCircle(bossRightHandUp.getPosition(), { bossRightHandUp.getPosition().x, bossRightHandUp.getPosition().y + bossRightHandUp.getSize().y - bossRightHandUp.getSize().x / 2.f * 2 }, bossRightHandUp.getRotation()));
		bossRightLegDown.setPosition(movePointOnTheCircle(bossRightLegUp.getPosition(), { bossRightLegUp.getPosition().x, bossRightLegUp.getPosition().y + bossRightLegUp.getSize().y - bossRightLegUp.getSize().x / 2.f * 2 }, bossRightLegUp.getRotation()));

		//Render
		window.clear();

		window.draw(bossLeftLegDown);
		window.draw(bossRightLegDown);
		window.draw(bossLeftLegUp);
		window.draw(bossRightLegUp);
		window.draw(bossLeftHandDown);
		window.draw(bossRightHandDown);
		window.draw(bossLeftHandUp);
		window.draw(bossRightHandUp);
		window.draw(bossBody);

		window.display();
	}

	return 0;
	
}