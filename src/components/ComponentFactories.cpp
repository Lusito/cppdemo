#include "ComponentFactories.hpp"
#include "../ui/nuklear_setup.h"
#include "RenderComponent.hpp"

bool RenderComponentFactory::assemble(Entity *entity, ComponentBlueprint &blueprint) {
	auto comp = entity->assign<RenderComponent>();
	comp->size = blueprint.getFloat("size", 1);
	comp->color = nk_rgb_hex(blueprint.getString("color", "FFFFFF").c_str());
	return true;
}