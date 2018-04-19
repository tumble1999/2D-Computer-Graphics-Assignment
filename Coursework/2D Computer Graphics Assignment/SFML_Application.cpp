#include "SFML_Application.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include "Util.h"

SFML_Application::SFML_Application(int windowWidth, int windowHeight)
	: m_window(sf::VideoMode(windowWidth, windowHeight), "SFML Application", sf::Style::Close)
	, m_screenWidth(windowWidth)
	, m_screenHeight(windowHeight)
	, m_appState(TITLESCREEN)
	, m_titleScreen("Media/Textures/title-screen.png", windowWidth, windowHeight)
	, m_mainMenu("Media/MenuInfo/main-menu.txt", windowWidth, windowHeight)
	, m_gameWorld(windowWidth, windowHeight, &m_window)
	
	//Initialise FPS related variables
	, m_desiredUpdateTime(sf::seconds(1.f / 60.f))
	, m_timeCounter(sf::seconds(0))
	, m_FPSCounter(0)
{
	m_initialised = m_textFont.loadFromFile("./Media/Fonts/SegoeMarker.ttf");
	m_messageText.setFont(m_textFont);
	m_creditsText.setFont(m_textFont);

	m_mainMenu.setScale(0.85f, 0.85f);
	m_mainMenu.setPosition(static_cast<float>(m_screenWidth / 2), static_cast<float>(m_screenHeight / 2));



	//CREDITS

	//Create Texture
	m_creditsScreenTexture.loadFromFile("./Media/Textures/tn/tumblenet-banner.png");

	//Apply Texture to a new sprite
	m_creditsScreenSprite.setTexture(m_creditsScreenTexture);

	//set rectangle to texture area
	sf::Vector2u bkTextureSize = m_creditsScreenTexture.getSize();
	m_creditsScreenSprite.setTextureRect(sf::IntRect(0, 0, bkTextureSize.x, bkTextureSize.y));

	//set texture position to top left
	m_creditsScreenSprite.setPosition(0, 0);

	std::string creditsText;
	std::ifstream inputFile("./Media/Menuinfo/credits.txt");

	if (inputFile.is_open())
	{
		std::string stringLine;

		std::getline(inputFile, stringLine);
		while (inputFile.good())
		{
			creditsText += "\n" + stringLine;

			std::getline(inputFile, stringLine);
		}
	}
	m_creditsText.setString(creditsText);
}

SFML_Application::~SFML_Application()
{
}

void SFML_Application::run()
{
	if (!m_initialised)
		return;

	sf::Clock clock;

	//Time since last time update() was called
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{
		//time since last loop
		sf::Time elapsedTime = clock.restart();

		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > m_desiredUpdateTime)
		{
			//update app
			update(m_desiredUpdateTime);

			timeSinceLastUpdate -= m_desiredUpdateTime;
		}

		//Find out the FPS
		updateFPS(elapsedTime);

		//render
		render();
	}
}

void SFML_Application::update(sf::Time elapsedTime)
{
	//see if user requested for window to close
	bool validEventPoll = m_window.pollEvent(m_event);

	if ((m_event.type == sf::Event::Closed) && validEventPoll)
		m_window.close();

	static bool currentEscapeKeyPressed = false;
	static bool currentDownKeyPressed = false;
	static bool currentUpKeyPressed = false;
	static bool currentAnyKeyPressed = false;


	//KEY DOWN LAST FRAME
	bool lastEscapeKeyPressed = currentEscapeKeyPressed;
	bool lastDownKeyPressed = currentDownKeyPressed;
	bool lastUpKeyPressed = currentUpKeyPressed;
	bool lastAnyKeyPressed = currentAnyKeyPressed;


	//KEY DOWN NOW
	currentEscapeKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
	currentDownKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	currentUpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	currentAnyKeyPressed = m_event.type == sf::Event::KeyPressed;


	//WHEN THE KEY WAS ACTUALLY PRESSED THE IN THE CURENT FRAME
	bool currentEscapeKeyPressedNow = !lastEscapeKeyPressed && currentEscapeKeyPressed;
	bool currentDownKeyPressedNow = !lastDownKeyPressed && currentDownKeyPressed;
	bool currentUpKeyPressedNow = !lastUpKeyPressed && currentUpKeyPressed;
	bool currentAnyKeyPressedNow = !lastAnyKeyPressed && currentAnyKeyPressed;

	float buffer = 250;
	int selection;
	float windowHeight = m_window.getSize().y + m_creditsText.getLocalBounds().height + buffer*2;
	static float creditsY = m_creditsText.getPosition().y;

	

	if (m_appState != CREDITSSCREEN)
	{
		//reset pos of credits
		creditsY = static_cast<float>(m_screenHeight / 2);
		m_creditsScreenSprite.setColor(sf::Color(255, 255, 255));
	}

	switch (m_appState)
	{
	case SFML_Application::TITLESCREEN:

		if (currentAnyKeyPressed)
			m_appState = MAINMENU;

		m_titleScreen.update(elapsedTime);

		break;
	case SFML_Application::MAINMENU:
		if (currentEscapeKeyPressedNow)
		{
			m_appState = EXITING;
		}
		selection = m_mainMenu.update(elapsedTime);
		if (selection >=0)
		{
			if (selection == 0)
				m_appState = GAMEPLAYING;
			else if (selection == 1)
				m_appState = OPTIONMENU;
			else if (selection = 2)
				m_appState = CREDITSSCREEN;
			else if (selection = 3)
				m_appState = EXITING;
		}

		break;
	case SFML_Application::OPTIONMENU:
		if (currentEscapeKeyPressedNow)
			m_appState = MAINMENU;

		m_messageText.setString("Option Menu Screen");

		break;
	case SFML_Application::GAMEPLAYING:
	{
		if (currentEscapeKeyPressedNow)
			m_appState = MAINMENU;

		//m_messageText.setString("Gameplay Screen");

		//m_camera.setPosition(sf::Vector2f(0, 0));

		m_gameWorld.update(elapsedTime.asSeconds());
	}
	break;
	case SFML_Application::CREDITSSCREEN:
		if (currentEscapeKeyPressedNow)
			m_appState = MAINMENU;

		creditsY = std::fmod(
				creditsY + 0.1f,
				windowHeight
			);
		Util::Log(this,"credits: " + std::to_string(creditsY) + "/" + std::to_string(windowHeight));

		if (creditsY > m_creditsText.getLocalBounds().height / 2 + buffer && creditsY < windowHeight - m_creditsText.getLocalBounds().height / 2 - buffer)
		{
			m_creditsScreenSprite.setColor(sf::Color(
				static_cast<sf::Uint8>(m_creditsScreenSprite.getColor().r == 50.0f ? 50.0f : m_creditsScreenSprite.getColor().r - 0.00001f),
				static_cast<sf::Uint8>(m_creditsScreenSprite.getColor().g == 50.0f ? 50.0f : m_creditsScreenSprite.getColor().g - 0.00001f),
				static_cast<sf::Uint8>(m_creditsScreenSprite.getColor().b == 50.0f ? 50.0f : m_creditsScreenSprite.getColor().b - 0.00001f)
			));
		}
		else
		{
			m_creditsScreenSprite.setColor(sf::Color(
				static_cast<sf::Uint8>(m_creditsScreenSprite.getColor().r == 255.0f ? 255.0f : m_creditsScreenSprite.getColor().r + 0.00001f),
				static_cast<sf::Uint8>(m_creditsScreenSprite.getColor().g == 255.0f ? 255.0f : m_creditsScreenSprite.getColor().g + 0.00001f),
				static_cast<sf::Uint8>(m_creditsScreenSprite.getColor().b == 255.0f ? 255.0f : m_creditsScreenSprite.getColor().b + 0.00001f)
			));
		}
		

		break;
	case SFML_Application::EXITING:
		m_window.close();
		break;
	default:
		break;
	}
	m_messageText.setPosition(0,0);
	m_messageText.setCharacterSize(25);

	sf::FloatRect textbox = m_messageText.getLocalBounds();
	m_messageText.setOrigin(0,0);



	
	m_creditsText.setCharacterSize(100);
	m_creditsText.setPosition(static_cast<float>(m_screenWidth / 2), static_cast<float>(windowHeight - creditsY - m_creditsText.getLocalBounds().height/2 - buffer));

	textbox = m_creditsText.getLocalBounds();
	m_creditsText.setOrigin(textbox.width / 2, textbox.height / 2);

}

void SFML_Application::render()
{
	m_window.clear();

	switch (m_appState)
	{
	case TITLESCREEN:
		m_window.draw(m_titleScreen);
		break;
	case MAINMENU:
		m_window.draw(m_mainMenu);
		break;
	case OPTIONMENU:
		m_window.draw(m_messageText);
		break;
	case GAMEPLAYING:
		m_window.draw(m_gameWorld);
		m_window.draw(m_messageText);
		break;
	case CREDITSSCREEN:
		m_window.draw(m_creditsScreenSprite);
		m_window.draw(m_creditsText);
		break;
	case EXITING:
		break;
	default:
		break;
	}

	m_window.display();
}

void SFML_Application::updateFPS(sf::Time elapsedTime)
{
	//Increment the timeCounter by time since last renderr
	m_timeCounter += elapsedTime;

	//Increae fps counter
	m_FPSCounter += 1;
	if (m_timeCounter >= sf::seconds(1.0f))
	{
		//set the mesage text
		m_messageText.setString(
			"Refresh rate = " + std::to_string(m_FPSCounter) +
			" fps \n" +
			"Time between screen refreshes = " +
			std::to_string(m_timeCounter.asMicroseconds() / m_FPSCounter) +
			" microseconds \n" +
			"MousePos: " + std::to_string(m_gameWorld.getMousePos().x) + "," + std::to_string(m_gameWorld.getMousePos().y) + "\n"
		);

		//subtract one second from time counter
		m_timeCounter -= sf::seconds(1.0f);
		
		//reset fps counter
		m_FPSCounter = 0;
	}
}


