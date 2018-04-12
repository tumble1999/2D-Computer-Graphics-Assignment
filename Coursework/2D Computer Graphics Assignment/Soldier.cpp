#include "Soldier.h"

Soldier::Soldier(sf::Vector2f pos)
{
	setDefaultTexture("Media/Textures/soldier.png", "Media/SpriteInfo/soldier.txt");
	setPosition(pos.x, pos.y);
}


Soldier::~Soldier()
{
}
