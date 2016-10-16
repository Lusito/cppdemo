#include "PlayState.hpp"
#include "menupages/MenuPageIngame.hpp"
#include "GLFW/glfw3.h"
#include "../systems/ApplyInputSystem.hpp"
#include "../systems/InputSystem.hpp"
#include "../systems/MovementSystem.hpp"
#include "../systems/RenderSystem.hpp"
#include "../components/PlayerComponent.hpp"
#include "../components/LocalPlayerComponent.hpp"
#include "../components/InputComponent.hpp"
#include "../components/PositionComponent.hpp"
#include "../components/VelocityComponent.hpp"
#include "../components/RenderComponent.hpp"
#include "../Constants.hpp"
#include "../net/ServerConnectHandler.hpp"
#include "../net/ServerMessageHandler.hpp"
#include "../net/ClientConnectHandler.hpp"
#include "../net/ClientMessageHandler.hpp"
#include "../Signals.hpp"
#include "../EntityFactory.hpp"

PlayState::PlayState(StateManager& manager, nk_context* nk, bool isServer)
	: manager(manager), canvas(nk), ingameMenu(std::make_shared<MenuPageIngame>(menuStateManager, nk)),
	isServer(isServer) {
	
	engine.addSystem<InputSystem>();
	if(isServer)
		engine.addSystem<ApplyInputSystem>();
	engine.addSystem<MovementSystem>();
	engine.addSystem<RenderSystem>(&canvas);
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

void PlayState::handleKey(int key, int scancode, int action, int mods) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
		if(menuStateManager.empty())
			menuStateManager.push(ingameMenu);
		else
			menuStateManager.pop();
	}
	menuStateManager.handleKey(key, scancode, action, mods);
	engine.getSystem<InputSystem>()->handleKey(key, scancode, action, mods);
}

void PlayState::resize(int width, int height) {
	canvas.setSize(width, height);
	menuStateManager.resize(width, height);
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
	
	auto localPlayer = EntityFactory::createPlayer(engine, 150, 250, nk_rgba(255,0,0,255));
	localPlayer->assign<LocalPlayerComponent>();
	EntityFactory::createPlayer(engine, 250, 250, nk_rgba(0,255,0,255));
	EntityFactory::createPlayer(engine, 200, 400, nk_rgba(0,0,255,255));
	
	//Fixme: handle false return values
	discoveryServer.start(Constants::DISCOVERY_PORT, servername,
						 port, Constants::MAX_SLOTS);
	discoveryServer.setAvailableSlots(discoveryServer.getAvailableSlots() - 1);
	connection.connect("", port, discoveryServer.getAvailableSlots(), static_cast<uint8_t>(NetChannel::COUNT));
	connectHandler = std::make_shared<ServerConnectHandler>(playerInfos);
	messageHandler = std::make_shared<ServerMessageHandler>(connection.getHost(), playerInfos, engine);
	connection.setConnectHandler(connectHandler);
	connection.setMessageHandler(messageHandler);
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
	//Fixme: handle false return value
	connection.connect(hostname, port, static_cast<uint8_t>(NetChannel::COUNT));
	connectHandler = std::make_shared<ClientConnectHandler>();
	messageHandler = std::make_shared<ClientMessageHandler>(username, connection.getPeer(), engine);
	connection.setConnectHandler(connectHandler);
	connection.setMessageHandler(messageHandler);
}

void ClientPlayState::leaving() {
	PlayState::leaving();
}

void ClientPlayState::update(float deltaTime) {
	PlayState::update(deltaTime);
	connection.update();
}
