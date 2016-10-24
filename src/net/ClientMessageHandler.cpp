#include "ClientMessageHandler.hpp"
#include "../../generated/MessageAdapters.hpp"
#include "../Signals.hpp"
#include "../Constants.hpp"
#include "../components/LocalPlayerComponent.hpp"
#include "../components/InputComponent.hpp"
#include "../components/PlayerComponent.hpp"
#include "../components/VelocityComponent.hpp"
#include "../components/PositionComponent.hpp"
#include "../components/RenderComponent.hpp"
#include <ecstasy/core/Engine.hpp>
#include <ecstasy/core/Entity.hpp>
#include <enet/enet.h>
#include <iostream>
#include <math.h>

ClientMessageHandler::ClientMessageHandler(const std::string &username, ENetPeer* peer, Engine &engine)
	: username(username), messageWriter(Constants::MAX_MESSAGE_SIZE), peer(peer), engine(engine) {	
	localPlayers = engine.getEntitiesFor(Family::all<LocalPlayerComponent, InputComponent>().get());

	connectionScope += Signals::getInstance()->serverConnected.connect(this, &ClientMessageHandler::onServerConnected);
	connectionScope += Signals::getInstance()->submitChat.connect(this, &ClientMessageHandler::onSubmitChat);
	
	putCallback(this, &ClientMessageHandler::handleHandshakeServerMessage);
	putCallback(this, &ClientMessageHandler::handleCreatePlayersMessage);
	putCallback(this, &ClientMessageHandler::handleDestroyPlayerMessage);
	putCallback(this, &ClientMessageHandler::handleUpdatePlayersMessage);
	putCallback(this, &ClientMessageHandler::handleChatMessage);
}

ClientMessageHandler::~ClientMessageHandler() { }

void ClientMessageHandler::update(float deltaTime) {
	nextBroadcast -= deltaTime;
	if(nextBroadcast <= 0) {
		nextBroadcast = 0.016f;
		sendInputUpdate();
	}
}

void ClientMessageHandler::onServerConnected() {
	eznet::HandshakeClientMessage message;
	message.name = username;
	send(NetChannel::WORLD_RELIABLE, eznet::createPacket(messageWriter, message));
}

void ClientMessageHandler::onSubmitChat(const std::string &text) {
	eznet::ChatMessage message;
	message.message = text;
	send(NetChannel::CHAT, eznet::createPacket(messageWriter, message));
}

void ClientMessageHandler::handleHandshakeServerMessage(eznet::HandshakeServerMessage& message, ENetEvent& event) {
	std::cout << static_cast<int>(message.playerIndex) << std::endl;
	for (auto& player : message.playerList) {
		std::cout << player.name << std::endl;
	}
	auto ent = getEntity(message.entityId);
	if(ent)
		ent->add<LocalPlayerComponent>();
}
void ClientMessageHandler::handleCreatePlayersMessage(eznet::CreatePlayersMessage& message, ENetEvent& event) {
	for (auto& entry : message.entities) {
		std::cout << "entity " << std::to_string(entry.entityId) << " created" << std::endl;
		auto entity = engine.assembleEntity("player");
		auto pos = entity->get<PositionComponent>();
		pos->x = entry.x;
		pos->y = entry.y;
		auto render = entity->get<RenderComponent>();
		render->color = entry.color;
		render->size = entry.size;
		auto vel = entity->get<VelocityComponent>();
		if(vel) {
			vel->x = entry.velX;
			vel->y = entry.velY;
		}
		engine.addEntity(entity);
		mapEntity(entry.entityId, entity);
	}
}

void ClientMessageHandler::handleDestroyPlayerMessage(eznet::DestroyPlayerMessage& message, ENetEvent& event) {
	auto entity = getEntity(message.entityId);
	if(entity) {
		engine.removeEntity(entity);
	}
}

void ClientMessageHandler::handleUpdatePlayersMessage(eznet::UpdatePlayersMessage& message, ENetEvent& event) {
	for (auto& entry : message.updates) {
		auto entity = getEntity(entry.entityId);
		if(entity) {
			auto player = entity->get<PlayerComponent>();
			if(player && player->packetNumber < entry.packetNumber) {
				player->packetNumber = entry.packetNumber;
				auto pos = entity->get<PositionComponent>();
				if(pos) {
					if(fabs(pos->x - entry.x) > 5.0f)
						pos->x = entry.x;
					if(fabs(pos->y - entry.y) > 5.0f)
						pos->y = entry.y;
				}
				auto vel = entity->get<VelocityComponent>();
				if(vel) {
					vel->x = entry.velX;
					vel->y = entry.velY;
				}
			}
		}
	}
}

void ClientMessageHandler::handleChatMessage(eznet::ChatMessage& message, ENetEvent& event) {
	Signals::getInstance()->chat.emit(message.message, message.username);
}

void ClientMessageHandler::sendInputUpdate() {
	for(auto entity : *localPlayers) {
		auto input = entity->get<InputComponent>();
		eznet::InputUpdateMessage message;
		message.moveX = input->x;
		message.moveY = input->y;
		send(NetChannel::INPUT_UNRELIABLE, createPacket(messageWriter, message));
		break;
	}
}

void ClientMessageHandler::send(NetChannel channel, ENetPacket* packet) {
	enet_peer_send(peer, (enet_uint8)channel, packet);
}

Entity* ClientMessageHandler::getEntity(uint64_t id) {
	auto it = entityMap.find(id);
	if(it == entityMap.end()) {
		// Fixme: Id does not exist, show error, disconnect
		std::cerr << "Error: Id " << std::to_string(id) << " does not exist" << std::endl;
		//		exit(EXIT_FAILURE);
		return nullptr;
	}
	return engine.getEntity(it->second);
}

void ClientMessageHandler::mapEntity(uint64_t id, Entity* entity) {
	if(entityMap.count(id) != 0) {
		// Fixme: Id already exists, show error, disconnect
		std::cerr << "Error: Id already exists" << std::endl;
		//Fixme: exit
		return;
	}
	entityMap[id] = entity->getId();
}
