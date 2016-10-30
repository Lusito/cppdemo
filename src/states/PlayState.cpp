#include "PlayState.hpp"
#include "menupages/MenuPageIngame.hpp"
#include "menupages/MenuPageConnecting.hpp"
#include "menupages/MenuPageChat.hpp"
#include "GLFW/glfw3.h"
#include "../systems/ChatRenderSystem.hpp"
#include "../systems/ApplyInputSystem.hpp"
#include "../systems/InputSystem.hpp"
#include "../systems/MovementSystem.hpp"
#include "../systems/RenderSystem.hpp"
#include "../components/LocalPlayerComponent.hpp"
#include "../components/PositionComponent.hpp"
#include "../components/RenderComponent.hpp"
#include "../Constants.hpp"
#include "../net/ServerConnectHandler.hpp"
#include "../net/ServerMessageHandler.hpp"
#include "../net/ClientConnectHandler.hpp"
#include "../net/ClientMessageHandler.hpp"
#include "../Signals.hpp"

PlayState::PlayState(StateManager& manager, nk_context* nk, bool isServer)
	: manager(manager), canvas(nk), ingameMenu(std::make_shared<MenuPageIngame>(menuStateManager, nk)),
	connectingMenu(std::make_shared<MenuPageConnecting>(menuStateManager, nk)),
	chatMenu(std::make_shared<MenuPageChat>(menuStateManager, nk)), isServer(isServer) {

	engine.setEntityFactory(manager.getEntityFactory());
	engine.emplaceSystem<InputSystem>();
	if(isServer)
		engine.emplaceSystem<ApplyInputSystem>();
	engine.emplaceSystem<MovementSystem>();
	engine.emplaceSystem<RenderSystem>(&canvas);
	engine.emplaceSystem<ChatRenderSystem>(nk);
}

PlayState::~PlayState() { }

void PlayState::entered() {
	while(menuStateManager.pop())
		continue;
}

void PlayState::leaving() {

}

void PlayState::update(float deltaTime) {
	engine.update(deltaTime);

	menuStateManager.update(deltaTime);
}

bool PlayState::handleKey(int key, int scancode, int action, int mods) {
	if(!menuStateManager.empty()) {
		if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
			menuStateManager.pop();
		menuStateManager.handleKey(key, scancode, action, mods);
		return true;
	} else {
		if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
			menuStateManager.push(ingameMenu);
			return true;
		}
		if(key == GLFW_KEY_ENTER && action == GLFW_RELEASE) {
			menuStateManager.push(chatMenu);
			return true;
		}
	}
	return engine.getSystem<InputSystem>()->handleKey(key, scancode, action, mods);
}

void PlayState::resize(int width, int height) {
	canvas.setSize(width, height);
	menuStateManager.resize(width, height);
	engine.getSystem<ChatRenderSystem>()->resize(width, height);
}

ServerPlayState::ServerPlayState(StateManager& manager, nk_context* nk,
								 uint16_t port, const std::string username, const std::string servername)
	: PlayState(manager, nk, true), discoveryServer(Constants::GAME_NAME),
		port(port), servername(servername), playerInfos(username) {
	connectionScope += Signals::getInstance()->clientConnected.connect(this, &ServerPlayState::onClientConnected);
	connectionScope += Signals::getInstance()->clientDisconnected.connect(this, &ServerPlayState::onClientDisconnected);
}

ServerPlayState::~ServerPlayState() { }

void ServerPlayState::onClientConnected(NetPlayerInfo *info) {
	discoveryServer.setAvailableSlots(discoveryServer.getAvailableSlots() - 1);
}

void ServerPlayState::onClientDisconnected(NetPlayerInfo *info) {
	discoveryServer.setAvailableSlots(discoveryServer.getAvailableSlots() + 1);
}

void ServerPlayState::entered() {
	PlayState::entered();

	auto localPlayer = engine.assembleEntity("player");
	auto pos = localPlayer->get<PositionComponent>();
	pos->x = 150;
	pos->y = 250;
	localPlayer->get<RenderComponent>()->color = nk_rgba(255,0,0,255);
	localPlayer->emplace<LocalPlayerComponent>();
	engine.addEntity(localPlayer);

	if(!discoveryServer.start(Constants::DISCOVERY_PORT, servername,
						 port, Constants::MAX_SLOTS))
		Signals::getInstance()->error.emit("Could not start discovery server");
	else {
		discoveryServer.setAvailableSlots(discoveryServer.getAvailableSlots() - 1);
		if(!connection.connect("", port, discoveryServer.getAvailableSlots(), static_cast<uint8_t>(NetChannel::COUNT)))
			Signals::getInstance()->error.emit("Could not start server");
		else {
			connectHandler = std::make_shared<ServerConnectHandler>(playerInfos);
			messageHandler = std::make_shared<ServerMessageHandler>(connection.getHost(), playerInfos, engine);
			connection.setConnectHandler(connectHandler);
			connection.setMessageHandler(messageHandler);
		}
	}
}

void ServerPlayState::leaving() {
	PlayState::leaving();
	discoveryServer.stop();
}

void ServerPlayState::update(float deltaTime) {
	PlayState::update(deltaTime);
	discoveryServer.update();
	messageHandler->update(deltaTime);
	connection.update();
}

ClientPlayState::ClientPlayState(StateManager& manager, nk_context* nk,
								 const std::string hostname, uint16_t port, const std::string username)
	: PlayState(manager, nk, false), hostname(hostname), port(port), username(username) {
}

ClientPlayState::~ClientPlayState() { }

void ClientPlayState::entered() {
	PlayState::entered();
	if(!connection.connect(hostname, port, static_cast<uint8_t>(NetChannel::COUNT)))
		Signals::getInstance()->error.emit("Could not start client");
	else {
		connectHandler = std::make_shared<ClientConnectHandler>();
		messageHandler = std::make_shared<ClientMessageHandler>(username, connection.getPeer(), engine);
		connection.setConnectHandler(connectHandler);
		connection.setMessageHandler(messageHandler);
		connectingMenu->setMessage("Host: " + hostname);
		menuStateManager.push(connectingMenu);
	}
}

void ClientPlayState::leaving() {
	PlayState::leaving();
}

void ClientPlayState::update(float deltaTime) {
	PlayState::update(deltaTime);
	connection.update();
	messageHandler->update(deltaTime);
}

bool ClientPlayState::handleKey(int key, int scancode, int action, int mods) {
	if(connection.isConnected())
		return PlayState::handleKey(key, scancode, action, mods);
	return false;
}
