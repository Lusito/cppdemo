#include "ServerMessageHandler.hpp"
#include "../../generated/MessageAdapters.hpp"
#include "../Signals.hpp"
#include "../Constants.hpp"
#include "NetPlayerInfo.hpp"
#include <enet/enet.h>

ServerMessageHandler::ServerMessageHandler(ENetHost* host, NetPlayerInfos &playerInfos)
	: messageWriter(Constants::MAX_MESSAGE_SIZE), host(host), playerInfos(playerInfos) {
	putCallback(this, &ServerMessageHandler::handleHandshakeClientMessage);
}

ServerMessageHandler::~ServerMessageHandler() { }

void ServerMessageHandler::handleHandshakeClientMessage(eznet::HandshakeClientMessage& message, ENetEvent& event) {
	NetPlayerInfo* info = static_cast<NetPlayerInfo*>(event.peer->data);
	info->status = NetPlayerStatus::CONNECTED;
	info->name = message.name;
	auto signals = Signals::getInstance();
	playerInfos.makeUniqueName(info);
	signals->clientConnected.emit(info);

	// Send greeting back
	eznet::HandshakeServerMessage reply;
	reply.status = status;
	reply.playerIndex = info->playerIndex;
	for (int i=0; i<Constants::MAX_SLOTS; i++) {
		auto& info = playerInfos.slots[i];
		if(info.status == NetPlayerStatus::CONNECTED) {
			reply.playerList.emplace_back();
			auto& entry = reply.playerList.back();
			entry.name = info.name;
			entry.playerIndex = info.playerIndex;
		}
	}


	send(event.peer, NetChannel::WORLD_RELIABLE, createPacket(messageWriter, reply));
}

void ServerMessageHandler::send(ENetPeer* peer, NetChannel channel, ENetPacket* packet) {
	enet_peer_send(peer, static_cast<uint8_t>(channel), packet);
}

void ServerMessageHandler::broadcast(NetChannel channel, ENetPacket* packet) {
	enet_host_broadcast(host, static_cast<uint8_t>(channel), packet);
}
