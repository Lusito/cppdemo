#pragma once
#include <ecstasy/systems/IteratingSystem.hpp>

class MovementSystem : public IteratingSystem<MovementSystem> {
public:
	MovementSystem();
	
	void processEntity(Entity *entity, float deltaTime) override;
};
