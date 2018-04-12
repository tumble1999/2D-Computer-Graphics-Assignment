#pragma once
#include "SFML_SpriteObject.h"
class Soldier :
	public SFML_SpriteObject
{
public:
	Soldier(sf::Vector2f pos);
	~Soldier();
};

