#include "SFML_2DCamera.h"

SFML_2DCamera::SFML_2DCamera(int projectionWindowWidth, int projectionWindowHeight)
	: m_cameraPosition(0, 0)
	, m_cameraWindowSize(static_cast<float>(projectionWindowWidth), static_cast<float>(projectionWindowHeight))
	, m_cameraZoom(1)
	, m_lastCameraZoom(1)
{}

SFML_2DCamera::~SFML_2DCamera()
{}

sf::FloatRect SFML_2DCamera::getCameraWindow(float parallaxFactor, bool enableParallaxZoom)
{

	sf::FloatRect window;
	float tmp_cameraZoom = enableParallaxZoom
		? ((m_cameraZoom-m_lastCameraZoom) +parallaxFactor-0.75f )+m_lastCameraZoom 
		: m_cameraZoom;

	window.left = m_cameraPosition.x - m_cameraWindowSize.x / 2 * tmp_cameraZoom * parallaxFactor;
	window.top = m_cameraPosition.y - m_cameraWindowSize.y / 2 * tmp_cameraZoom * parallaxFactor;

	window.width = m_cameraWindowSize.x * tmp_cameraZoom * parallaxFactor;
	window.height = m_cameraWindowSize.y * tmp_cameraZoom * parallaxFactor;

	return window;
}

void SFML_2DCamera::setPosition(sf::Vector2f target)
{
	m_cameraPosition = target;
}

void SFML_2DCamera::zoomUp(float elapsedTime)
{
	m_lastCameraZoom = m_cameraZoom;
	float zoomSpeed = 30.0f;
	float zoomChange = m_cameraZoom * 0.1f * elapsedTime * zoomSpeed;
	m_cameraZoom -= zoomChange;
}

void SFML_2DCamera::zoomDown(float elapsedTime)
{
	m_lastCameraZoom = m_cameraZoom;
	float zoomSpeed = 30.0f;
	float zoomChange = m_cameraZoom * 0.1f * elapsedTime * zoomSpeed;
	m_cameraZoom += zoomChange;
}

float SFML_2DCamera::getCameraZoom() const
{
	return m_cameraZoom;
}

sf::Transform SFML_2DCamera::getViewTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	transform.translate(m_cameraPosition);
	return transform.getInverse();
}

sf::Transform SFML_2DCamera::getProjTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	transform.translate(m_cameraWindowSize.x / 2, m_cameraWindowSize.y / 2);
	transform.scale(1.0f / m_cameraZoom, 1.0f / m_cameraZoom);
	return transform;
}
