#pragma once

struct nk_color;

namespace ECS {
	class Engine;
	class Entity;
}

namespace EntityFactory {
	ECS::Entity* createPlayer(ECS::Engine &engine, float x, float y, const nk_color &color);
}
