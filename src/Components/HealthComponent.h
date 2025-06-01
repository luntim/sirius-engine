#pragma once

struct HealthComponent {
	int health;
	int startingHealth;
	std::string fontAssetId;

	HealthComponent(int health = 100, std::string fontAssetId = "") {
		this->health = health;
		this->fontAssetId = fontAssetId;
		this->startingHealth = health;
	}
};