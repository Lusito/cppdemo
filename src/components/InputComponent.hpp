#pragma once
#include <ecstasy/core/Component.hpp>

struct InputComponent: public Component<InputComponent> {
	InputComponent() {}
	~InputComponent() {}
	
	float x = 0;
	float y = 0;
};
