#include <SFML\Graphics.hpp>

int main()
{
	//Create The window
	int screenWidth = 800;
	int	screenHeight = 600;
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "4019 - SFML Template");

	//Create a circle of radius 256 units
	float circleRadius = 256;
	sf::CircleShape shape(256.f);

	//Set The color and position of the circle
	shape.setFillColor(sf::Color::Blue);
	float shapeXPos = 0;
	float shapeYPos = 0;
	shape.setPosition(shapeXPos, shapeYPos);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				//window.setPosition(sf::Vector2i(window.getPosition().x + 100, window.getPosition().y));
			}
		}
		window.clear();
		window.draw(shape);
		window.display();
	}
	return 0;
}