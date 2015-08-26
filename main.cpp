#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <cmath>

sf::Vector2f relativeMovingAlongTheRim(sf::RectangleShape&);
int step(sf::RectangleShape&, float);
int step(sf::RectangleShape&, float, float);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Boss!");

	window.setFramerateLimit(60);
	
	sf::RectangleShape bossBody(sf::Vector2f(100.f, 300.f));
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
	bossBody.setPosition(900, 350);
	bossBody.setOutlineThickness(1);
	bossBody.setOutlineColor(sf::Color::Yellow);

	bossLeftHandUp.setFillColor(sf::Color(150, 0, 0));
	bossLeftHandUp.setOrigin(bossLeftHandUp.getSize().x / 2.f, bossLeftHandUp.getSize().x / 2.f);
	bossLeftHandUp.setPosition(bossBody.getPosition().x, bossBody.getPosition().y - bossBody.getSize().y + bossBody.getSize().y / 4.f);
	bossLeftHandUp.setOutlineThickness(1);
	bossLeftHandUp.setOutlineColor(sf::Color::Yellow);
	bossLeftHandUp.setRotation(35);

	bossLeftHandDown.setFillColor(sf::Color(0, 150, 0));
	bossLeftHandDown.setOrigin(bossLeftHandDown.getSize().x / 2.f, bossLeftHandDown.getSize().x / 2.f);
	bossLeftHandDown.setPosition(880, 260);
	bossLeftHandDown.setOutlineThickness(1);
	bossLeftHandDown.setOutlineColor(sf::Color::Yellow);
	bossLeftHandDown.setRotation(110);

	bossRightHandUp.setFillColor(sf::Color::Red);
	bossRightHandUp.setOrigin(bossRightHandUp.getSize().x / 2.f, bossRightHandUp.getSize().x / 2.f);
	bossRightHandUp.setPosition(bossBody.getPosition().x, bossBody.getPosition().y - bossBody.getSize().y + bossBody.getSize().y / 4.f);
	bossRightHandUp.setOutlineThickness(1);
	bossRightHandUp.setOutlineColor(sf::Color::Yellow);
	bossRightHandUp.setRotation(15);

	bossRightHandDown.setFillColor(sf::Color::Green);
	bossRightHandDown.setOrigin(bossRightHandDown.getSize().x / 2.f, bossRightHandDown.getSize().x / 2.f);
	bossRightHandDown.setPosition(880, 260);
	bossRightHandDown.setOutlineThickness(1);
	bossRightHandDown.setOutlineColor(sf::Color::Yellow);
	bossRightHandDown.setRotation(75);

	bossLeftLegUp.setFillColor(sf::Color(150, 0, 150));
	bossLeftLegUp.setOrigin(bossLeftLegUp.getSize().x / 2.f, bossLeftLegUp.getSize().x / 2.f);
	bossLeftLegUp.setPosition(bossBody.getPosition().x, bossBody.getPosition().y + 50);
	bossLeftLegUp.setOutlineThickness(1);
	bossLeftLegUp.setOutlineColor(sf::Color::Yellow);
	
	bossLeftLegDown.setFillColor(sf::Color(0, 0, 150));
	bossLeftLegDown.setOrigin(bossLeftLegDown.getSize().x / 2.f, bossLeftLegDown.getSize().x / 2.f);
	bossLeftLegDown.setPosition(940, 520);
	bossLeftLegDown.setOutlineThickness(1);
	bossLeftLegDown.setOutlineColor(sf::Color::Yellow);
	bossLeftLegDown.setRotation(-30);

	bossRightLegUp.setFillColor(sf::Color::Magenta);
	bossRightLegUp.setOrigin(bossRightLegUp.getSize().x / 2.f, bossRightLegUp.getSize().x / 2.f);
	bossRightLegUp.setPosition(bossBody.getPosition().x, bossBody.getPosition().y + 50);
	bossRightLegUp.setOutlineThickness(1);
	bossRightLegUp.setOutlineColor(sf::Color::Yellow);
	bossRightLegUp.setRotation(45);
	
	bossRightLegDown.setFillColor(sf::Color::Blue);
	bossRightLegDown.setOrigin(bossRightLegDown.getSize().x / 2.f, bossRightLegDown.getSize().x / 2.f);
	bossRightLegDown.setPosition(1060, 520);
	bossRightLegDown.setOutlineThickness(1);
	bossRightLegDown.setOutlineColor(sf::Color::Yellow);

	////////

	bool bossLeftLegUpMovingForward = true;
	bool bossLeftLegUpMovingBack = false;
	bool bossLeftLegDownMovingForward = false;
	bool bossLeftLegDownMovingBack = false;
	bool bossRightLegUpMovingForward = false;
	bool bossRightLegUpMovingBack = true;
	bool bossRightLegDownMovingForward = false;
	bool bossRightLegDownMovingBack = false;

	sf::RectangleShape& frontLegUp = bossLeftLegUp;
	sf::RectangleShape& frontLegDown = bossLeftLegDown;
	sf::RectangleShape& backLegUp = bossRightLegUp;
	sf::RectangleShape& backLegDown = bossRightLegDown;

	float bossLeftLegUpRotationAngle = 1;
	float bossLeftLegUpRotationAngleStop = 45;
	float bossLeftLegDownRotationAngle = 2;
	float bossLeftLegDownRotationAngleStop = 35;
	float bossRightLegUpRotationAngle = 1;
	float bossRightLegUpRotationAngleStop = 45;
	float bossRightLegDownRotationAngle = 2;
	float bossRightLegDownRotationAngleStop = 35;
	
	while (window.isOpen())
	{
		////////
		//Events
		////////
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		////////
		//Update
		////////

		//// Left leg
		if (bossLeftLegUpMovingForward)
		{
			short stepCode = step(frontLegUp, bossLeftLegUpRotationAngle, bossLeftLegUpRotationAngleStop);
			step(frontLegDown, bossLeftLegUpRotationAngle, bossLeftLegUpRotationAngleStop);
			if (stepCode == 1)
			{
				bossLeftLegUpMovingForward = false;

				bossLeftLegDownMovingForward = true;
			}
		}
		if (bossLeftLegDownMovingForward)
		{
			short stepCode = step(frontLegDown, bossLeftLegDownRotationAngle, bossLeftLegDownRotationAngleStop);
			if (stepCode == 1)
			{
				bossLeftLegDownMovingForward = false;
				
				bossLeftLegUpMovingBack = true;
			}
		}
		if (bossLeftLegDownMovingBack)
		{
			short stepCode = step(frontLegDown, -bossLeftLegDownRotationAngle, bossLeftLegDownRotationAngleStop);
			bossBody.move(-1, 0);
			if (stepCode == 1)
			{
				bossLeftLegDownMovingBack = false;

				bossLeftLegUpMovingBack = true;
				bossRightLegUpMovingForward = true;
			}
		}
		if (bossLeftLegUpMovingBack)
		{
			short stepCode2 = step(frontLegUp, -bossLeftLegUpRotationAngle, bossLeftLegUpRotationAngleStop);
			step(frontLegDown, -bossLeftLegUpRotationAngle, bossLeftLegUpRotationAngleStop); // для синхронности верха и низа ноги
			bossBody.move(-1, 0);
			if (stepCode2 == 1)
			{
				bossLeftLegUpMovingBack = false;

				bossLeftLegUpMovingForward = true;
			}
		}
		//// Right leg
		if (bossRightLegUpMovingForward)
		{
			short stepCode = step(backLegUp, bossRightLegUpRotationAngle, bossRightLegUpRotationAngleStop);
			step(backLegDown, bossRightLegUpRotationAngle, bossRightLegUpRotationAngleStop);
			if (stepCode == 1)
			{
				bossRightLegUpMovingForward = false;

				bossRightLegDownMovingForward = true;
			}
		}
		if (bossRightLegDownMovingForward)
		{
			short stepCode = step(backLegDown, bossRightLegDownRotationAngle, bossRightLegDownRotationAngleStop);
			if (stepCode == 1)
			{
				bossRightLegDownMovingForward = false;

				bossRightLegUpMovingBack = true;
			}
		}
		if (bossRightLegDownMovingBack)
		{
			short stepCode = step(backLegDown, -bossRightLegDownRotationAngle, bossRightLegDownRotationAngleStop);
			bossBody.move(-1, 0);
			if (stepCode == 1)
			{
				bossRightLegDownMovingBack = false;

				bossRightLegUpMovingBack = true;
				bossLeftLegUpMovingForward = true;
			}
		}
		if (bossRightLegUpMovingBack)
		{
			short stepCode = step(backLegUp, -bossRightLegUpRotationAngle, bossRightLegUpRotationAngleStop);
			step(backLegDown, -bossRightLegUpRotationAngle, bossRightLegUpRotationAngleStop); // для синхронности верха и низа ноги
			bossBody.move(-1, 0);
			if (stepCode == 1)
			{
				bossRightLegUpMovingBack = false;

				bossRightLegUpMovingForward = true;
			}
		}

		bossLeftHandDown.setPosition(relativeMovingAlongTheRim(bossLeftHandUp));
		bossLeftLegDown.setPosition(relativeMovingAlongTheRim(bossLeftLegUp));
		bossRightHandDown.setPosition(relativeMovingAlongTheRim(bossRightHandUp));
		bossRightLegDown.setPosition(relativeMovingAlongTheRim(bossRightLegUp));
		bossLeftHandUp.setPosition(bossBody.getPosition().x, bossBody.getPosition().y - bossBody.getSize().y + bossBody.getSize().y / 4.f);
		bossRightHandUp.setPosition(bossBody.getPosition().x, bossBody.getPosition().y - bossBody.getSize().y + bossBody.getSize().y / 4.f);
		bossLeftLegUp.setPosition(bossBody.getPosition().x, bossBody.getPosition().y + 50);
		bossRightLegUp.setPosition(bossBody.getPosition().x, bossBody.getPosition().y + 50);
		
		////////
		//Render
		////////
		window.clear();

		window.draw(bossLeftLegDown);
		window.draw(bossLeftHandDown);
		window.draw(bossLeftLegUp);
		window.draw(bossLeftHandUp);
		window.draw(bossBody);
		window.draw(bossRightLegDown);
		window.draw(bossRightHandDown);
		window.draw(bossRightLegUp);
		window.draw(bossRightHandUp);
		
		window.display();
	}

	return 0;
	
}

sf::Vector2f relativeMovingAlongTheRim(sf::RectangleShape& obj)
{
	sf::Vector2f center = obj.getPosition();
	sf::Vector2f startPoint = { obj.getPosition().x, obj.getPosition().y + obj.getSize().y - obj.getSize().x / 2.f * 2 };
	short angle = obj.getRotation();
	
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

int step(sf::RectangleShape& steppingLeg, float angle)
{
	steppingLeg.rotate(angle);
	if (steppingLeg.getRotation() >= 90)
	{
		return 1;
	}
	return 0;
}
int step(sf::RectangleShape& steppingLeg, float angle, float stop)
{
	steppingLeg.rotate(angle);
	if (steppingLeg.getRotation() > stop)
		return 1;
	else 
		return 0;
}