#include "SFML_GameWorld.h"
#include <math.h>
#include "Util.h"

SFML_GameWorld::SFML_GameWorld(int windowWidth, int windowHeight, sf::RenderWindow* parentWindow)
	: m_windowWidth(windowWidth)
	, m_windowHeight(windowHeight)
	, m_camera(windowWidth, windowHeight)
{

	SFML_GameWorldLayer* background = new SFML_GameWorldLayer("Media/Textures/wall.png",
		1.0f,
		windowWidth, windowHeight);
	m_gameWorldLayerList.push_back(background);

	SFML_GameWorldLayer* middleground = new SFML_GameWorldLayer("Media/Textures/fog.png",
		0.65f,
		windowWidth, windowHeight);
	m_gameWorldLayerList.push_back(middleground);

	SFML_GameWorldLayer* foreground = new SFML_GameWorldLayer("Media/Textures/wire.png",
		0.3f,
		windowWidth, windowHeight);
	m_gameWorldLayerList.push_back(foreground);

	std::sort(m_gameWorldLayerList.begin(), m_gameWorldLayerList.end(), layerSortFunction);

	m_cameraPosition = sf::Vector2f(0, 0);

	/*m_spriteObject.setDefaultTexture("Media/Textures/soldier.png", "Media/SpriteInfo/soldier.txt");

	m_spriteObject.setPosition(0, 0);*/

	int maxXY = 5000;
	int solderCount = 99;

	int fullMax = maxXY * 2;

	for (int i = 0; i < solderCount; i++)
	{
		int randX = (rand() % fullMax) - maxXY;
		int randY = (rand() % fullMax) - maxXY;
		sf::Vector2f randPos = sf::Vector2f(static_cast<float>(randX), static_cast<float>(randY));
		m_soldiers.push_back(new Soldier(randPos));
	}


	m_parentWindow = parentWindow;

	m_animatedObject = new SFML_AnimatedSpriteObject();
	m_idleAnimationID = m_animatedObject->addAnimation("Media/Textures/zombie-move.png",
		"Media/SpriteInfo/zombie-move.txt",
		1.0f);
	m_animatedObject->setPosition(0, 0);
	m_animatedObject->setCurrentAnimation(m_idleAnimationID);

	m_numberofZombies = 3;

	for (int i = 0; i < m_numberofZombies; i++)
	{
		SFML_NPCSpriteObject* npcSprite = new SFML_NPCSpriteObject();
		npcSprite->setIdleAnimation("Media/Textures/zombie-idle.png", "Media/SpriteInfo/zombie-idle.txt", 1.0f);
		npcSprite->setWalkingAnimation("Media/Textures/zombie-walking.png", "Media/SpriteInfo/zombie-walking.txt", 1.0f);
		npcSprite->setAttackingAnimation("Media/Textures/zombie-attack.png", "Media/SpriteInfo/zombie-attacke.txt", 1.0f);

		npcSprite->setPosition(static_cast<float>(rand() % 4000 - 2000), static_cast<float>(rand() % 4000 - 2000));
		npcSprite->setTargetLocation(sf::Vector2f(static_cast<float>(rand() % 4000 - 2000), static_cast<float>(rand() % 4000 - 2000)));
		m_zombieCharacterList.push_back(npcSprite);
	}

	m_shiftKeyWasPressed = false;
	m_ctrlKeyWasPressed = false;
}

SFML_GameWorld::~SFML_GameWorld()
{
	for (std::vector<SFML_GameWorldLayer*>::iterator it = m_gameWorldLayerList.begin(); it != m_gameWorldLayerList.end(); it++)
	{
		delete(*it);
	}
	for (std::vector<Soldier*>::iterator it = m_soldiers.begin(); it != m_soldiers.end(); it++)
	{
		delete(*it);
	}
	m_gameWorldLayerList.clear();

	delete m_animatedObject;
}

void SFML_GameWorld::update(float elapsedTime)
{
	processEvents(elapsedTime);
	m_camera.setPosition(m_cameraPosition);

	for (std::size_t counter = 0; counter < m_gameWorldLayerList.size(); counter++)
	{
		m_gameWorldLayerList[counter]->followCamera(&m_camera, true);
		m_gameWorldLayerList[counter]->update(elapsedTime);
	}

	for (size_t i = 0; i < m_soldiers.size(); i++) {
		m_soldiers[i]->update(elapsedTime);
	}

	m_animatedObject->update(elapsedTime);

	for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++)
	{
		m_zombieCharacterList[counter]->update(elapsedTime);
	}
}

sf::Vector2f SFML_GameWorld::getMousePos()
{
	sf::Transform transform;
	transform = m_camera.getProjTransform() * m_camera.getViewTransform();

	sf::Transform inv = transform.getInverse();

	sf::Vector2f mouseScreenPosition = sf::Vector2f(sf::Mouse::getPosition(*m_parentWindow));

	sf::Vector2f wp = inv.transformPoint(mouseScreenPosition);
	return wp;
}

void SFML_GameWorld::processEvents(float elapsedTime)
{
	bool shiftKeyIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
	bool ctrlKeyIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);

	float cameraPanSpeed = 60.0f;
	float cameraSpeedMultiplier = 4.0f;
	cameraPanSpeed *= cameraSpeedMultiplier;

	if (shiftKeyIsPressed & m_shiftKeyWasPressed)
	{
		cameraPanSpeed *= cameraSpeedMultiplier;
	}
	if (ctrlKeyIsPressed & m_ctrlKeyWasPressed)
	{
		cameraPanSpeed /= cameraSpeedMultiplier;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_cameraPosition.x -= cameraPanSpeed * elapsedTime;// .asSeconds();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_cameraPosition.x += cameraPanSpeed * elapsedTime;//.asSeconds();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_cameraPosition.y -= cameraPanSpeed * elapsedTime;//.asSeconds();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_cameraPosition.y += cameraPanSpeed * elapsedTime;//.asSeconds();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
	{
		m_camera.zoomUp(elapsedTime);//.asSeconds());
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
	{
		m_camera.zoomDown(elapsedTime);//.asSeconds());
	}

	
	m_shiftKeyWasPressed = shiftKeyIsPressed;
	m_ctrlKeyWasPressed = ctrlKeyIsPressed;


	sf::Vector2f wp = getMousePos();

	for (size_t i = 0; i < m_soldiers.size(); i++)
	{
		sf::FloatRect rect = m_soldiers[i]->getGlobalBounds();

		if (rect.contains(wp))
		{
			m_soldiers[i]->setColor(sf::Color(244, 67, 54));

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				Util::Log(this, "Left mouse button pressed");
				m_cameraPosition = m_soldiers[i]->getPosition();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			{
				Util::Log(this, "Middle mouse button pressed");
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				Util::Log(this, "Right mouse button pressed");
			}
		}
		else
		{
			m_soldiers[i]->setColor(sf::Color(255, 255, 266));
		}
	}
	
}

void SFML_GameWorld::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	float far = 10;
	for (std::size_t counter = 0; counter < m_gameWorldLayerList.size(); counter++)
	{
		if (m_gameWorldLayerList[counter]->getParalaxFactor() >=1.0f)
		{
			float layerY = m_gameWorldLayerList[counter]->getY(m_gameWorldLayerList[0]->getParalaxFactor());
			float cameraY = m_camera.getCameraZoom();
			if ((cameraY > (layerY - 0.2f)) & (far > cameraY))
			{
				target.draw(*m_gameWorldLayerList[counter]);
			}
		}
	}

	sf::RenderStates renderState;
	renderState.transform = m_camera.getProjTransform() * m_camera.getViewTransform();

	target.draw(*m_animatedObject, renderState);

	for (size_t i = 0; i < m_soldiers.size(); i++) {
		target.draw(*m_soldiers[i], renderState);
	}

	for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++)
	{
		target.draw(*m_zombieCharacterList[counter], renderState);
	}

	for (std::size_t counter = 0; counter < m_gameWorldLayerList.size(); counter++)
	{
		if (m_gameWorldLayerList[counter]->getParalaxFactor() < 1.0f)
		{
			float layerY = m_gameWorldLayerList[counter]->getY(m_gameWorldLayerList[0]->getParalaxFactor());
			float cameraY = m_camera.getCameraZoom();
			if ((cameraY > (layerY - 0.2f)) & (far > cameraY))
			{
				target.draw(*m_gameWorldLayerList[counter]);
			}
		}
	}
}

bool SFML_GameWorld::layerSortFunction(SFML_GameWorldLayer * a, SFML_GameWorldLayer * b)
{
	return (a->getParalaxFactor() > b->getParalaxFactor());
}
