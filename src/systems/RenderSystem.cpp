#include "RenderSystem.hpp"
#include "../components/PositionComponent.hpp"
#include "../components/RenderComponent.hpp"
#include "../ui/Canvas.hpp"

RenderSystem::RenderSystem(Canvas *canvas) : IteratingSystem(Family::all<PositionComponent, RenderComponent>().get()), canvas(canvas) {
	
}

void RenderSystem::update(float deltaTime) {
	canvas->begin();
	IteratingSystem::update(deltaTime);
	canvas->end();
}

void RenderSystem::processEntity(Entity *entity, float deltaTime) {
	auto position = entity->get<PositionComponent>();
	auto render = entity->get<RenderComponent>();
	canvas->drawCircle(position->x, position->y, render->size, render->color);
}
