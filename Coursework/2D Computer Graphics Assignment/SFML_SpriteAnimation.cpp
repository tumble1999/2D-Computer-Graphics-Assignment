#include "SFML_SpriteAnimation.h"



SFML_SpriteAnimation::SFML_SpriteAnimation()
	: m_currentFrameNumber(0)
	, m_canbeInterrupted(true)
	, m_isLoop(true)

{
}


SFML_SpriteAnimation::~SFML_SpriteAnimation()
{
	m_frameCentreList.clear();
	m_frameRectangleList.clear();
}


void SFML_SpriteAnimation::setSpriteSheet(sf::Texture* spriteTexture)
{
	m_spritesheet = spriteTexture;
}


void SFML_SpriteAnimation::addFrame(sf::IntRect textureRect, sf::Vector2f centre)
{
	m_frameRectangleList.push_back(textureRect);
	m_frameCentreList.push_back(centre);
}


bool SFML_SpriteAnimation::getCurrentFrame(sf::IntRect* rect, sf::Vector2f* centre)
{
	if ((m_currentFrameNumber < 0)
		|| (m_currentFrameNumber >= m_frameRectangleList.size()))
	{
		return false;
	}
	sf::IntRect irect = m_frameRectangleList[m_currentFrameNumber];
	sf::Vector2f icentre = m_frameCentreList[m_currentFrameNumber];

	rect->left = irect.left;
	rect->top = irect.top;
	rect->width = irect.width;
	rect->height = irect.height;

	centre->x = icentre.x;
	centre->y = icentre.y;
	return true;
}


void SFML_SpriteAnimation::setFrameTime(float timeperFrame)
{
	m_timeperFrame = timeperFrame;
}


float SFML_SpriteAnimation::getTimePerFrame()
{
	return m_timeperFrame;
}


sf::Texture* SFML_SpriteAnimation::getSpriteSheet()
{
	return m_spritesheet;
}


int SFML_SpriteAnimation::getNumberOfFrames()
{
	return 0;
}


void SFML_SpriteAnimation::getTextureInfo(int newFrame, sf::IntRect* rect, sf::Vector2f* centre)
{}


void SFML_SpriteAnimation::setLoop(bool loop)
{
	m_isLoop = loop;
}


bool SFML_SpriteAnimation::isLooped() const
{
	return m_isLoop;
}


void SFML_SpriteAnimation::setCanbeInterrupted(bool trueorfalse)
{
	m_canbeInterrupted = trueorfalse;
}


bool SFML_SpriteAnimation::canbeInterrupted() const
{
	return m_canbeInterrupted;
}

void SFML_SpriteAnimation::incrementFrameNumber()
{
	m_currentFrameNumber++;
	if (m_currentFrameNumber >= m_frameRectangleList.size() - 1)
	{
		if (m_isLoop)
		{
			resetCurrentAnimation();
		} else {
			m_currentFrameNumber = m_frameRectangleList.size() - 1;
		}
	}
}


int SFML_SpriteAnimation::getCurrentFrameNumber()
{
	return m_currentFrameNumber;
}

void SFML_SpriteAnimation::resetCurrentAnimation()
{
	m_currentFrameNumber = 0;
}


bool SFML_SpriteAnimation::isCompleted()
{
	if (m_currentFrameNumber >= m_frameRectangleList.size() - 1)
	{
		return true;
	}
	return false;
}
