#include <memory>

#include "MenuPageMain.hpp"
#include "MenuPageCreateServer.hpp"
#include "MenuPageFindServers.hpp"
#include "MenuPageJoinServer.hpp"
#include "../../state/StateManager.hpp"
#include "../PlayState.hpp"

MenuPageMain::MenuPageMain(StateManager& manager, nk_context* nk)
	: MenuPage(manager, nk, "mainmenu") {
	createServerMenu = std::make_shared<MenuPageCreateServer>(manager, nk);
	findServersMenu = std::make_shared<MenuPageFindServers>(manager, nk);
	joinServerMenu = std::make_shared<MenuPageJoinServer>(manager, nk);
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