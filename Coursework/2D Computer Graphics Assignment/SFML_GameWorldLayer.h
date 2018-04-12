#pragma once
#include <SFML/Graphics.hpp>
#include "SFML_2DCamera.h"

class SFML_GameWorldLayer :
	public sf::Drawable
{
public:
	SFML_GameWorldLayer(std::string textureFileName, float parallaxFactor, int viewportWidth, int viewportHeight);
	~SFML_GameWorldLayer();

	float m_parallaxFactor;

	void update(float elapsedTime);
	void followCamera(SFML_2DCamera* camera, bool enableParallaxZoom=false);
	float getParalaxFactor();
	float getY(float highestFactor);
private:
	sf::Texture m_layerTexture;
	sf::VertexArray m_layerVertices;

	sf::Vector2f m_offset;
	sf::Vector2f m_scrollSpeed;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setScrollSpeed(sf::Vector2f scrollSpeed);
};

