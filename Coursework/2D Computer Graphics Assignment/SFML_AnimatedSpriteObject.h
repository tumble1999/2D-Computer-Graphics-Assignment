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

	virtual void updarte(float elapsedTime);
	
	void play();
	void pause();
	void stop();
};

