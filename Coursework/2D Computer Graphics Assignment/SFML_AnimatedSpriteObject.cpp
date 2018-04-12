#include "SFML_AnimatedSpriteObject.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

SFML_AnimatedSpriteObject::SFML_AnimatedSpriteObject()
{}


SFML_AnimatedSpriteObject::~SFML_AnimatedSpriteObject()
{}

int SFML_AnimatedSpriteObject::addAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	return 0;
}

void SFML_AnimatedSpriteObject::setCurrentAnimation(int animationIndex)
{}

SFML_SpriteAnimation * SFML_AnimatedSpriteObject::getCurrentAnimation()
{
	return nullptr;
}

void SFML_AnimatedSpriteObject::update(float elapsedTime)
{}

void SFML_AnimatedSpriteObject::play()
{}

void SFML_AnimatedSpriteObject::pause()
{}

void SFML_AnimatedSpriteObject::stop()
{}
