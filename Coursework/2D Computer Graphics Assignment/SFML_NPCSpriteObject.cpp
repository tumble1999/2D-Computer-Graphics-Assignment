#include "SFML_NPCSpriteObject.h"


SFML_NPCSpriteObject::SFML_NPCSpriteObject()
	: m_targetLocation(0, 0)
	, m_moveSpeed(100.0f)
	, m_state(IDLE)
	, m_idleAnimationID(-1)
	, m_walkingAnimationID(-1)
	, m_attackingAnimationID(-1)
	, m_visionConeAngle(90.0f)
	, m_visionRange(1200.0f)
{

}

SFML_NPCSpriteObject::~SFML_NPCSpriteObject()
{
}

int SFML_NPCSpriteObject::setIdleAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_idleAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_idleAnimationID;
}

int	SFML_NPCSpriteObject::setWalkingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_walkingAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_walkingAnimationID;
}

int SFML_NPCSpriteObject::setAttackingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_attackingAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_attackingAnimationID;
}

void SFML_NPCSpriteObject::toIdleState()
{
	m_state = IDLE;
	setCurrentAnimation(m_idleAnimationID);
}

void SFML_NPCSpriteObject::toWalkingState()
{
	m_state = WALKING;
	setCurrentAnimation(m_walkingAnimationID);
}

void SFML_NPCSpriteObject::toAttackingState()
{
	m_state = ATTACKING;
	setCurrentAnimation(m_attackingAnimationID);
}

void SFML_NPCSpriteObject::setTargetLocation(sf::Vector2f targetLocation)
{
	m_targetLocation = targetLocation;
}

void SFML_NPCSpriteObject::setMovementSpeed(float speed)
{
	m_moveSpeed = speed;
}

void SFML_NPCSpriteObject::update(float elapsedTime)
{

	SFML_AnimatedSpriteObject::update(elapsedTime);
}
