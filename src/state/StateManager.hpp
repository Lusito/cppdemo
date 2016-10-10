#pragma once
#include <memory>
#include <vector>
class AbstractState;

class StateManager {
private:
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

	void update(float deltaTime);
	void handleKey(int key, int scancode, int action, int mods);
	void resize(int width, int height);
};
