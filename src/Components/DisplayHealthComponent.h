#pragma once

#include <string>

struct DisplayHealthComponent {
	std::string assetId;

	DisplayHealthComponent(std::string assetId = "") {
		this->assetId = assetId;
	}
};
