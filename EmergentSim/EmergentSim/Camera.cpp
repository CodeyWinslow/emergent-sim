#include "Camera.h"
#include "InputManager.h"

using namespace EmergentGraphics;

Camera::Camera(SDL_Renderer* renderer, int width, int height, int pixelsPerUnit, float minZoomMultiplier, float maxZoomMultiplier) :
	m_renderer(renderer), m_width(width), m_height(height),
	m_pixelsPerUnit(pixelsPerUnit), m_position(0, 0, Transform::Direction::UP),
	m_minZoomMultiplier(minZoomMultiplier), m_maxZoomMultiplier(maxZoomMultiplier),
	m_lastMousePosition(0, 0, Transform::Direction::UP),
	m_shaders(0)
{
	InputManager& input = InputManager::GetInstance();
	input.SubscribeEvent(InputEvent::BUTTON_DOWN, this);
	input.SubscribeEvent(InputEvent::BUTTON_UP, this);
	input.SubscribeEvent(InputEvent::SCROLL, this);
}

Camera::~Camera()
{
	InputManager& input = InputManager::GetInstance();
	input.UnsubscribeEvent(InputEvent::BUTTON_DOWN, this);
	input.UnsubscribeEvent(InputEvent::BUTTON_UP, this);
	input.UnsubscribeEvent(InputEvent::SCROLL, this);
}

void Camera::Draw(Transform obj, SDL_Color color, int width, int height)
{
	SDL_Rect screenPos = WorldToCamera(obj);
	Draw(screenPos, color);
}

void Camera::Draw(SDL_Rect obj, SDL_Color color)
{
	if (IsCullable(obj))
		return;

	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

	for (Shader* shader : m_shaders)
	{
		obj = shader->Compute(obj);
	}
	SDL_RenderFillRect(m_renderer, &obj);
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

void Camera::ApplyShader(Shader* shader)
{
	m_shaders.push_back(shader);
}

void Camera::RemoveShader(Shader* shader)
{
	for (auto iter = m_shaders.begin(); iter != m_shaders.end(); iter++)
	{
		if ((*iter) == shader)
		{
			iter = m_shaders.erase(iter);
			return;
		}
	}
}

Transform Camera::GetMinBounds()
{
	Transform min = CameraToWorld({ 0,0 });
	min.x--;
	min.y--;
	return min;
}

Transform Camera::GetMaxBounds()
{
	Transform max = CameraToWorld({ m_width, m_height });
	max.x++;
	max.y++;
	return max;
}

bool Camera::IsCullable(SDL_Rect obj)
{
	if (obj.x + obj.w < 0)
		return true;

	if (obj.x > m_width)
		return true;

	if (obj.y + obj.h < 0)
		return true;

	if (obj.y > m_height)
		return true;

	return false;
}

void Camera::MiddleButtonDown()
{
	m_mousePressed = true;
	InputManager::GetInstance().SubscribeEvent(InputEvent::MOUSE_MOVE, this);
	SDL_GetMouseState(&m_lastMousePosition.x, &m_lastMousePosition.y);
}

void Camera::MiddleButtonUp()
{
	m_mousePressed = false;
	InputManager::GetInstance().UnsubscribeEvent(InputEvent::MOUSE_MOVE, this);
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
	SDL_Rect innerGridOffset = WorldToCamera(mouseWorldPos);
	innerGridOffset = { m_lastMousePosition.x - innerGridOffset.x, m_lastMousePosition.y - innerGridOffset.y };
	//mouseWorldPos.x += 1;
	//mouseWorldPos.y += 1;
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
	m_position.x += offsetX + innerGridOffset.x;
	m_position.y += offsetY + innerGridOffset.y;
}
