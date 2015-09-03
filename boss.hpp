#ifndef BOSS_H
#define BOSS_H

#include <SFML/Graphics.hpp>

enum attackType
{
	leftHand,
	rightHand,
	kick
};

enum motion
{
	forward,
	back,
	stay
};

class Boss: public sf::Drawable
{
public:
	Boss(float, float);
	void walk(float);
	void attack();
	void attack(attackType);
	// more
private:
	//sf::Vector2f position;

	sf::RectangleShape body;
	sf::RectangleShape leftLegUp;
	sf::RectangleShape leftLegDown;
	sf::RectangleShape rightLegUp;
	sf::RectangleShape rightLegDown;
	sf::RectangleShape leftHandUp;
	sf::RectangleShape leftHandDown;	
	sf::RectangleShape rightHandUp;
	sf::RectangleShape rightHandDown;

	sf::Vector2i leftLegUpRotationStops;
	sf::Vector2i leftLegDownRotationStops;
	sf::Vector2i rightLegUpRotationStops;
	sf::Vector2i rightLegDownRotationStops;
	float leftHandUpRotationStop;
	float leftHandDownRotationStop;
	float rightHandUpRotationStop;
	float rightHandDownRotationStop;

	motion leftLegUpMotion;
	motion leftLegDownMotion;
	motion rightLegUpMotion;
	motion rightLegDownMotion;

	//sf::Thread leftLeg;
	//sf::Thread rightLeg;
	//sf::Thread leftHand;
	//sf::Thread rightHand;

	sf::Vector2f relativeMovingAlongTheRim(sf::RectangleShape&);
	int step(sf::RectangleShape&, float, float);
	int stepBack(sf::RectangleShape&, float, float);
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	
	void walking();
	void updatePartsPosition();

};

#endif // BOSS_H