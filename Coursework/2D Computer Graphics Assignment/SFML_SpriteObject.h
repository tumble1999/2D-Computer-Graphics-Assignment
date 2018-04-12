#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <SFML\Graphics.hpp>


class SFML_SpriteObject :
	public sf::Drawable, public sf::Transformable
{
public:
	SFML_SpriteObject();
	virtual ~SFML_SpriteObject();

	bool setDefaultTexture(std::string textureFilename);
	bool setDefaultTexture(std::string tetureFilename, std::string spriteInfoFilename);

	void setColor(const sf::Color& color);

	sf::Vector2f getWorldPosition();
	sf::Vector2f getScreenPosition(sf::Transform cameraScreenTranform);

	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;

	virtual void update(float elpasedTime);
private:
	sf::Texture* m_defaultTexture;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	sf::Sprite m_sprite;
	sf::Texture* m_spriteTexture;
	sf::IntRect m_textureRectangle;
	sf::Vector2f m_spriteOrigin;
	bool m_initialised;

};

