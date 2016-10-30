#include "InputSystem.hpp"
#include "../components/InputComponent.hpp"
#include "../components/LocalPlayerComponent.hpp"
#include <ecstasy/core/Family.hpp>
#include <GLFW/glfw3.h>
#include <math.h>

InputSystem::InputSystem() : IteratingSystem(Family::all<InputComponent, LocalPlayerComponent>().get()) {
}

void InputSystem::processEntity(Entity *entity, float deltaTime) {
	auto input = entity->get<InputComponent>();

	float x = 0, y = 0;
	if(moveUp)
		y -= 1;
	if(moveDown)
		y += 1;
	if(moveLeft)
		x -= 1;
	if(moveRight)
		x += 1;

	// normalize
	if(x || y) {
		float len = sqrtf(x*x + y*y);
		x /= len;
		y /= len;
	}
	input->x = x;
	input->y = y;
}

bool InputSystem::handleKey(int key, int scancode, int action, int mods) {
	bool down = action != GLFW_RELEASE;
	switch(key) {
	case GLFW_KEY_UP:
		moveUp = down;
		return true;
	case GLFW_KEY_DOWN:
		moveDown = down;
		return true;
	case GLFW_KEY_LEFT:
		moveLeft = down;
		return true;
	case GLFW_KEY_RIGHT:
		moveRight = down;
		return true;
	}
	return false;
}
