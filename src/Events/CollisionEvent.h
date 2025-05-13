#pragma once

#include "../EventBus/Event.h"

class Entity;

class CollisionEvent: public Event {
public:
	Entity a;
	Entity b;
	CollisionEvent(Entity a, Entity b): a(a), b(b) {}
};