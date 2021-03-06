#include "ServerMessageHandler.hpp"
#include "../../generated/MessageAdapters.hpp"
#include "../Signals.hpp"
#include "../Constants.hpp"
#include "NetPlayerInfo.hpp"
#include "../components/PlayerComponent.hpp"
#include "../components/RenderComponent.hpp"
#include "../components/PositionComponent.hpp"
#include "../components/VelocityComponent.hpp"
#include "../components/InputComponent.hpp"
#include <enet/enet.h>
#include <ecstasy/core/Engine.hpp>
#include <ecstasy/core/Family.hpp>

const int max_size_per_packet = Constants::MAX_MESSAGE_SIZE - sizeof(eznet::MessageType::NUM_TYPES);

ServerMessageHandler::ServerMessageHandler(ENetHost* host, NetPlayerInfos &playerInfos, Engine &engine)
	: engine(engine), messageWriter(Constants::MAX_MESSAGE_SIZE), host(host), playerInfos(playerInfos) {

	players = engine.getEntitiesFor(Family::all<PlayerComponent, RenderComponent, PositionComponent, VelocityComponent>().get());

	connectionScope += engine.entityAdded.connect(this, &ServerMessageHandler::onEntityAdded);
	connectionScope += engine.entityAdded.connect(this, &ServerMessageHandler::onEntityRemoved);
	connectionScope += Signals::getInstance()->submitChat.connect(this, &ServerMessageHandler::onSubmitChat);

	putCallback(this, &ServerMessageHandler::handleHandshakeClientMessage);
	putCallback(this, &ServerMessageHandler::handleChatMessage);
	putCallback(this, &ServerMessageHandler::handleInputUpdateMessage);
}

ServerMessageHandler::~ServerMessageHandler() { }

void ServerMessageHandler::update(float deltaTime) {
	nextBroadcast -= deltaTime;
	if(nextBroadcast <= 0) {
		nextBroadcast = 0.016f;
		broadcastPlayerUpdates();
	}
}

void ServerMessageHandler::broadcastPlayerUpdates() {
	eznet::UpdatePlayersMessage message;
	for(auto entity : *players) {
		decltype(message.updates)::value_type entry;
		entry.entityId = entity->getId();
		entry.packetNumber = entity->get<PlayerComponent>()->packetNumber++;
		auto pos = entity->get<PositionComponent>();
		entry.x = pos->x;
		entry.y = pos->y;
		auto vel = entity->get<VelocityComponent>();
		entry.velX = vel->x;
		entry.velY = vel->y;

		if(getMessageSize(message) + getMessageSize(entry)>max_size_per_packet) {
			broadcast(NetChannel::WORLD_UNRELIABLE, createPacket(messageWriter, message));
			message.updates.clear();
		}
		message.updates.push_back(std::move(entry));
	}
	if(!message.updates.empty()) {
		broadcast(NetChannel::WORLD_UNRELIABLE, createPacket(messageWriter, message));
	}
}

void ServerMessageHandler::onEntityAdded(Entity *entity) {
}

void ServerMessageHandler::onEntityRemoved(Entity *entity) {
}

void ServerMessageHandler::onSubmitChat(const std::string &text) {
	eznet::ChatMessage message;
	message.message = text;
	message.username = playerInfos.slots[0].name;
	broadcast(NetChannel::CHAT, createPacket(messageWriter, message));
	Signals::getInstance()->chat.emit(message.message, message.username);
}

void ServerMessageHandler::sendCreatePlayers(ENetPeer* peer) {
	eznet::CreatePlayersMessage message;
	for(auto entity : *players) {
		decltype(message.entities)::value_type entry;
		entry.entityId = entity->getId();
		auto render = entity->get<RenderComponent>();
		entry.color = render->color;
		entry.size = render->size;
		auto pos = entity->get<PositionComponent>();
		entry.x = pos->x;
		entry.y = pos->y;
		auto vel = entity->get<VelocityComponent>();
		entry.velX = vel->x;
		entry.velY = vel->y;

		if(getMessageSize(message) + getMessageSize(entry)>max_size_per_packet) {
			send(peer, NetChannel::WORLD_RELIABLE, createPacket(messageWriter, message));
			message.entities.clear();
		}
		message.entities.push_back(std::move(entry));
	}
	if(!message.entities.empty()) {
		send(peer, NetChannel::WORLD_RELIABLE, createPacket(messageWriter, message));
	}
}

void ServerMessageHandler::handleHandshakeClientMessage(eznet::HandshakeClientMessage& message, ENetEvent& event) {
	NetPlayerInfo* info = static_cast<NetPlayerInfo*>(event.peer->data);
	info->status = NetPlayerStatus::CONNECTED;
	info->name = message.name;
	auto signals = Signals::getInstance();
	playerInfos.makeUniqueName(info);
	signals->clientConnected.emit(info);

	// Create player
	auto entity = engine.assembleEntity("player");
	auto pos = entity->get<PositionComponent>();
	//fixme: pos
	pos->x = 0;
	pos->y = 0;
	auto render = entity->get<RenderComponent>();
	render->color = nk_rgb(255,255,255);//fixme: color
//	250, 250, nk_rgba(0,255,0,255)
//	200, 400, nk_rgba(0,0,255,255)
	engine.addEntity(entity);

	info->entityId = entity->getId();

	// Send greeting back
	eznet::HandshakeServerMessage reply;
	reply.status = status;
	reply.entityId = entity->getId();
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

	sendCreatePlayers(event.peer);
	send(event.peer, NetChannel::WORLD_RELIABLE, createPacket(messageWriter, reply));
}

void ServerMessageHandler::handleChatMessage(eznet::ChatMessage& message, ENetEvent& event) {
	message.username = static_cast<NetPlayerInfo*>(event.peer->data)->name;
	broadcast(NetChannel::CHAT, createPacket(messageWriter, message));
	Signals::getInstance()->chat.emit(message.message, message.username);
}

void ServerMessageHandler::handleInputUpdateMessage(eznet::InputUpdateMessage& message, ENetEvent& event) {
	auto info = static_cast<NetPlayerInfo*>(event.peer->data);
	auto entity = engine.getEntity(info->entityId);
	if(entity) {
		auto input = entity->get<InputComponent>();
		if(input) {
			input->x = message.moveX;
			input->y = message.moveY;
		}
	}
}

void ServerMessageHandler::send(ENetPeer* peer, NetChannel channel, ENetPacket* packet) {
	enet_peer_send(peer, static_cast<uint8_t>(channel), packet);
}

void ServerMessageHandler::broadcast(NetChannel channel, ENetPacket* packet) {
	enet_host_broadcast(host, static_cast<uint8_t>(channel), packet);
}
