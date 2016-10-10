#pragma once
#include "../../state/AbstractState.hpp"
#include <string>
#include "../../ui/nuklear_setup.h"

struct nk_context;

class StateManager;
class MenuPage : public AbstractState {
protected:
	nk_context* nk;
	std::string name;
	nk_panel layout;
	struct nk_rect area;
	StateManager& manager;

public:
	MenuPage(StateManager& manager, nk_context* nk, const std::string &name);
	MenuPage(const MenuPage& orig) = delete;
	virtual ~MenuPage();
	
	void update(float deltaTime) override;
	virtual void show(bool visible);
	void entered() override { show(true); }
	void leaving() override { show(false); }
	void obscuring() override { show(false); }
	void reveiling() override { show(true); }

	
	virtual void resize(int width, int height) {
		area.w = width;
		area.h = height;
	}

protected:
	virtual void updateContent() = 0;

};
