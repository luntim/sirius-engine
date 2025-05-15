#pragma once

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"

class DamageSystem : public System {
public:
	DamageSystem() {
		RequireComponent<BoxColliderComponent>();
	}

	void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
		eventBus->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::onCollision);
	}

	void onCollision(CollisionEvent& event) {
		Entity a = event.a;
		Entity b = event.b;
		Logger::Log("The damage system recieved an event between entities " + std::to_string(a.GetId())
			+ " and " + std::to_string(b.GetId()) );
		
		// Collision between projectiles and player
		if (a.BelongsToGroup("projectiles") && b.HasTag("player")) {
			OnProjectileHitsPlayer(a, b); // a is projectile, b is the player
		}
		if (b.BelongsToGroup("projectiles") && a.HasTag("player")) {
			OnProjectileHitsPlayer(b, a); // b is projectile, a is the player
		}
		// Collision between projectiles and enemies
		if (a.BelongsToGroup("projectiles") && b.BelongsToGroup("enemies")) {
			OnProjectileHitsEnemy(b, a); // b is projectile, a is the player
		}

		if (b.BelongsToGroup("projectiles") && a.BelongsToGroup("enemies")) {
			OnProjectileHitsEnemy(b, a); // b is projectile, a is the player
		}
	}

	void OnProjectileHitsPlayer(Entity projectile, Entity player) {
		auto projectileComponent = projectile.GetComponent<ProjectileComponent>();
		
		if (!projectileComponent.isFriendly) {
			auto& hpComponent = player.GetComponent<HealthComponent>();
			hpComponent.health -= projectileComponent.hitDmg;

			if (hpComponent.health <= 0) {
				player.Kill();
			}

			projectile.Kill();
		}
	}

	void OnProjectileHitsEnemy(Entity projectile, Entity enemy) {
		auto projectileComponent = projectile.GetComponent<ProjectileComponent>();

		if (projectileComponent.isFriendly) {
			auto& hpComponent = enemy.GetComponent<HealthComponent>();
			hpComponent.health -= projectileComponent.hitDmg;

			if (hpComponent.health <= 0) {
				enemy.Kill();
			}

			projectile.Kill();
		}
	}

	void Update() {	
		// TODO: ...
	}

};