#include "SFML_Application.h"

SFML_Application::SFML_Application(int windowWidth, int windowHeight)
	: m_window(sf::VideoMode(windowWidth, windowHeight), "SFML Application", sf::Style::Default)
	, m_screenWidth(windowWidth)
	, m_screenHeight(windowHeight)
	, m_appState(TITLESCREEN)
{
	m_initialised = m_textFont.loadFromFile("./Media/Fonts/SegoeMarker.ttf");
	m_messageText.setFont(m_textFont);
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
	bool currentDownKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	bool currentUpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool currentEscapeKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

	if (currentEscapeKeyPressed)
	{
		m_appState = EXITING;
	}

	switch (m_appState)
	{
	case SFML_Application::TITLESCREEN:
		if (currentDownKeyPressed)
			m_appState = MAINMENU;
		else if (currentUpKeyPressed)
			m_appState = GAMEPLAYING;

		m_messageText.setString("Title Screen");

		break;
	case SFML_Application::MAINMENU:
		if (currentDownKeyPressed)
			m_appState = OPTIONMENU;
		else if (currentUpKeyPressed)
			m_appState = TITLESCREEN;

		m_messageText.setString("Main Menu Screen");

		break;
	case SFML_Application::OPTIONMENU:
		if (currentDownKeyPressed)
			m_appState = GAMEPLAYING;
		else if (currentUpKeyPressed)
			m_appState = MAINMENU;

		m_messageText.setString("Option Menu Screen");

		break;
	case SFML_Application::GAMEPLAYING:
		if (currentDownKeyPressed)
			m_appState = TITLESCREEN;
		else if (currentUpKeyPressed)
			m_appState = OPTIONMENU;

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
	m_window.draw(m_messageText);
	m_window.display();
}
