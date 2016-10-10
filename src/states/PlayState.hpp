#pragma once
#include "../state/StateManager.hpp"
#include "../state/AbstractState.hpp"
#include "../ui/Canvas.hpp"

class MenuPageIngame;
class PlayState : public AbstractState {
private:
	StateManager& manager;
	StateManager menuStateManager;
	Canvas canvas;
	std::shared_ptr<MenuPageIngame> ingameMenu;

public:
	PlayState(StateManager& manager, nk_context* nk);
	PlayState(const PlayState& orig) = delete;
	virtual ~PlayState();
	
	void entered() override;
	void leaving() override;
	void update(float deltaTime);
	void handleKey(int key, int scancode, int action, int mods) override;
	void resize(int width, int height) override;
};
