#pragma once
#include "SDL.h"
#include "Transform.h"
#include "IEventObserver.h"

class Camera : public IEventObserver
{
public:
	Camera(int pixelsPerUnit = 40, float minZoomMultiplier = 0.15f, float maxZoomMultiplier = 8.0f);
	~Camera();

	void Handle(SDL_Event& e);
	SDL_Rect WorldToCamera(Transform worldTransform, int width = 1, int height = 1);
	Transform CameraToWorld(SDL_Rect worldTransform);

private:
	Transform m_position;
	int m_pixelsPerUnit;
	float m_zoomMultiplier = 1.0f;
	const float m_minZoomMultiplier;
	const float m_maxZoomMultiplier;
	Transform m_lastMousePosition;
	bool m_mousePressed = false;

	void MiddleButtonDown();
	void MiddleButtonUp();
	void MouseMoved(SDL_MouseMotionEvent& e);
	void ScrollZoom(SDL_MouseWheelEvent& e);
};

