#pragma once

#include <glm/glm.hpp>
#include <SDL.h>

struct ProjectileEmitterComponent {
	glm::vec2 projectileVelocity;
	int repeatFrequency; 
	int projectileDuration;
	int hitDmg;
	bool isFriendly;
	int lastEmissionTime;

	ProjectileEmitterComponent(glm::vec2 projectileVelocity = glm::vec2(0), int repeatFrequency = 0, int projectileDuration = 10000,
								int hitDmg = 10, bool isFriendly = false) {
		this->projectileVelocity = projectileVelocity;
		this->repeatFrequency = repeatFrequency;
		this->projectileDuration = projectileDuration;
		this->hitDmg = hitDmg;
		this->isFriendly = isFriendly;
		this->lastEmissionTime = SDL_GetTicks();
	}
		
};