#pragma once
#include <ecstasy/core/Component.hpp>

struct PositionComponent: public Component<PositionComponent> {
	float x = 0;
	float y = 0;
};
