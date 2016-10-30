#pragma once
#include "../ui/nuklear_setup.h"
#include <ecstasy/core/Component.hpp>

struct RenderComponent: public Component<RenderComponent> {
	RenderComponent() : color{1,1,1,1} {}

	float size = 1;
	nk_color color;
};
