#include "InputManager.h"

ListenerException::ListenerException(std::string message) : m_message(message)
{}

std::string ListenerException::GetMessage()
{
	return m_message;
}

InputManager& InputManager::GetInstance()
{
	static InputManager* m_instance = nullptr;

	if (m_instance == nullptr)
	{
		m_instance = new InputManager;
	}

	return *m_instance;
}

InputManager::InputManager()
{}

InputManager::~InputManager()
{}

bool InputManager::Update()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				NotifySubscribers(InputEvent::BUTTON_DOWN, e);
				break;
			case SDL_MOUSEBUTTONUP:
				NotifySubscribers(InputEvent::BUTTON_UP, e);
				break;
			case SDL_MOUSEWHEEL:
				NotifySubscribers(InputEvent::SCROLL, e);
				break;
			case SDL_MOUSEMOTION:
				NotifySubscribers(InputEvent::MOUSE_MOVE, e);
				break;
			case SDL_WINDOWEVENT_CLOSE:
				e.type = SDL_QUIT;
				SDL_PushEvent(&e);
				break;
			case SDL_QUIT:
				return false;
				break;
		}
	}

	return true;
}

void InputManager::SubscribeEvent(InputEvent eventType, IEventObserver* subscriber)
{
	m_subscribers[eventType].push_back(subscriber);
}

void InputManager::UnsubscribeEvent(InputEvent eventType, IEventObserver* subscriber)
{
	std::vector<IEventObserver*>& subscribers = m_subscribers[eventType];
	for (auto iter = subscribers.begin(); iter != subscribers.end(); iter++)
	{
		if ((*iter) == subscriber)
		{
			iter = subscribers.erase(iter);
			return;
		}
	}

	throw ListenerException("Subscriber not found");
}

void InputManager::NotifySubscribers(InputEvent eventType, SDL_Event& e)
{
	for (IEventObserver* subscriber : m_subscribers[eventType])
	{
		subscriber->Handle(e);
	}
}