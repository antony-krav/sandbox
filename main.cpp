#include <SFML/Graphics.hpp>
#include "Level.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(980, 640), "My indie!");
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 980, 640));
	
	Level lvlMain, lvlPar1, lvlPar2, lvlPar3;
	lvlMain.LoadFromFile("mapMain.tmx");
	lvlPar1.LoadFromFile("mapPar1.tmx");
	lvlPar2.LoadFromFile("mapPar2.tmx");
	lvlPar3.LoadFromFile("mapPar3.tmx");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && view.getCenter().x > window.getSize().x / 2)
			{
				view.move({ -10, 0 });
				lvlPar1.move({ 50, 0 });
				lvlPar2.move({ -4, 0 });
				lvlPar3.move({ -8, 0 });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && view.getCenter().x < 2000)
			{
				view.move({ 10, 0 });
				lvlPar1.move({ -50, 0 });
				lvlPar2.move({ 4, 0 });
				lvlPar3.move({ 8, 0 });
			}
		}
		window.setView(view);		

		window.clear();
		window.draw(lvlPar3);
		window.draw(lvlPar2);
		window.draw(lvlMain);
		window.draw(lvlPar1);
		
		
		window.display();
	}

	return 0;
}