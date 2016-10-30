#pragma once
#include <eznet/ConnectHandler.hpp>
#include "NetPlayerInfo.hpp"
#include "../Constants.hpp"
#include <memory>
#include <signal11/Signal.hpp>

struct Signals;

class ServerConnectHandler : public eznet::ConnectHandler {
private:
	ServerStatus status = ServerStatus::INIT;
	NetPlayerInfos &playerInfos;

public:
	ServerConnectHandler(NetPlayerInfos &playerInfos);
	ServerConnectHandler(const ServerConnectHandler& orig) = delete;
	~ServerConnectHandler();

	void onConnect(ENetEvent& event) override;
	void onDisconnect(ENetEvent& event) override;
};
