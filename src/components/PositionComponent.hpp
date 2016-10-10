#pragma once
#include <ecstasy/core/Component.hpp>

struct PositionComponent: public Component<PositionComponent> {
	PositionComponent() {}
	~PositionComponent() {}
	
	float x = 0;
	float y = 0;
};
