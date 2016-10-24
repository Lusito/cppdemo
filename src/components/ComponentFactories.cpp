#include "ComponentFactories.hpp"
#include "../ui/nuklear_setup.h"
#include "RenderComponent.hpp"
#include <ecstasy/utils/Blueprint.hpp>

bool RenderComponentFactory::assemble(Entity *entity, ComponentBlueprint &blueprint) {
	auto comp = entity->add<RenderComponent>();
	comp->size = blueprint.getFloat("size", 1);
	comp->color = nk_rgb_hex(blueprint.getString("color", "FFFFFF").c_str());
	return true;
}
