#pragma once

#include <SFML\Graphics.hpp>
#include "SFML_TitleScreen.h"
#include "SFML_GameMenu.h"

#include "SFML_GameWorldLayer.h"

#include "SFML_GameWorld.h"

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

	//update fps data
	void updateFPS(sf::Time elapsedTime);

	bool m_initialised;

	sf::RenderWindow m_window;
	std::size_t m_screenWidth;
	std::size_t m_screenHeight;

	//These variables will help in calculating the fps
	sf::Time m_timeCounter;
	sf::Time m_desiredUpdateTime;
	std::size_t m_FPSCounter;

	sf::Texture m_creditsScreenTexture;
	sf::Sprite m_creditsScreenSprite;

	sf::Font m_textFont;
	sf::Text m_messageText;
	sf::Text m_creditsText;

	sf::Event m_event;


	SFML_GameWorld m_gameWorld;

	enum AppState
	{
		TITLESCREEN,
		MAINMENU,
		OPTIONMENU,
		GAMEPLAYING,
		CREDITSSCREEN,
		EXITING
	};

	AppState m_appState;

	SFML_TitleScreen m_titleScreen;
	SFML_GameMenu m_mainMenu;
};


