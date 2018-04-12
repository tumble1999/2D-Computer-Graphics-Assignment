#pragma once

#include <SFML/Graphics.hpp>
#include "SFML_GameWorldLayer.h"
#include "SFML_SpriteObject.h"
#include "Soldier.h"

class SFML_GameWorld :
	public sf::Drawable
{
public:
	SFML_GameWorld(int windowWidth, int windowHeight, sf::RenderWindow * parentWindow);
	~SFML_GameWorld();

	void update(float elapsedTime);
	sf::Vector2f getMousePos();
private:
	void processEvents(float elapsedTime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	static bool layerSortFunction(SFML_GameWorldLayer* a, SFML_GameWorldLayer* b);

	int m_windowWidth;
	int m_windowHeight;
	sf::RenderWindow* m_parentWindow;

	std::vector<SFML_GameWorldLayer*> m_gameWorldLayerList;
	SFML_2DCamera m_camera;
	sf::Vector2f m_cameraPosition;
	std::vector<Soldier*> m_soldiers;
};
