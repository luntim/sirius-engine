#pragma once

#include "../ECS/ECS.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../Components/SpriteComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Events/PrimaryFireEvent.h"

class KeyboardControlSystem : public System {
public:
	KeyboardControlSystem() {
		RequireComponent<RigidBodyComponent>();
		RequireComponent<SpriteComponent>();
		RequireComponent<KeyboardControlledComponent>();
	}

	void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
		eventBus->SubscribeToEvent<KeyPressedEvent>(this, &KeyboardControlSystem::OnKeyPressed);
	}

	void OnKeyPressed(KeyPressedEvent& event) {
		for (auto entity : GetSystemEntities()) {
			const auto& keyboardcontrol = entity.GetComponent<KeyboardControlledComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();
			auto& rigidbody = entity.GetComponent<RigidBodyComponent>();

			switch (event.keycode) {
			case SDLK_UP:
				rigidbody.velocity = keyboardcontrol.upVelocity;
				sprite.srcRect.y = sprite.height * 0;
				break;
			case SDLK_RIGHT:
				rigidbody.velocity = keyboardcontrol.rightVelocity;
				sprite.srcRect.y = sprite.height * 1;
				break;
			case SDLK_DOWN:
				rigidbody.velocity = keyboardcontrol.downVelocity;
				sprite.srcRect.y = sprite.height * 2;
				break;
			case SDLK_LEFT:
				rigidbody.velocity = keyboardcontrol.leftVelocity;
				sprite.srcRect.y = sprite.height * 3;
				break;
			case SDLK_SPACE:
				event.eventBus->EmitEvent<PrimaryFireEvent>(entity, event.eventBus);

			}
		}
	}
};