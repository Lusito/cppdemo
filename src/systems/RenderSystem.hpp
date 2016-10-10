#pragma once
#include <ecstasy/systems/IteratingSystem.hpp>

class Canvas;
class RenderSystem : public IteratingSystem<RenderSystem> {
private:
	Canvas *canvas;

public:
	RenderSystem(Canvas *canvas);
	
	void update(float deltaTime) override;
	void processEntity(Entity *entity, float deltaTime) override;
};
