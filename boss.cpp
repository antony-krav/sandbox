#define _USE_MATH_DEFINES			// for M_PI

#ifndef M_PI						// if _USE_MATH_DEFINES not works
#define M_PI 3.14159265358979323846	// define M_PI manually
#endif // M_PI

#include "boss.hpp"

#include <cmath>
#include <ctime>

Boss::Boss(float positionX, float positionY)
{
	body.setSize(sf::Vector2f(100.f, 300.f));
	body.setFillColor(sf::Color::Cyan);
	body.setOrigin(body.getSize().x / 2.f, body.getSize().y / 6.f);
	body.setPosition(positionX, positionY);
	body.setOutlineThickness(1);
	body.setOutlineColor(sf::Color::Yellow);

	leftLegUp.setSize(sf::Vector2f(80.f, 160.f));
	leftLegUp.setFillColor(sf::Color::Magenta);
	leftLegUp.setOrigin(leftLegUp.getSize().x / 2.f, leftLegUp.getSize().x / 2.f);
	leftLegUp.setPosition(body.getPosition().x, body.getPosition().y + body.getSize().y - body.getSize().x / 2.f);
	leftLegUp.setOutlineThickness(1);
	leftLegUp.setOutlineColor(sf::Color::Yellow);
	leftLegUp.setRotation(45);

	leftLegDown.setSize(sf::Vector2f(70.f, 180.f));
	leftLegDown.setFillColor(sf::Color::Blue);
	leftLegDown.setOrigin(leftLegDown.getSize().x / 2.f, leftLegDown.getSize().x / 2.f);
	leftLegDown.setPosition(relativeMovingAlongTheRim(leftLegUp));
	leftLegDown.setOutlineThickness(1);
	leftLegDown.setOutlineColor(sf::Color::Yellow);

	leftHandUp.setSize(sf::Vector2f(40.f, 150.f));
	leftHandUp.setFillColor(sf::Color::Red);
	leftHandUp.setOrigin(leftHandUp.getSize().x / 2.f, leftHandUp.getSize().x / 2.f);
	leftHandUp.setPosition(body.getPosition().x, body.getPosition().y -20);
	leftHandUp.setOutlineThickness(1);
	leftHandUp.setOutlineColor(sf::Color::Yellow);
	leftHandUp.setRotation(15);

	leftHandDown.setSize(sf::Vector2f(36.f, 160.f));
	leftHandDown.setFillColor(sf::Color::Green);
	leftHandDown.setOrigin(leftHandDown.getSize().x / 2.f, leftHandDown.getSize().x / 2.f);
	leftHandDown.setPosition(relativeMovingAlongTheRim(leftHandUp));
	leftHandDown.setOutlineThickness(1);
	leftHandDown.setOutlineColor(sf::Color::Yellow);
	leftHandDown.setRotation(75);

	rightLegUp.setSize(sf::Vector2f(80.f, 160.f));
	rightLegUp.setFillColor(sf::Color(150, 0, 150)); // half-margenta
	rightLegUp.setOrigin(rightLegUp.getSize().x / 2.f, rightLegUp.getSize().x / 2.f);
	rightLegUp.setPosition(body.getPosition().x, body.getPosition().y + body.getSize().y - body.getSize().x / 2.f);
	rightLegUp.setOutlineThickness(1);
	rightLegUp.setOutlineColor(sf::Color::Yellow);

	rightLegDown.setSize(sf::Vector2f(70.f, 180.f));
	rightLegDown.setFillColor(sf::Color(0, 0, 150)); // half-blue
	rightLegDown.setOrigin(rightLegDown.getSize().x / 2.f, rightLegDown.getSize().x / 2.f);
	rightLegDown.setPosition(relativeMovingAlongTheRim(rightLegUp));
	rightLegDown.setOutlineThickness(1);
	rightLegDown.setOutlineColor(sf::Color::Yellow);

	rightHandUp.setSize(sf::Vector2f(40.f, 150.f));
	rightHandUp.setFillColor(sf::Color(150, 0, 0)); // half-red
	rightHandUp.setOrigin(rightHandUp.getSize().x / 2.f, rightHandUp.getSize().x / 2.f);
	rightHandUp.setPosition(body.getPosition().x, body.getPosition().y - 20);
	rightHandUp.setOutlineThickness(1);
	rightHandUp.setOutlineColor(sf::Color::Yellow);
	rightHandUp.setRotation(35);

	rightHandDown.setSize(sf::Vector2f(36.f, 160.f));
	rightHandDown.setFillColor(sf::Color(0, 150, 0)); // half-green
	rightHandDown.setOrigin(rightHandDown.getSize().x / 2.f, rightHandDown.getSize().x / 2.f);
	rightHandDown.setPosition(relativeMovingAlongTheRim(rightHandUp));
	rightHandDown.setOutlineThickness(1);
	rightHandDown.setOutlineColor(sf::Color::Yellow);
	rightHandDown.setRotation(110);

	leftLegUpMotion = forward;
	leftLegDownMotion = stay;
	rightLegUpMotion = stay;
	rightLegDownMotion = stay;

	leftLegUpRotationStops = { 45, 325 };
	leftLegDownRotationStops = { 45, 325 };
	rightLegUpRotationStops = { 45, 325 };
	rightLegDownRotationStops = { 45, 325 };
}
void Boss::walk(float dist)
{
	// must add counter
	walking();
}
void Boss::attack()
{
	srand(time(0));
	short i = 1 + rand() % 3;
	switch (i)
	{
	case 1:
		attack(leftHand);
		break;
	case 2:
		attack(rightHand);
		break;
	case 3:
		attack(kick);
		break;
	default:
		break;
	}
}
void Boss::attack(attackType type)
{
	switch (type)
	{
	case leftHand:
		// empty yet
		break;
	case rightHand:
		// empty yet
		break;
	case kick:
		// empty yet
		break;
	default:
		break;
	}
}
void Boss::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rightLegDown);
	target.draw(rightLegUp);
	target.draw(rightHandDown);
	target.draw(rightHandUp);
	target.draw(body);
	target.draw(leftLegDown);
	target.draw(leftLegUp);
	target.draw(leftHandDown);
	target.draw(leftHandUp);
}
void Boss::walking()
{
	// left
	if (leftLegUpMotion != stay)
	{
		float speed = 1;
		short stepCode;
		if (leftLegUpMotion == back)
		{
			stepCode = stepBack(leftLegUp, -speed, leftLegUpRotationStops.y);
			body.move(-1.f, 0.f);
			updatePartsPosition();
		}
		else stepCode = step(leftLegUp, speed, leftLegUpRotationStops.x);
		if (stepCode == 1)
		{
			if (leftLegUpMotion == forward)
			{
				leftLegUpMotion = stay;
				leftLegDownMotion = forward;
			}
			else
			{
				leftLegUpMotion = forward;
			}
			
		}
		leftLegDown.setPosition(relativeMovingAlongTheRim(leftLegUp));
	}
	if (leftLegDownMotion != stay)
	{
		float speed = 1;
		short stepCode;
		if (leftLegDownMotion == back) stepCode = stepBack(leftLegDown, -speed, leftLegDownRotationStops.y);
		else stepCode = step(leftLegDown, speed, leftLegDownRotationStops.x);
		if (stepCode == 1)
		{
			if (leftLegDownMotion == forward)
			{
				leftLegDownMotion = back;
				if (leftLegUpMotion == stay) leftLegUpMotion = back;
				rightLegUpMotion = forward;
			}
			else
			{
				leftLegDownMotion = stay;
			}
		}
	}
	// right
	if (rightLegUpMotion != stay)
	{
		float speed = 1;
		short stepCode;
		if (rightLegUpMotion == back)
		{
			stepCode = stepBack(rightLegUp, -speed, rightLegUpRotationStops.y);
			body.move(-1.f, 0.f);
			updatePartsPosition();
		}
		else stepCode = step(rightLegUp, speed, rightLegUpRotationStops.x);
		if (stepCode == 1)
		{
			if (rightLegUpMotion == forward)
			{
				rightLegUpMotion = stay;
				rightLegDownMotion = forward;
			}
			else
			{
				rightLegUpMotion = forward;
			}

		}
		rightLegDown.setPosition(relativeMovingAlongTheRim(rightLegUp));
	}
	if (rightLegDownMotion != stay)
	{
		float speed = 1;
		short stepCode;
		if (rightLegDownMotion == back) stepCode = stepBack(rightLegDown, -speed, rightLegDownRotationStops.y);
		else stepCode = step(rightLegDown, speed, rightLegDownRotationStops.x);
		if (stepCode == 1)
		{
			if (rightLegDownMotion == forward)
			{
				rightLegDownMotion = back;
				if (rightLegUpMotion == stay) rightLegUpMotion = back;
			}
			else
			{
				rightLegDownMotion = stay;
			}
		}
	}
}
void Boss::updatePartsPosition()
{
	leftLegUp.setPosition(body.getPosition().x, body.getPosition().y + body.getSize().y - body.getSize().x / 2.f);
	leftLegDown.setPosition(relativeMovingAlongTheRim(leftLegUp));
	leftHandUp.setPosition(body.getPosition().x, body.getPosition().y - 20);
	leftHandDown.setPosition(relativeMovingAlongTheRim(leftHandUp));
	rightLegUp.setPosition(body.getPosition().x, body.getPosition().y + body.getSize().y - body.getSize().x / 2.f);
	rightLegDown.setPosition(relativeMovingAlongTheRim(rightLegUp));
	rightHandUp.setPosition(body.getPosition().x, body.getPosition().y - 20);
	rightHandDown.setPosition(relativeMovingAlongTheRim(rightHandUp));
}
sf::Vector2f Boss::relativeMovingAlongTheRim(sf::RectangleShape& obj)
{
	sf::Vector2f center = obj.getPosition();
	sf::Vector2f startPoint = { obj.getPosition().x, obj.getPosition().y + obj.getSize().y - obj.getSize().x};
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
int Boss::step(sf::RectangleShape& steppingLeg, float speed, float stop)
{
	steppingLeg.rotate(speed);
	if (steppingLeg.getRotation() == stop+1)
		return 1;
	else
		return 0;
}
int Boss::stepBack(sf::RectangleShape& steppingLeg, float speed, float stop)
{
	steppingLeg.rotate(speed);
	if (steppingLeg.getRotation() == stop+1)
		return 1;
	else
		return 0;
}