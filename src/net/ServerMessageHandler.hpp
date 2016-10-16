#pragma once
#include "../../generated/Messages.hpp"
#include "NetPlayerInfo.hpp"
#include <eznet/Buffer.hpp>
#include <eznet/MessageHandler.hpp>
#include <memory>

struct Signals;
struct _ENetPeer;
typedef _ENetPeer ENetPeer;
struct _ENetPacket;
typedef _ENetPacket ENetPacket;
struct _ENetHost;
typedef _ENetHost ENetHost;

class ServerMessageHandler : public eznet::MessageHandler {
private:
	ServerStatus status = ServerStatus::INIT;
	eznet::BufferWriter messageWriter;
	ENetHost* host;
	NetPlayerInfos &playerInfos;

public:
	ServerMessageHandler(ENetHost* host, NetPlayerInfos &playerInfos);
	ServerMessageHandler(const ServerMessageHandler& orig) = delete;
	~ServerMessageHandler();
	
private:
	// Message handlers
	void handleHandshakeClientMessage(eznet::HandshakeClientMessage& message, ENetEvent& event);
	
	// Utility
	void send(ENetPeer* peer, NetChannel channel, ENetPacket* packet);
	void broadcast(NetChannel channel, ENetPacket* packet);
};
