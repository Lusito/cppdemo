#include "PlayState.hpp"
#include "menupages/MenuPageIngame.hpp"
#include "GLFW/glfw3.h"
#include "../systems/ApplyInputSystem.hpp"
#include "../systems/InputSystem.hpp"
#include "../systems/MovementSystem.hpp"
#include "../systems/RenderSystem.hpp"
#include "../components/PlayerComponent.hpp"
#include "../components/LocalPlayerComponent.hpp"
#include "../components/InputComponent.hpp"
#include "../components/PositionComponent.hpp"
#include "../components/VelocityComponent.hpp"
#include "../components/RenderComponent.hpp"

PlayState::PlayState(StateManager& manager, nk_context* nk, bool isServer)
	: manager(manager), canvas(nk), ingameMenu(std::make_shared<MenuPageIngame>(menuStateManager, nk)),
	isServer(isServer) {
	
	engine.addSystem<InputSystem>();
	engine.addSystem<ApplyInputSystem>();
	engine.addSystem<MovementSystem>();
	engine.addSystem<RenderSystem>(&canvas);
}

PlayState::~PlayState() { }

void PlayState::entered() {
	while(menuStateManager.pop())
		continue;
	
	auto e = engine.createEntity();
	e->assign<PlayerComponent>();
	e->assign<LocalPlayerComponent>();
	e->assign<InputComponent>();
	e->assign<PositionComponent>();
	e->assign<VelocityComponent>();
	e->assign<RenderComponent>();
	auto pos = e->get<PositionComponent>();
	pos->x = 150;
	pos->y = 250;
	auto render = e->get<RenderComponent>();
	render->size = 25;
	render->color = nk_rgba(255,0,0,255);
	engine.addEntity(e);
}

void PlayState::leaving() {
	
}

void PlayState::update(float deltaTime) {
	engine.update(deltaTime);
	
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
	engine.getSystem<InputSystem>()->handleKey(key, scancode, action, mods);
}

void PlayState::resize(int width, int height) {
	canvas.setSize(width, height);
	menuStateManager.resize(width, height);
}

ServerPlayState::ServerPlayState(StateManager& manager, nk_context* nk,
								 int port, const std::string userName, const std::string serverName)
	: PlayState(manager, nk, true) {
}

ServerPlayState::~ServerPlayState() { }

ClientPlayState::ClientPlayState(StateManager& manager, nk_context* nk,
								 const std::string hostName, int port, const std::string userName)
	: PlayState(manager, nk, false) {
}

ClientPlayState::~ClientPlayState() { }
