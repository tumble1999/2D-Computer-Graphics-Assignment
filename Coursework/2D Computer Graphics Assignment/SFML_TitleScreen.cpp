#include "SFML_TitleScreen.h"

SFML_TitleScreen::SFML_TitleScreen(std::string texturefilename, int windowWidth, int windowHeight)
{
	//Create Texture
	m_titleScreenTexture.loadFromFile(texturefilename);

	//Apply Texture to a new sprite
	m_titleScreenSprite.setTexture(m_titleScreenTexture);

	//set rectangle to texture area
	sf::Vector2u bkTextureSize = m_titleScreenTexture.getSize();
	m_titleScreenSprite.setTextureRect(sf::IntRect(0, 0, bkTextureSize.x, bkTextureSize.y));

	//set texture position to top left
	m_titleScreenSprite.setPosition(0, 0);


	//Create press any key texture
	m_messageTexture.loadFromFile("Media/Textures/continue.png");

	//appy texture to a new sprite
	m_messageSprite.setTexture(m_messageTexture);

	//place on the screen
	m_messageSprite.setPosition(windowWidth*0.5f, windowHeight*0.75f);

	//center the image
	sf::Vector2u msgTextureSize = m_messageTexture.getSize();
	m_messageSprite.setOrigin(static_cast<float>(msgTextureSize.x) / 2, static_cast<float>(msgTextureSize.y) / 2);

	//set rectangkle to cover texture area
	m_messageSprite.setTextureRect(sf::IntRect(0, 0, msgTextureSize.x, msgTextureSize.y));

	//tint texture
	m_messageSprite.setColor(sf::Color(255, 0, 0));

	//control flashing
	m_timeSinceLastFlash = sf::Time::Zero;
	m_flashingTime = sf::seconds(0.0167f);
}

SFML_TitleScreen::~SFML_TitleScreen()
{

}

void SFML_TitleScreen::update(sf::Time elapsedTime)
{
	m_timeSinceLastFlash += elapsedTime;

	if (m_timeSinceLastFlash > m_flashingTime)
	{
		m_flashon = !m_flashon;
		m_timeSinceLastFlash -= m_flashingTime;
		if (m_flashon)
			m_messageSprite.setColor(sf::Color(255, 255, 255));
		else
			m_messageSprite.setColor(sf::Color(255, 0, 0));
	}
}

void SFML_TitleScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_titleScreenSprite);
	target.draw(m_messageSprite);
}
