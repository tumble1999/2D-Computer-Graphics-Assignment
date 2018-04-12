#pragma once

#include <SFML\Graphics.hpp>
#include "SFML_TitleScreen.h"
#include "SFML_GameMenu.h"

class SFML_Application :
	public sf::NonCopyable
{
public:
	SFML_Application(int windowWidth, int windowHeight);
	~SFML_Application();
	void run();

private:
	void update(sf::Time elapsedTime);
	void render();

	bool m_initialised;

	sf::RenderWindow m_window;
	std::size_t m_screenWidth;
	std::size_t m_screenHeight;

	sf::Font m_textFont;
	sf::Text m_messageText;

	sf::Event m_event;

	enum AppState
	{
		TITLESCREEN,
		MAINMENU,
		OPTIONMENU,
		GAMEPLAYING,
		EXITING
	};

	AppState m_appState;

	SFML_TitleScreen m_titleScreen;
	SFML_GameMenu m_mainMenu;
};

