#pragma once
#include "SFML_PlayableSpriteObject.h"
class Player :
	public SFML_PlayableSpriteObject
{
public:
	Player();
	~Player();

	void update(float elapsedTime);

private:
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

