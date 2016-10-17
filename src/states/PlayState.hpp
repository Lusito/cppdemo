#pragma once
#include "../state/StateManager.hpp"
#include "../state/AbstractState.hpp"
#include "../ui/Canvas.hpp"
#include "../net/NetPlayerInfo.hpp"
#include <ecstasy/core/Engine.hpp>
#include <eznet/Connection.hpp>
#include <eznet/DiscoveryServer.hpp>

class MenuPageIngame;
class ServerConnectHandler;
class ServerMessageHandler;
class ClientConnectHandler;
class ClientMessageHandler;
class MenuPageConnecting;
class PlayState : public AbstractState {
protected:
	StateManager& manager;
	StateManager menuStateManager;
	Canvas canvas;
	std::shared_ptr<MenuPageIngame> ingameMenu;
	std::shared_ptr<MenuPageConnecting> connectingMenu;
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
};

class ServerPlayState : public PlayState {
private:
	eznet::DiscoveryServer discoveryServer;
	eznet::ServerConnection connection;
	std::shared_ptr<ServerConnectHandler> connectHandler;
	std::shared_ptr<ServerMessageHandler> messageHandler;
	uint16_t port;
	std::string servername;
	NetPlayerInfos playerInfos;
	ConnectionScope connectionScope;

public:
	ServerPlayState(StateManager& manager, nk_context* nk,
				 uint16_t port, const std::string username, const std::string servername);
	ServerPlayState(const PlayState& orig) = delete;
	virtual ~ServerPlayState();

	void entered() override;
	void leaving() override;
	void update(float deltaTime) override;

private:
	void onClientConnected(NetPlayerInfo *info);
	void onClientDisconnected(NetPlayerInfo *info);
};

class ClientPlayState : public PlayState {
private:
	std::string hostname;
	uint16_t port;
	std::string username;
	eznet::ClientConnection connection;
	std::shared_ptr<ClientConnectHandler> connectHandler;
	std::shared_ptr<ClientMessageHandler> messageHandler;

public:
	ClientPlayState(StateManager& manager, nk_context* nk,
				 const std::string hostname, uint16_t port, const std::string username);
	ClientPlayState(const PlayState& orig) = delete;
	virtual ~ClientPlayState();

	void entered() override;
	void leaving() override;
	void update(float deltaTime) override;
	void handleKey(int key, int scancode, int action, int mods) override;
};
