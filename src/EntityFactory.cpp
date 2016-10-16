#include "EntityFactory.hpp"
#include <ecstasy/core/Engine.hpp>
#include "components/PlayerComponent.hpp"
#include "components/InputComponent.hpp"
#include "components/PositionComponent.hpp"
#include "components/VelocityComponent.hpp"
#include "components/RenderComponent.hpp"

namespace EntityFactory {
	Entity* createPlayer(Engine &engine, float x, float y, const nk_color &color) {
		auto e = engine.createEntity();
		e->assign<PlayerComponent>();
		e->assign<InputComponent>();
		auto pos = e->assign<PositionComponent>();
		e->assign<VelocityComponent>();
		auto render = e->assign<RenderComponent>();
		pos->x = x;
		pos->y = y;
		render->size = 25;
		render->color = color;
		engine.addEntity(e);
		return e;
	}
}
