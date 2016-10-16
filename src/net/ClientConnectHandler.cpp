#include "ClientConnectHandler.hpp"
#include "../Signals.hpp"
#include "../Constants.hpp"
#include <enet/enet.h>

ClientConnectHandler::ClientConnectHandler() { }

ClientConnectHandler::~ClientConnectHandler() { }

void ClientConnectHandler::onConnect(ENetEvent& event) {
	Signals::getInstance()->serverConnected.emit();
}

void ClientConnectHandler::onDisconnect(ENetEvent& event) {
	Signals::getInstance()->serverDisconnected.emit(event.peer ? DisconnectReason::DISCONNECT : DisconnectReason::CONNECT_FAILED);
}
