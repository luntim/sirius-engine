#pragma once

#include <SDL.h>

struct ProjectileComponent {
	bool isFriendly;
	int hitDmg;
	int duration;
	int startTime;

	ProjectileComponent(bool isFriendly = false, int hitDmg = 0, int duration = 0) {
		this->isFriendly = isFriendly;
		this->hitDmg = hitDmg;
		this->duration = duration;
		this->startTime = SDL_GetTicks();
	}
};
