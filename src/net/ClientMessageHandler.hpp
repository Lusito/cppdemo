#pragma once
#include "../../generated/Messages.hpp"
#include <eznet/MessageHandler.hpp>
#include <signal11/Signal.hpp>
#include <memory>
#include <unordered_map>

struct Signals;
struct _ENetPeer;
typedef _ENetPeer ENetPeer;
struct _ENetPacket;
typedef _ENetPacket ENetPacket;
struct _ENetHost;
typedef _ENetHost ENetHost;

namespace ecstasy {
	class Engine;
	class Entity;
}

class ClientMessageHandler : public eznet::MessageHandler {
private:
	std::string username;
	ConnectionScope connectionScope;
	eznet::BufferWriter messageWriter;
	ENetPeer* peer;
	ecstasy::Engine &engine;
	std::unordered_map<uint64_t, uint64_t> entityMap;
	const std::vector<ecstasy::Entity *> *localPlayers;
	float nextBroadcast = 0;

public:
	ClientMessageHandler(const std::string &username, ENetPeer* peer, ecstasy::Engine &engine);
	ClientMessageHandler(const ClientMessageHandler& orig) = delete;
	~ClientMessageHandler();
	
	void update(float deltaTime);

private:
	// Signal callbacks
	void onServerConnected();
	void onSubmitChat(const std::string &message);
	
	// Message handlers
	void handleHandshakeServerMessage(eznet::HandshakeServerMessage& message, ENetEvent& event);
	void handleCreatePlayersMessage(eznet::CreatePlayersMessage& message, ENetEvent& event);
	void handleDestroyPlayerMessage(eznet::DestroyPlayerMessage& message, ENetEvent& event);
	void handleUpdatePlayersMessage(eznet::UpdatePlayersMessage& message, ENetEvent& event);
	void handleChatMessage(eznet::ChatMessage& message, ENetEvent& event);
	
	// Utility
	void sendInputUpdate();
	void send(NetChannel channel, ENetPacket* packet);
	
	ecstasy::Entity* getEntity(uint64_t id);
	void mapEntity(uint64_t id, ecstasy::Entity* entity);
};
