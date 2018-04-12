#pragma once

#include <SFML/Graphics.hpp>
class SFML_GameMenu :
	public sf::Drawable, public sf::Transformable
{
public:
	SFML_GameMenu(std::string menufilename, int windowWidth, int windowHeight);
	~SFML_GameMenu();

	int update(sf::Time elapsedTime);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture m_logo;
	sf::Sprite m_logoSprite;

	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;
	sf::FloatRect m_backgroundRect;

	sf::Font m_gameFont;
	sf::Color m_highlightedTextColor;
	sf::Color m_normalTextColor;
	sf::Color m_normalOutlineColor;
	sf::Color m_highlightedOutlineColor;
	sf::Vector2f m_menuItemBorder;
	std::vector<sf::Text> m_menuText;

	enum MENU_ALIGNMENT
	{
		LEFT_JUSTIFIED,
		CENTRE_JUSTIFIED,
		CENTER_JUSTIFIED=1,
		RIGHT_JUSTIFIED
	};

	MENU_ALIGNMENT m_menuAlignment;

	int m_highlightIndex;
	bool m_prevUpKeyPressed;
	bool m_prevDownKeyPressed;
	bool m_prevReturnKeyPressed;

	float m_quickMenuNavigationDelay;
	float m_quickMenuNavigationRate;
	float m_quickMenuNavigationTimer;
};

