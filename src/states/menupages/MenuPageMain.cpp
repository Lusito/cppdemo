#include <memory>

#include "MenuPageMain.hpp"
#include "MenuPageCreateServer.hpp"
#include "../../state/StateManager.hpp"
#include "../PlayState.hpp"

MenuPageMain::MenuPageMain(StateManager& manager, nk_context* nk)
	: MenuPage(manager, nk, "mainmenu") {
	createServerMenu = std::make_shared<MenuPageCreateServer>(manager, nk);
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
	}
	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Exit")) {
        exit(EXIT_SUCCESS);
//		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}