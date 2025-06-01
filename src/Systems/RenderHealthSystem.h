#pragma once

#include "../AssetStore/AssetStore.h"
#include "../ECS/ECS.h"
#include "../Components/HealthComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include <SDL.h>
#include <cmath>

class RenderHealthSystem : public System {
public:
	RenderHealthSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<HealthComponent>();
		RequireComponent<SpriteComponent>();
	}

	void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore, const SDL_Rect& camera) {
		for (auto entity : GetSystemEntities()) {
			// I want to take the current hp value and divide it by the starting hp value and display every 10% as individual blocks.
			// If they have 100% hp i display "100%" and 10 blocks. 100-70 green, 60-30 yellow, 20-10 red
			// THe position comes from transform component but offset the Y so it is always above the enemies.
			const auto health = entity.GetComponent<HealthComponent>(); 
			const auto transform = entity.GetComponent<TransformComponent>();
			const auto sprite = entity.GetComponent<SpriteComponent>();

			const float healthPercentageF = (static_cast<float>(health.health) / static_cast<float>(health.startingHealth) * 100);
			const int healthPercentage = std::round(healthPercentageF);
			SDL_Color color;
			if (healthPercentage <= 20) {
				// Green
				color = { 255, 0, 0 };
			}
			else if (healthPercentage < 70 && healthPercentage > 20) {
				// Yellow
				color = { 255, 255, 0 };
			}
			else if (healthPercentage >= 70) {
				// Red
				color = { 0, 255, 0 };
			}
			SDL_Surface* surface = TTF_RenderText_Blended(
				assetStore->GetFont("charriot-font-11"),
				std::to_string(health.health).c_str(), 
				color
			);
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);

			int labelWidth = 0;
			int labelHeight = 0;
			int x = transform.position.x - camera.x + (sprite.width * transform.scale.x);
			int y = transform.position.y - camera.y;
			int healthbarWidth = 15;
			int healthbarHeight = 5;
			SDL_Rect healthbarRect = {
				x,
				y,
				static_cast<int>(healthbarWidth * (healthPercentage / 100.0)),
				healthbarHeight
			};

			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
			SDL_RenderFillRect(renderer, &healthbarRect); 
			SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);
			SDL_Rect dstRect = {
				x,
				y + 7,
				labelWidth,
				labelHeight,
			};
			Logger::Log(std::to_string(x) + std::to_string(y));

			SDL_RenderCopy(renderer, texture, NULL, &dstRect);
			SDL_DestroyTexture(texture);
		}
	}
};