#pragma once

#include "../AssetStore/AssetStore.h"
#include "../ECS/ECS.h"
#include "../Components/TextLabelComponent.h"
#include <SDL.h>

class RenderTextSystem : public System {
public:
	RenderTextSystem() {
		RequireComponent<TextLabelComponent>();
	}

	void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore, const SDL_Rect& camera) {
		for (auto entity : GetSystemEntities()) {
			const auto textLabel = entity.GetComponent<TextLabelComponent>();
			
			SDL_Surface* surface = TTF_RenderText_Blended(
				assetStore->GetFont(textLabel.assetId),
				textLabel.text.c_str(),
				textLabel.color
			);

			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);

			int labelWidth = 0;
			int labelHeight = 0;
			int x = textLabel.position.x - (textLabel.isFixed ? 0 : camera.x);
			int y = textLabel.position.y - (textLabel.isFixed ? 0 : camera.y);

			SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);
			SDL_Rect dstRect = {
				x,
				y,
				labelWidth,
				labelHeight,
			};
			Logger::Log(std::to_string(x) + std::to_string(y));
			SDL_RenderCopy(renderer, texture, NULL, &dstRect);
			SDL_DestroyTexture(texture);
		}
	}
};
