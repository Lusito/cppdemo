#include <memory>

#include "MenuPageMain.hpp"
#include "MenuPageCreateServer.hpp"
#include "MenuPageFindServers.hpp"
#include "MenuPageJoinServer.hpp"
#include "MenuPageError.hpp"
#include "../../state/StateManager.hpp"
#include "../PlayState.hpp"
#include "../../Signals.hpp"

MenuPageMain::MenuPageMain(StateManager& manager, nk_context* nk)
	: MenuPage(manager, nk, "mainmenu") {
	createServerMenu = std::make_shared<MenuPageCreateServer>(manager, nk);
	findServersMenu = std::make_shared<MenuPageFindServers>(manager, nk);
	joinServerMenu = std::make_shared<MenuPageJoinServer>(manager, nk);
	errorMenu = std::make_shared<MenuPageError>(manager, nk);
	
	connectionScope += Signals::getInstance()->error.connect(this, &MenuPageMain::onError);
	connectionScope += Signals::getInstance()->serverDisconnected.connect(this, &MenuPageMain::onServerDisconnected);
}

MenuPageMain::~MenuPageMain() { }

void MenuPageMain::updateContent() {
	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Create Server")) {
		manager.push(createServerMenu);
		return;
	}
	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Find Servers in LAN")) {
		manager.push(findServersMenu);
		return;
	}
	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Join Server")) {
		manager.push(joinServerMenu);
		return;
	}
	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Exit")) {
		exit(EXIT_SUCCESS);
//		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void MenuPageMain::onError(const std::string &message) {
	errorMenu->setMessage(message);
	while(manager.size() > 1)
		manager.pop();
	manager.push(errorMenu);
}

void MenuPageMain::onServerDisconnected(DisconnectReason reason) {
	if(reason == DisconnectReason::CONNECT_FAILED)
		onError("Could not connect to server");
	else
		onError("The server disconnected");
}
