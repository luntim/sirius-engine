#pragma once

#include "../EventBus/Event.h"

class EventBus;

class KeyPressedEvent : public Event {
public:
	SDL_Keycode keycode;
	std::unique_ptr<EventBus>& eventBus;
	KeyPressedEvent(SDL_Keycode keycode, std::unique_ptr<EventBus>& eventBus):
					keycode(keycode), eventBus(eventBus) {}
};