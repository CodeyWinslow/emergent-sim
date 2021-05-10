#pragma once
#include "InputManager.h"

class Button : public IEventObserver
{
public:
	Button(SDL_Rect bounds, SDL_Color backColor);
	~Button();
	
	void SetBackColor(SDL_Color color);

	void Render(SDL_Renderer* renderer);

	void HandleButtonDown(SDL_MouseButtonEvent& e);
	void HandleButtonUp(SDL_MouseButtonEvent& e);
	void Handle(SDL_Event& e);

protected:
	virtual void OnButtonClicked() = 0;

private:
	std::function<void(SDL_MouseButtonEvent&)> m_buttonDownHandler = [this](SDL_MouseButtonEvent& e) {this->HandleButtonDown(e);};
	std::function<void(SDL_MouseButtonEvent&)> m_buttonUpHandler = [this](SDL_MouseButtonEvent& e) {this->HandleButtonUp(e);};

	bool m_buttonPressed;
	SDL_Rect m_buttonBounds;
	SDL_Color m_backColor;
};

