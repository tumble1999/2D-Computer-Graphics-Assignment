#pragma once
#include "SFML_PlayableSpriteObject.h"

#include "SFML_BulletSpriteObject.h"
#include "SFML_2DCamera.h"

class Player :
	public SFML_PlayableSpriteObject
{
public:
	Player();
	~Player();
	void processEvents(float elapsedTime, sf::Transform transform, sf::Vector2f mouseScreenPosition);
	void update(float elapsedTime, SFML_2DCamera & camera);
private:
	std::vector<SFML_BulletSpriteObject*> m_bulletList;

	void draw(sf::RenderTarget & target, sf::RenderStates states);
};

