#pragma once
#include "InputManager.h"
#include "IRenderable.h"

class Button : public IEventObserver
{
public:
	Button(SDL_Renderer* renderer, SDL_Rect bounds, SDL_Color backColor);
	virtual ~Button();
	
	void SetBackColor(SDL_Color color);

	virtual void Render();

	void HandleButtonDown(SDL_MouseButtonEvent& e);
	void HandleButtonUp(SDL_MouseButtonEvent& e);
	void Handle(SDL_Event& e);

protected:
	SDL_Renderer* m_renderer;
	SDL_Rect m_buttonBounds;
	SDL_Color m_backColor;
	virtual void OnButtonClicked() = 0;

private:
	std::function<void(SDL_MouseButtonEvent&)> m_buttonDownHandler = [this](SDL_MouseButtonEvent& e) {this->HandleButtonDown(e);};
	std::function<void(SDL_MouseButtonEvent&)> m_buttonUpHandler = [this](SDL_MouseButtonEvent& e) {this->HandleButtonUp(e);};

	bool m_buttonPressed;
};

