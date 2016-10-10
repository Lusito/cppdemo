#include "PlayState.hpp"
#include "menupages/MenuPageIngame.hpp"
#include "GLFW/glfw3.h"

PlayState::PlayState(StateManager& manager, nk_context* nk)
	: manager(manager), canvas(nk), ingameMenu(std::make_shared<MenuPageIngame>(menuStateManager, nk)) { }

PlayState::~PlayState() { }

void PlayState::entered() {
	while(menuStateManager.pop())
		continue;
}

void PlayState::leaving() {
	
}

void PlayState::update(float deltaTime) {
	struct nk_color red{255,0,0,255};
	canvas.begin();
	canvas.drawCircle(150, 250, 25, red);
	canvas.end();
	
	menuStateManager.update(deltaTime);
}

void PlayState::handleKey(int key, int scancode, int action, int mods) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
		if(menuStateManager.empty())
			menuStateManager.push(ingameMenu);
		else
			menuStateManager.pop();
	}
	menuStateManager.handleKey(key, scancode, action, mods);
}

void PlayState::resize(int width, int height) {
	canvas.setSize(width, height);
	menuStateManager.resize(width, height);
}
