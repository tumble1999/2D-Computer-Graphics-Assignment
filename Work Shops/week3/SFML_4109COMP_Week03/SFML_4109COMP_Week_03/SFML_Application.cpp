#include "SFML_Application.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

SFML_Application::SFML_Application(int windowWidth, int windowHeight)
	: m_window(sf::VideoMode(windowWidth, windowHeight), "SFML Application", sf::Style::Fullscreen)
	, m_screenWidth(windowWidth)
	, m_screenHeight(windowHeight)
	, m_appState(TITLESCREEN)
	, m_titleScreen("Media/Textures/title-screen.png", windowWidth, windowHeight)
	, m_mainMenu("Media/MenuInfo/main-menu.txt", windowWidth, windowHeight)
{
	m_initialised = m_textFont.loadFromFile("./Media/Fonts/SegoeMarker.ttf");
	m_messageText.setFont(m_textFont);

	m_mainMenu.setScale(0.85f, 0.85f);
//	m_mainMenu.setPosition(m_screenWidth / 2, m_screenHeight / 2);
}

SFML_Application::~SFML_Application()
{}

void SFML_Application::run()
{
	if (!m_initialised)
		return;

	sf::Clock clock;

	while (m_window.isOpen())
	{
		//time since last loop
		sf::Time elapsedTime = clock.restart();

		//see if user requested for window to close
		m_window.pollEvent(m_event);
		if (m_event.type == sf::Event::Closed)
			m_window.close();

		//update app
		update(elapsedTime);

		//render
		render();
	}
}

void SFML_Application::update(sf::Time elapsedTime)
{
	bool currentEscapeKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
	bool currentDownKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	bool currentUpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool currentAnyKeyPressed = m_event.type == sf::Event::KeyPressed;

	int selection;

	if (currentEscapeKeyPressed)
	{
		m_appState = EXITING;
	}

	switch (m_appState)
	{
	case SFML_Application::TITLESCREEN:
		if (currentAnyKeyPressed)
			m_appState = MAINMENU;

		m_titleScreen.update(elapsedTime);

		break;
	case SFML_Application::MAINMENU:
		selection = m_mainMenu.update(elapsedTime);
		if (selection >=0)
		{
			if (selection == 0)
				m_appState = GAMEPLAYING;
			else if (selection == 1)
				m_appState = OPTIONMENU;
			else if (selection = 2)
				m_appState = EXITING;
		}

		break;
	case SFML_Application::OPTIONMENU:
		if (currentAnyKeyPressed)
			m_appState = GAMEPLAYING;

		m_messageText.setString("Option Menu Screen");

		break;
	case SFML_Application::GAMEPLAYING:
		if (currentAnyKeyPressed)
			m_appState = EXITING;

		m_messageText.setString("Gameplay Screen");

		break;
	case SFML_Application::EXITING:
		m_window.close();
		break;
	default:
		break;
	}
//	m_messageText.setPosition(m_screenWidth / 2, m_screenHeight / 2);
	m_messageText.setCharacterSize(100);

	sf::FloatRect textbox = m_messageText.getLocalBounds();
	m_messageText.setOrigin(textbox.width / 2, textbox.height / 2);

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
		m_window.draw(m_messageText);
		break;
	case EXITING:
		break;
	default:
		break;
	}

	m_window.display();
}
//