#pragma once
#include <vector>
#include "UIComponent.h"

using std::vector;

namespace EmergentGraphics
{
	class UICanvas : public UIComponent
	{
	public:
		UICanvas(SDL_Renderer* renderer, SDL_Rect bounds);
		virtual ~UICanvas();

		virtual void Render();

	protected:
		void AddComponent(UIComponent* component);
	private:
		vector<UIComponent*> m_uiComponents;
	};
}