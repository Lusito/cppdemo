#pragma once
#include "../../generated/Messages.hpp"
#include <eznet/MessageHandler.hpp>
#include <signal11/Signal.hpp>
#include <memory>

struct Signals;
struct _ENetPeer;
typedef _ENetPeer ENetPeer;
struct _ENetPacket;
typedef _ENetPacket ENetPacket;
struct _ENetHost;
typedef _ENetHost ENetHost;

class ClientMessageHandler : public eznet::MessageHandler {
private:
	std::string username;
	ConnectionScope connectionScope;
	eznet::BufferWriter messageWriter;
	ENetPeer* peer;

public:
	ClientMessageHandler(const std::string &username, ENetPeer* peer);
	ClientMessageHandler(const ClientMessageHandler& orig) = delete;
	~ClientMessageHandler();
	
private:
	// Signal callbacks
	void onServerConnected();
	
	// Message handlers
	void handleHandshakeServerMessage(eznet::HandshakeServerMessage& message, ENetEvent& event);
	
	// Utility
	void send(NetChannel channel, ENetPacket* packet);
};
