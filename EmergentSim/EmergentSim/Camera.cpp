#include "Camera.h"
#include "InputManager.h"

Camera::Camera(int pixelsPerUnit, float minZoomMultiplier, float maxZoomMultiplier) :
	m_pixelsPerUnit(pixelsPerUnit), m_position(0,0,Transform::Direction::UP),
	m_minZoomMultiplier(minZoomMultiplier), m_maxZoomMultiplier(maxZoomMultiplier),
	m_lastMousePosition(0,0,Transform::Direction::UP)
{
	InputManager& input = InputManager::GetInstance();
	input.SubscribeEvent(InputEvent::BUTTON_DOWN, this);
	input.SubscribeEvent(InputEvent::BUTTON_UP, this);
	input.SubscribeEvent(InputEvent::MOUSE_MOVE, this);
	input.SubscribeEvent(InputEvent::SCROLL, this);
}

Camera::~Camera()
{
	InputManager& input = InputManager::GetInstance();
	input.UnsubscribeEvent(InputEvent::BUTTON_DOWN, this);
	input.UnsubscribeEvent(InputEvent::BUTTON_UP, this);
	input.UnsubscribeEvent(InputEvent::MOUSE_MOVE, this);
	input.UnsubscribeEvent(InputEvent::SCROLL, this);
}

void Camera::Handle(SDL_Event& e)
{
	switch (e.type)
	{
		case SDL_MOUSEMOTION:
			MouseMoved(e.motion);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_MIDDLE)
				MiddleButtonDown();
			break;
		case SDL_MOUSEBUTTONUP:
			if (e.button.button == SDL_BUTTON_MIDDLE)
				MiddleButtonUp();
			break;
		case SDL_MOUSEWHEEL:
			ScrollZoom(e.wheel);
			break;
	}
}

SDL_Rect Camera::WorldToCamera(Transform worldTransform, int width, int height)
{
	SDL_Rect rend = {};
	rend.h = height * m_pixelsPerUnit *m_zoomMultiplier;
	rend.w = width * m_pixelsPerUnit *m_zoomMultiplier;

	rend.x = worldTransform.x * (m_pixelsPerUnit * m_zoomMultiplier) - m_position.x;
	rend.y = worldTransform.y * (m_pixelsPerUnit * m_zoomMultiplier) - m_position.y;

	return rend;
}

Transform Camera::CameraToWorld(SDL_Rect pixelPos)
{
	Transform pos(0,0,Transform::Direction::UP);
	pos.x = (pixelPos.x + m_position.x) / (m_pixelsPerUnit * m_zoomMultiplier);
	pos.y = (pixelPos.y + m_position.y) / (m_pixelsPerUnit * m_zoomMultiplier);

	return pos;
}

void Camera::MiddleButtonDown()
{
	m_mousePressed = true;
	SDL_GetMouseState(&m_lastMousePosition.x, &m_lastMousePosition.y);
}

void Camera::MiddleButtonUp()
{
	m_mousePressed = false;
}

void Camera::MouseMoved(SDL_MouseMotionEvent& e)
{
	if (!m_mousePressed)
		return;

	int deltaX = e.x - m_lastMousePosition.x;
	int deltaY = e.y - m_lastMousePosition.y;

	m_position.x -= deltaX;
	m_position.y -= deltaY;

	m_lastMousePosition.x = e.x;
	m_lastMousePosition.y = e.y;
}

void Camera::ScrollZoom(SDL_MouseWheelEvent& e)
{
	const float scrollAmount = 0.02f;
	const int pixelDiff = 5;

	SDL_GetMouseState(&m_lastMousePosition.x, &m_lastMousePosition.y);
	Transform mouseWorldPos = CameraToWorld(SDL_Rect{ m_lastMousePosition.x, m_lastMousePosition.y });
	mouseWorldPos.x += 1;
	mouseWorldPos.y += 1;
	if (e.y > 0)
	{
		m_zoomMultiplier += m_zoomMultiplier * pixelDiff * scrollAmount;
		if (m_zoomMultiplier > m_maxZoomMultiplier)
			m_zoomMultiplier = m_maxZoomMultiplier;
		
	}
	else
	{
		m_zoomMultiplier -= m_zoomMultiplier * pixelDiff * scrollAmount;
		if (m_zoomMultiplier < m_minZoomMultiplier)
			m_zoomMultiplier = m_minZoomMultiplier;
	}

	SDL_Rect after = WorldToCamera(mouseWorldPos);
	int offsetX = after.x - m_lastMousePosition.x;
	int offsetY = after.y - m_lastMousePosition.y;
	m_position.x += offsetX;
	m_position.y += offsetY;
}
