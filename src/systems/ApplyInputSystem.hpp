#pragma once
#include <ecstasy/systems/IteratingSystem.hpp>

class ApplyInputSystem : public IteratingSystem<ApplyInputSystem> {
public:
	ApplyInputSystem();

	void processEntity(Entity *entity, float deltaTime) override;
};
