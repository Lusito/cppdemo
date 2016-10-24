#pragma once
#include <ecstasy/core/Component.hpp>

struct VelocityComponent: public Component<VelocityComponent> {
	float x = 0;
	float y = 0;
};
