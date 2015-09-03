#include "SFML\Graphics.hpp"
#include "boss.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Boss!");
	window.setFramerateLimit(60);

	Boss boss(900, 250);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(boss);
		window.display();

		boss.walk(5); // args not works yet
	}

	return 0;

}
