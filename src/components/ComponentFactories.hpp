#pragma once 
#include <ecstasy/utils/ComponentFactory.hpp>

using ECS::ComponentBlueprint;

class RenderComponentFactory : public ComponentFactory {
public:
	RenderComponentFactory() {}
	RenderComponentFactory(const RenderComponentFactory& orig) = delete;
	~RenderComponentFactory() {}
	
	bool assemble(Entity *entity, ComponentBlueprint &blueprint) override;
};
