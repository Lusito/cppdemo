#pragma once
#include <ecstasy/core/Component.hpp>

struct LocalPlayerComponent: public Component<LocalPlayerComponent> {
	LocalPlayerComponent() {}
	~LocalPlayerComponent() {}
};
