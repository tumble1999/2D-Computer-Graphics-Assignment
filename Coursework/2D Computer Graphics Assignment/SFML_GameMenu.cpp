#include "SFML_GameMenu.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Util.h"

SFML_GameMenu::SFML_GameMenu(std::string menufilename, int windowWidth, int windowHeight)
{
	std::ifstream inputFile(menufilename);

	m_quickMenuNavigationDelay = 50.0f;
	m_quickMenuNavigationRate = 5.0f;
	m_quickMenuNavigationTimer = m_quickMenuNavigationDelay;
	
	if (inputFile.is_open())
	{
		std::string stringLine;

		//line 1
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			m_backgroundTexture.loadFromFile(stringLine);
			m_backgroundSprite.setTexture(m_backgroundTexture);

			sf::Vector2u textureSize = m_backgroundTexture.getSize();
			m_backgroundSprite.setOrigin(static_cast<float>(textureSize.x / 2), static_cast<float>(textureSize.y / 2));
			m_backgroundSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
			m_backgroundSprite.setPosition(0, 0);

			//set texture
			m_backgroundRect.left = -static_cast<float> (textureSize.x / 2);
			m_backgroundRect.top = -static_cast<float> (textureSize.y / 2);
			m_backgroundRect.width = static_cast<float>(textureSize.x);
			m_backgroundRect.height = static_cast<float>(textureSize.y);
		}

		//line 2
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture to a sprite
			m_logo.loadFromFile(stringLine);
			m_logoSprite.setTexture(m_logo);

			sf::Vector2u textureSize = m_logo.getSize();
			m_logoSprite.setOrigin(static_cast<float>(textureSize.x / 2), static_cast<float>(textureSize.y / 2));
			m_logoSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
			m_logoSprite.setPosition(0, m_backgroundTexture.getSize().y / 2 * 0.9f);
		}

		//line 3
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			m_gameFont.loadFromFile(stringLine);
		}

		std::string redString;
		std::string greenString;
		std::string blueString;

		int redInt;
		int greenInt;
		int blueInt;


		//line 4
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			m_normalTextColor = sf::Color(redInt, greenInt, blueInt);
		}

		//LINE 5
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			m_normalOutlineColor = sf::Color(redInt, greenInt, blueInt);
		}

		//LINE 6
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			m_highlightedTextColor = sf::Color(redInt, greenInt, blueInt);
		}

		//LINE 7
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			m_highlightedOutlineColor = sf::Color(redInt, greenInt, blueInt);
		}

		std::string xBorderString;
		std::string yBorderString;

		int xBorderInt;
		int yBorderInt;

		//LINE 8
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			std::istringstream stringStream(stringLine);
			stringStream >> xBorderString;
			stringStream >> yBorderString;

			xBorderInt = std::stoi(redString);
			yBorderInt = std::stoi(greenString);

			m_menuItemBorder.x = static_cast<float>(xBorderInt);
			m_menuItemBorder.y = static_cast<float>(yBorderInt);
		}

		sf::Text start;
		start.setFont(m_gameFont);
		start.setCharacterSize(50);
		start.setStyle(sf::Text::Bold);
		start.setFillColor(m_normalTextColor);
		start.setOutlineColor(m_normalOutlineColor);
		start.setOutlineThickness(1.0f);

		sf::Vector2f textpos;

		m_menuAlignment = CENTER_JUSTIFIED;

		//LINE 9
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			if (!std::strcmp(stringLine.c_str(), "LEFT_JUSTIFIED"))
			{
				m_menuAlignment = LEFT_JUSTIFIED;
			}
			else if (!std::strcmp(stringLine.c_str(), "CENTER_JUSTIFIED"))
			{
				m_menuAlignment = CENTER_JUSTIFIED;
			}
			else if (!std::strcmp(stringLine.c_str(), "CENTRE_JUSTIFIED"))
			{
				m_menuAlignment = CENTRE_JUSTIFIED;
			}
			else if (!std::strcmp(stringLine.c_str(), "RIGHT_JUSTIFIED"))
			{
				m_menuAlignment = RIGHT_JUSTIFIED;
			}
		}

		//textpos.x = m_BackgroundRect.left + m_menuItemBoarder.x;
		//textpos.y = m_BackgroundRect.top + m_menuItemBoarder.y;

		if (m_menuAlignment == CENTRE_JUSTIFIED)
		{
			textpos.x = m_backgroundRect.left + m_backgroundRect.width / 2;
			textpos.y = m_backgroundRect.top + m_menuItemBorder.y;
		} 
		else if (m_menuAlignment == LEFT_JUSTIFIED)
		{
			textpos.x = m_backgroundRect.left + m_menuItemBorder.x;
			textpos.y = m_backgroundRect.top + m_menuItemBorder.y;
		} 
		else if (m_menuAlignment == RIGHT_JUSTIFIED)
		{
			textpos.x = m_backgroundRect.left + m_backgroundRect.width - m_menuItemBorder.x;
			textpos.y = m_backgroundRect.top + m_menuItemBorder.y;
		}

		//LINE 10+
		do
		{
			//Read everyline for each menu item
			std::getline(inputFile, stringLine);
			if (inputFile.good())
			{
				//set the text;s position to textpos
				start.setPosition(textpos.x, textpos.y);

				//set the text's string to stringLine
				start.setString(stringLine);

				//set the texts origin tyo midleft coordinate
				sf::FloatRect textbox = start.getLocalBounds();
				//start.setOrigin(0, textbox.height / 2);

				if (m_menuAlignment == CENTRE_JUSTIFIED)
				{
					start.setOrigin(textbox.width /2, textbox.height / 2);
				}
				else if (m_menuAlignment == LEFT_JUSTIFIED)
				{
					start.setOrigin(0, textbox.height / 2);
				}
				else if (m_menuAlignment == RIGHT_JUSTIFIED)
				{
					start.setOrigin(textbox.width, textbox.height / 2);
				}

				//store the texts to m_menuText array
				m_menuText.push_back(start);

				//Calculate the netxt text position by incrementing its y position
				textpos.y += start.getLocalBounds().height * 1.2f;
				if (textpos.y >= windowHeight)
				{
					textpos.y = 0;
					textpos.x += start.getLocalBounds().width;
					if (textpos.x >= windowWidth)
					{
						textpos.x = 0;
					}
				}
			}
			else
			{
				break;
			}
		} while (true);

		m_highlightIndex = 0;
		m_menuText[m_highlightIndex].setFillColor(m_highlightedTextColor);
		m_menuText[m_highlightIndex].setOutlineColor(m_highlightedOutlineColor);

		m_prevDownKeyPressed = true;
		m_prevUpKeyPressed = true;
		m_prevReturnKeyPressed = true;
	}

	//close the file
	inputFile.close();
}

SFML_GameMenu::~SFML_GameMenu()
{
	//clear the menu item list
	m_menuText.clear();
}

int SFML_GameMenu::update(sf::Time elapsedTime)
{
	bool m_currentDownKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	bool m_currentUpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool m_currentReturnKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);

	bool canChange = false;

	if (!m_currentDownKeyPressed && !m_currentUpKeyPressed)
	{
		m_quickMenuNavigationTimer = m_quickMenuNavigationDelay;
	}

	if (m_currentDownKeyPressed | m_currentUpKeyPressed)
	{
		m_quickMenuNavigationTimer -= elapsedTime.asMilliseconds();

		if (m_quickMenuNavigationTimer < 0)
		{
			m_quickMenuNavigationTimer = m_quickMenuNavigationRate;
			canChange = true;
		}
	}

	Util::Log(this, m_quickMenuNavigationTimer);

	if ((m_currentDownKeyPressed && !m_prevDownKeyPressed)|(m_currentDownKeyPressed && canChange))
	//if (m_currentDownKeyPressed && canchange)
	{
		//set the color of the CURRENT hilighted menu item to normal color
		m_menuText[m_highlightIndex].setFillColor(m_normalTextColor);
		m_menuText[m_highlightIndex].setOutlineColor(m_normalOutlineColor);

		//goto next menu item
		m_highlightIndex++;
		m_highlightIndex %= m_menuText.size();

		m_menuText[m_highlightIndex].setFillColor(m_highlightedTextColor);
		m_menuText[m_highlightIndex].setOutlineColor(m_highlightedOutlineColor);
	}
	else if ((m_currentUpKeyPressed && !m_prevUpKeyPressed) | (m_currentUpKeyPressed & canChange))
	{
		//set the color of the CURRENT hilighted menu item to normal color
		m_menuText[m_highlightIndex].setFillColor(m_normalTextColor);
		m_menuText[m_highlightIndex].setOutlineColor(m_normalOutlineColor);

		//goto previewous menu item
		m_highlightIndex--;
		m_highlightIndex %= m_menuText.size();

		m_menuText[m_highlightIndex].setFillColor(m_highlightedTextColor);
		m_menuText[m_highlightIndex].setOutlineColor(m_highlightedOutlineColor);
	}

	m_prevDownKeyPressed = m_currentDownKeyPressed;
	m_prevUpKeyPressed = m_currentUpKeyPressed;

	

	bool hasSelected = false;

	if (m_currentReturnKeyPressed && !m_prevReturnKeyPressed)
	{
		hasSelected = true;
	}

	m_prevReturnKeyPressed = m_currentReturnKeyPressed;

	if (hasSelected)
		return m_highlightIndex;
	else
		return -1;
}

void SFML_GameMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_backgroundSprite, states);
	target.draw(m_logoSprite, states);

	//draw menu items
	for (std::size_t count = 0; count < m_menuText.size(); count++)
	{
		target.draw(m_menuText[count], states);
	}
}
