#pragma once

#include "../EventBus/Event.h"

class EventBus;
class Entity;

class PrimaryFireEvent : public Event {
public:
	Entity entity;
	std::unique_ptr<EventBus>& eventBus;
	
	// Later have to add raycast etc
	PrimaryFireEvent(Entity entity, std::unique_ptr<EventBus>& eventBus):
					entity(entity), eventBus(eventBus) {}
};
