#pragma once
#include "../state/StateManager.hpp"
#include "../state/AbstractState.hpp"
#include "../ui/Canvas.hpp"
#include <ecstasy/core/Engine.hpp>

class MenuPageIngame;
class PlayState : public AbstractState {
private:
	StateManager& manager;
	StateManager menuStateManager;
	Canvas canvas;
	std::shared_ptr<MenuPageIngame> ingameMenu;
	Engine engine;
	bool isServer;

protected:
	PlayState(StateManager& manager, nk_context* nk, bool isServer);

public:
	PlayState(const PlayState& orig) = delete;
	virtual ~PlayState();
	
	void entered() override;
	void leaving() override;
	void update(float deltaTime);
	void handleKey(int key, int scancode, int action, int mods) override;
	void resize(int width, int height) override;
	
private:
	Entity* createPlayer(float x, float y, const nk_color &color);
};

class ServerPlayState : public PlayState {
public:
	ServerPlayState(StateManager& manager, nk_context* nk,
				 int port, const std::string userName, const std::string serverName);
	ServerPlayState(const PlayState& orig) = delete;
	virtual ~ServerPlayState();
};

class ClientPlayState : public PlayState {
public:
	ClientPlayState(StateManager& manager, nk_context* nk,
				 const std::string hostName, int port, const std::string userName);
	ClientPlayState(const PlayState& orig) = delete;
	virtual ~ClientPlayState();
};
