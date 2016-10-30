#pragma once
#include <memory>
#include <vector>
class AbstractState;

namespace ecstasy {
	class EntityFactory;
}
using ecstasy::EntityFactory;
class StateManager {
private:
	std::shared_ptr<EntityFactory> entityFactory;
	std::vector<std::shared_ptr<AbstractState>> states;
	int width = 0;
	int height = 0;

public:
	StateManager();
	StateManager(const StateManager& orig) = delete;
	~StateManager();

	void push(std::shared_ptr<AbstractState> state);
	bool pop();
	bool empty() const { return states.empty(); }
	auto size() const { return states.size(); }

	void update(float deltaTime);
	bool handleKey(int key, int scancode, int action, int mods);
	void resize(int width, int height);

	void setEntityFactory(std::shared_ptr<EntityFactory> entityFactory) {
		this->entityFactory = entityFactory;
	}

	std::shared_ptr<EntityFactory> getEntityFactory() {
		return entityFactory;
	}
};
