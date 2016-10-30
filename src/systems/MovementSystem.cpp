#include "MovementSystem.hpp"
#include "../components/VelocityComponent.hpp"
#include "../components/PositionComponent.hpp"
#include <ecstasy/core/Family.hpp>

MovementSystem::MovementSystem() : IteratingSystem(Family::all<VelocityComponent, PositionComponent>().get()) {
}

void MovementSystem::processEntity(Entity *entity, float deltaTime) {
	auto velocity = entity->get<VelocityComponent>();
	auto position = entity->get<PositionComponent>();
	position->x += velocity->x * deltaTime;
	position->y += velocity->y * deltaTime;
}
