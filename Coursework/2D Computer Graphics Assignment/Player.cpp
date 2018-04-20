#include "Player.h"

Player::Player()
{
	setFlashlightIdleAnimation("Media/Textures/hero_flashlight_idle.png", "Media/SpriteInfo/hero_flashlight_idle.txt", 1.0f);
	setFlashlightMeleeAnimation("Media/Textures/hero_flashlight_idle.png", "Media/SpriteInfo/hero_flashlight_idle.txt", 1.0f);
	setFlashlightWalkingAnimation("Media/Textures/hero_flashlight_idle.png", "Media/SpriteInfo/hero_flashlight_idle.txt", 1.0f);

	equipFlashlight();
	toIdleState();

	setPosition(0, 0);
}


Player::~Player()
{}

void Player::update(float elapsedTime, SFML_2DCamera& camera) {
	SFML_PlayableSpriteObject::update(elapsedTime);
	camera.setPosition(getWorldPosition());

	for (unsigned int counter = 0; counter < m_bulletList.size(); counter++)
	{
		m_bulletList[counter]->update(elapsedTime);
	}

}

void Player::processEvents(float elapsedTime, sf::Transform transform, sf::Vector2f mouseScreenPosition) {
	SFML_BulletSpriteObject* bullet = SFML_PlayableSpriteObject::processEvents(elapsedTime, transform, mouseScreenPosition);
	if (bullet)
	{
		m_bulletList.push_back(bullet);
	}
}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) {
	target.draw((SFML_PlayableSpriteObject)*this, states);
	for (unsigned int counter = 0; counter < m_bulletList.size(); counter++)
	{
		target.draw(*m_bulletList[counter], states);
	}
}
