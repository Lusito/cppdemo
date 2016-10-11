#include <memory>

#include "MenuPageIngame.hpp"
#include "../../state/StateManager.hpp"

MenuPageIngame::MenuPageIngame(StateManager& manager, nk_context* nk)
	: MenuPage(manager, nk, "ingame") {
}

MenuPageIngame::~MenuPageIngame() { }

void MenuPageIngame::updateContent() {
	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Continue")) {
		while(manager.pop())
			continue;
	}
	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Exit")) {
        exit(EXIT_SUCCESS);
//		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}