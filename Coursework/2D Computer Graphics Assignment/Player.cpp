#include "Player.h"



Player::Player()
{
	setFlashlightIdleAnimation("Media/Textures/hero_flashshlight_idle.png", "Media/SpriteInfo/hero_flashshlight_idle.txt", 1.0f);
	setFlashlightMeleeAnimation("Media/Textures/hero_flashshlight_idle.png", "Media/SpriteInfo/hero_flashshlight_idle.txt", 1.0f);
	setFlashlightWalkingAnimation("Media/Textures/hero_flashshlight_idle.png", "Media/SpriteInfo/hero_flashshlight_idle.txt", 1.0f);
}


Player::~Player()
{}

void Player::update(float elapsedTime)
{
	SFML_PlayableSpriteObject::update(elapsedTime);
}

//void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
//{
	//target.draw((SFML_PlayableSpriteObject) *this,states);
//}
