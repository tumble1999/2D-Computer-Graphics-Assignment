#pragma once
#include "SFML_SpriteObject.h"

#include "SFML_SpriteAnimation.h"

class SFML_AnimatedSpriteObject :
	public SFML_SpriteObject
{
public:
	SFML_AnimatedSpriteObject();
	virtual ~SFML_AnimatedSpriteObject();

	int addAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);

	void setCurrentAnimation(int animationIndex);

	SFML_SpriteAnimation* getCurrentAnimation();

	virtual void update(float elapsedTime);
	
	void play();
	void pause();
	void stop();

protected:
	std::vector <SFML_AnimatedSpriteObject*> m_animatedSpriteList;
	SFML_SpriteAnimation* m_currentAnimation;
};

