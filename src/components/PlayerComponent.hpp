#pragma once
#include <ecstasy/core/Component.hpp>

struct PlayerComponent: public Component<PlayerComponent> {
	PlayerComponent() {}
	~PlayerComponent() {}
	
	float lookDirX = 0;
	float lookDirY = 0;
};
