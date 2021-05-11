#pragma once
#include <vector>
#include "SDL.h"
#include "Transform.h"
#include "IEventObserver.h"
#include "Shader.h"

class Camera : public IEventObserver
{
public:
	Camera(SDL_Renderer* renderer, int width, int height, int pixelsPerUnit = 40, float minZoomMultiplier = 0.05f, float maxZoomMultiplier = 8.0f);
	~Camera();

	void Draw(Transform obj, SDL_Color color, int width = 1, int height = 1);
	void Draw(SDL_Rect obj, SDL_Color color);
	void Handle(SDL_Event& e);
	SDL_Rect WorldToCamera(Transform worldTransform, int width = 1, int height = 1);
	Transform CameraToWorld(SDL_Rect worldTransform);
	inline void SetRenderer(SDL_Renderer* renderer) { m_renderer = renderer; }
	void ApplyShader(Shader* shader);
	void RemoveShader(Shader* shader);
	Transform GetMinBounds();
	Transform GetMaxBounds();

private:
	SDL_Renderer* m_renderer;
	Transform m_position;
	int m_width;
	int m_height;
	int m_pixelsPerUnit;
	float m_zoomMultiplier = 1.0f;
	const float m_minZoomMultiplier;
	const float m_maxZoomMultiplier;
	Transform m_lastMousePosition;
	bool m_mousePressed = false;
	std::vector<Shader*> m_shaders;

	bool IsCullable(SDL_Rect obj);
	void MiddleButtonDown();
	void MiddleButtonUp();
	void MouseMoved(SDL_MouseMotionEvent& e);
	void ScrollZoom(SDL_MouseWheelEvent& e);
};

