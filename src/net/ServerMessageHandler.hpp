#pragma once
#include "../../generated/Messages.hpp"
#include "NetPlayerInfo.hpp"
#include <eznet/Buffer.hpp>
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
namespace ECS {
	class Engine;
}
class ServerMessageHandler : public eznet::MessageHandler {
private:
	ServerStatus status = ServerStatus::INIT;
	eznet::BufferWriter messageWriter;
	ENetHost* host;
	NetPlayerInfos &playerInfos;
	ConnectionScope connectionScope;
	const std::vector<Entity *> *players;
	float nextBroadcast = 0;

public:
	ServerMessageHandler(ENetHost* host, NetPlayerInfos &playerInfos, ECS::Engine &engine);
	ServerMessageHandler(const ServerMessageHandler& orig) = delete;
	~ServerMessageHandler();
	
	void update(float deltaTime);
	
private:
	// Signal callbacks
	void onEntityAdded(Entity *entity);
	void onEntityRemoved(Entity *entity);
	void onSubmitChat(const std::string &message);
	
	// Message handlers
	void handleHandshakeClientMessage(eznet::HandshakeClientMessage& message, ENetEvent& event);
	void handleChatMessage(eznet::ChatMessage& message, ENetEvent& event);
	
	// Utility
	void broadcastPlayerUpdates();
	void send(ENetPeer* peer, NetChannel channel, ENetPacket* packet);
	void broadcast(NetChannel channel, ENetPacket* packet);

	void sendCreatePlayers(ENetPeer* peer);
};
