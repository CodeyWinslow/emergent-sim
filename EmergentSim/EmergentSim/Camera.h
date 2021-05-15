#pragma once
#include <vector>
#include "SDL.h"
#include "Transform.h"
#include "IEventObserver.h"
#include "Shader.h"

namespace EmergentGraphics
{
	class Camera : public IEventObserver
	{
	public:
		Camera(SDL_Renderer* renderer, int width, int height, int pixelsPerUnit = 20, float minZoomMultiplier = 0.1f, float maxZoomMultiplier = 4.0f);
		~Camera();

		void Draw(Transform obj, SDL_Color color, int width = 1, int height = 1);
		void Draw(SDL_Rect obj, SDL_Color color);
		void Handle(SDL_Event& e);
		SDL_Rect WorldToCamera(Transform worldTransform, int width = 1, int height = 1) const;
		Transform CameraToWorld(SDL_Rect worldTransform) const;
		inline void SetRenderer(SDL_Renderer* renderer) { m_renderer = renderer; }
		void ApplyShader(Shader* shader);
		void RemoveShader(Shader* shader);
		Transform GetMinBounds() const;
		Transform GetMaxBounds() const;
		void Focus(const Transform worldTransform);

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

		bool IsCullable(SDL_Rect obj) const;
		void MiddleButtonDown();
		void MiddleButtonUp();
		void MouseMoved(SDL_MouseMotionEvent& e);
		void ScrollZoom(SDL_MouseWheelEvent& e);
	};

}