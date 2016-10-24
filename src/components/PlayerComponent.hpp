#pragma once
#include <stdint.h>
#include <ecstasy/core/Component.hpp>

struct PlayerComponent: public Component<PlayerComponent> {
	float lookDirX = 0;
	float lookDirY = 0;
	uint64_t packetNumber = 0;
};
