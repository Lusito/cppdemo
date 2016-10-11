#pragma once

#include "state/StateManager.hpp"

class Game {
private:
	StateManager stateManager;

public:
	Game();
	Game(const Game& orig) = delete;
	~Game() = default;
	
	void run();

	StateManager& getStateManager() {
		return stateManager;
	}
};
