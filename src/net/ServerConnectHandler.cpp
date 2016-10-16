#include "ServerConnectHandler.hpp"
#include "../Signals.hpp"
#include <enet/enet.h>

ServerConnectHandler::ServerConnectHandler(NetPlayerInfos &playerInfos) : playerInfos(playerInfos) {
}

ServerConnectHandler::~ServerConnectHandler() { }

void ServerConnectHandler::onConnect(ENetEvent& event) {
	if (status != ServerStatus::SHUTDOWN) {
		for (int i = 0; i < Constants::MAX_SLOTS; i++) {
			auto& info = playerInfos.slots[i];
			if (info.status == NetPlayerStatus::DISCONNECTED) {
				event.peer->data = &info;
				info.init(event.peer);
				return;
			}
		}
	}
	enet_peer_disconnect(event.peer, 0);
}

void ServerConnectHandler::onDisconnect(ENetEvent& event) {
	if (event.peer->data) {
		NetPlayerInfo *info = static_cast<NetPlayerInfo *>(event.peer->data);
		Signals::getInstance()->clientDisconnected.emit(info);
		event.peer->data = nullptr;
		info->invalidate();
	}
}
