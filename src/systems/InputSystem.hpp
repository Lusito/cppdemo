#pragma once
#include <ecstasy/systems/IteratingSystem.hpp>

class InputSystem : public IteratingSystem<InputSystem> {
private:
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;

public:
	InputSystem();

	void processEntity(Entity *entity, float deltaTime) override;

	bool handleKey(int key, int scancode, int action, int mods);
};
