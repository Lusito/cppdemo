#pragma once
#include "../state/StateManager.hpp"
#include "../state/AbstractState.hpp"
#include "../ui/Canvas.hpp"
#include <ecstasy/core/Engine.hpp>
#include <eznet/DiscoveryServer.hpp>

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
	void update(float deltaTime) override;
	void handleKey(int key, int scancode, int action, int mods) override;
	void resize(int width, int height) override;
	
private:
	Entity* createPlayer(float x, float y, const nk_color &color);
};

class ServerPlayState : public PlayState {
private:
	eznet::DiscoveryServer discoveryServer;
	uint16_t port;
	std::string username;
	std::string servername;

public:
	ServerPlayState(StateManager& manager, nk_context* nk,
				 uint16_t port, const std::string username, const std::string servername);
	ServerPlayState(const PlayState& orig) = delete;
	virtual ~ServerPlayState();

	void entered() override;
	void leaving() override;
	void update(float deltaTime) override;
};

class ClientPlayState : public PlayState {
private:
	std::string hostname;
	uint16_t port;
	std::string username;

public:
	ClientPlayState(StateManager& manager, nk_context* nk,
				 const std::string hostname, uint16_t port, const std::string username);
	ClientPlayState(const PlayState& orig) = delete;
	virtual ~ClientPlayState();

	void entered() override;
	void leaving() override;
	void update(float deltaTime) override;
};
