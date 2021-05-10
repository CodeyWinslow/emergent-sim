#pragma once
#include <functional>
#include <vector>
#include <string>
#include <unordered_map>
#include "SDL.h"
#include "IEventObserver.h"

class ListenerException {
public:
	ListenerException(std::string message);
	std::string GetMessage();

private:
	std::string m_message;
};

enum class InputEvent {
	BUTTON_DOWN,
	BUTTON_UP,
	SCROLL,
	MOUSE_MOVE
};

typedef void(*ButtonClickListener)(SDL_MouseButtonEvent&);
typedef void(*ScrollListener)(SDL_MouseWheelEvent&);
class InputManager
{
public:
	static InputManager& GetInstance();
	
	~InputManager();

	bool Update();

	void SubscribeEvent(InputEvent eventType, IEventObserver* subscriber);
	void UnsubscribeEvent(InputEvent eventType, IEventObserver* subscriber);
	void NotifySubscribers(InputEvent eventType, SDL_Event& e);

private:
	std::unordered_map<InputEvent, std::vector<IEventObserver*>> m_subscribers = {};

	InputManager();
};