#include <memory>

#include "MenuPageMain.hpp"
#include "../../state/StateManager.hpp"
#include "../PlayState.hpp"

MenuPageMain::MenuPageMain(StateManager& manager, nk_context* nk)
	: MenuPage(manager, nk, "mainmenu") {
	hostname[0] = '\0';
}

MenuPageMain::~MenuPageMain() { }

void MenuPageMain::updateContent() {
	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Create Server")) {
		while(manager.pop())
			continue;
		manager.push(std::make_shared<PlayState>(manager, nk));
	}
	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Find Servers in LAN")) {
	}
	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Exit")) {
        exit(EXIT_SUCCESS);
//		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	nk_layout_row_dynamic(nk, 30, 1);
	nk_edit_string(nk, NK_EDIT_SIMPLE, hostname, &hostnameLength, 256, nk_filter_default);
}