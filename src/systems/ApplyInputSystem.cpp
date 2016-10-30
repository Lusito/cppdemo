#include "ApplyInputSystem.hpp"
#include "../components/InputComponent.hpp"
#include "../components/VelocityComponent.hpp"
#include <ecstasy/core/Family.hpp>

const float PLAYER_SPEED = 200;

ApplyInputSystem::ApplyInputSystem() : IteratingSystem(Family::all<InputComponent, VelocityComponent>().get()) {

}

void ApplyInputSystem::processEntity(Entity *entity, float deltaTime) {
	auto input = entity->get<InputComponent>();
	auto velocity = entity->get<VelocityComponent>();
	velocity->x = input->x * PLAYER_SPEED;
	velocity->y = input->y * PLAYER_SPEED;
}
