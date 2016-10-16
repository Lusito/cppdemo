#pragma once
#include <eznet/ConnectHandler.hpp>
#include <memory>

struct Signals;

class ClientConnectHandler : public eznet::ConnectHandler {
public:
	ClientConnectHandler();
	ClientConnectHandler(const ClientConnectHandler& orig) = delete;
	~ClientConnectHandler();
	
	void onConnect(ENetEvent& event) override;
	void onDisconnect(ENetEvent& event) override;
};
