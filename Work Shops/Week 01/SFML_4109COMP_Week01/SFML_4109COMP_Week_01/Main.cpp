#include <SFML\Graphics.hpp>
#include <iostream>

int main()
{
	//Create The window
	int screenWidth = 800;
	int	screenHeight = 600;
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "4019 - SFML Template");

	//Create a circle of radius 50 units
	float circleRadius = 50;
	sf::CircleShape shape(circleRadius);

	//Set The color and position of the circle
	shape.setFillColor(sf::Color::Blue);
	float shapeXPos = 0;
	float shapeYPos = 0;

	float shapeSpeed = 0.5;
	int shapeDirection = 1;
	float shapeStep = 0;

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

		if (shape.getPosition().x + 2*circleRadius >= screenWidth )
		{
			shapeDirection = -1;
		}
		if (shape.getPosition().x <= 0)
		{
			shapeDirection = 1;
		}

		shapeStep = shapeSpeed * shapeDirection;
		std::cout << "Step:" << shapeStep << " Speed:" << shapeSpeed << " Direction:" << shapeDirection << " pos:" << shape.getPosition().x << "," << shape.getPosition().y << std::endl;
		shape.move(sf::Vector2f(shapeStep,0));
		window.setPosition(window.getPosition().x - shapeStep, window.getPosition().y);



		window.clear();
		window.draw(shape);
		window.display();
	}
	return 0;
}