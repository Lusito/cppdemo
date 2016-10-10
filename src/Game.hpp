#pragma once

#include "state/StateManager.hpp"

struct vertex_data {
    float x, y;
    float r, g, b;
};

class Game {
private:
	StateManager stateManager;

public:
	Game();
	Game(const Game& orig) = delete;
	~Game() = default;
	
	void run();
	void update(float deltaTime);

	StateManager& getStateManager() {
		return stateManager;
	}
};
