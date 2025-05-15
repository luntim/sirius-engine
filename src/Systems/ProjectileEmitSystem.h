#pragma once

#include <SDL.h>
#include <glm/glm.hpp>
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Events/PrimaryFireEvent.h"
#include "../Logger/Logger.h"

class ProjectileEmitSystem : public System {
public:
	ProjectileEmitSystem() {
		RequireComponent<ProjectileEmitterComponent>();
		RequireComponent<TransformComponent>();
	}

	void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
		eventBus->SubscribeToEvent<PrimaryFireEvent>(this, &ProjectileEmitSystem::OnPrimaryFire);
	}

	void OnPrimaryFire(PrimaryFireEvent& event) {
		auto entity = event.entity;
		auto& projectileEmitter = entity.GetComponent<ProjectileEmitterComponent>();
		auto rigidbody = event.entity.GetComponent<RigidBodyComponent>();
		auto transform = event.entity.GetComponent<TransformComponent>();

		glm::vec2 projectilePosition = transform.position;
		if (entity.HasComponent<SpriteComponent>()) {
			auto sprite = entity.GetComponent<SpriteComponent>();
			projectilePosition.x += (transform.scale.x * sprite.width / 2);
			projectilePosition.y += (transform.scale.y * sprite.height / 2);
		}

		glm::vec2 projectileVelocity = projectileEmitter.projectileVelocity;
		int directionX = 0;
		int directionY = 0;
		if (rigidbody.velocity.x > 0) directionX += 1;
		if (rigidbody.velocity.x < 0) directionX -= 1;
		if (rigidbody.velocity.y > 0) directionY += 1;
		if (rigidbody.velocity.y < 0) directionY -= 1;
		projectileVelocity.x = projectileEmitter.projectileVelocity.x * directionX;
		projectileVelocity.y = projectileEmitter.projectileVelocity.y * directionY;

		Entity projectile = entity.registry->CreateEntity();
		projectile.Group("projectiles");
		projectile.AddComponent<TransformComponent>(projectilePosition, glm::vec2(1.0, 1.0), 0.0);
		projectile.AddComponent<RigidBodyComponent>(projectileVelocity);
		projectile.AddComponent<SpriteComponent>("bullet-image", 4, 4, 4);
		projectile.AddComponent<BoxColliderComponent>(4, 4);
		projectile.AddComponent<ProjectileComponent>(projectileEmitter.isFriendly, projectileEmitter.hitDmg, projectileEmitter.projectileDuration);
	}

	void Update(std::unique_ptr<Registry>& registry) {
		for (auto entity : GetSystemEntities()) {
			auto& projectileEmitter = entity.GetComponent<ProjectileEmitterComponent>();
			const auto transform = entity.GetComponent<TransformComponent>();

			// 0 means no repeat, so it is triggered by an event.
			if (projectileEmitter.repeatFrequency == 0) {
				continue;
			}

			if (SDL_GetTicks() - projectileEmitter.lastEmissionTime > projectileEmitter.repeatFrequency) {
				glm::vec2 projectilePosition = transform.position;
				if (entity.HasComponent<SpriteComponent>()) {
					auto sprite = entity.GetComponent<SpriteComponent>();
					projectilePosition.x += (transform.scale.x * sprite.width / 2);
					projectilePosition.y += (transform.scale.y * sprite.height / 2);
				}

				Entity projectile = registry->CreateEntity();
				projectile.Group("projectiles");
				projectile.AddComponent<TransformComponent>(projectilePosition, glm::vec2(1.0, 1.0), 0.0);
				projectile.AddComponent<RigidBodyComponent>(projectileEmitter.projectileVelocity);
				projectile.AddComponent<SpriteComponent>("bullet-image", 4, 4, 4);
				projectile.AddComponent<BoxColliderComponent>(4, 4);
				projectile.AddComponent<ProjectileComponent>(projectileEmitter.isFriendly, projectileEmitter.hitDmg, projectileEmitter.projectileDuration);

				projectileEmitter.lastEmissionTime = SDL_GetTicks();
				
			}
		}
	}
private:

};