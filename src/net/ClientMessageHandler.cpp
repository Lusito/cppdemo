#include "ClientMessageHandler.hpp"
#include "../../generated/MessageAdapters.hpp"
#include "../Signals.hpp"
#include "../Constants.hpp"
#include <enet/enet.h>
#include <iostream>

ClientMessageHandler::ClientMessageHandler(const std::string &username, ENetPeer* peer)
	: username(username), messageWriter(Constants::MAX_MESSAGE_SIZE), peer(peer) {
	connectionScope += Signals::getInstance()->serverConnected.connect(this, &ClientMessageHandler::onServerConnected);
	putCallback(this, &ClientMessageHandler::handleHandshakeServerMessage);
}

ClientMessageHandler::~ClientMessageHandler() { }

void ClientMessageHandler::onServerConnected() {
	eznet::HandshakeClientMessage message;
	message.name = username;
	send(NetChannel::WORLD_RELIABLE, eznet::createPacket(messageWriter, message));
}

void ClientMessageHandler::handleHandshakeServerMessage(eznet::HandshakeServerMessage& message, ENetEvent& event) {
	std::cout << static_cast<int>(message.playerIndex) << std::endl;
	for (auto& player : message.playerList) {
		std::cout << player.name << std::endl;
	}
}

void ClientMessageHandler::send(NetChannel channel, ENetPacket* packet) {
	enet_peer_send(peer, (enet_uint8)channel, packet);
}
