#include <memory>

#include "MenuPageIngame.hpp"
#include "../../state/StateManager.hpp"
#include "../../Signals.hpp"

MenuPageIngame::MenuPageIngame(StateManager& manager, nk_context* nk)
	: MenuPage(manager, nk, "ingame") {
}

MenuPageIngame::~MenuPageIngame() { }

void MenuPageIngame::updateContent() {
	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Continue")) {
		manager.pop();
	}
	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Disconnect"))
		Signals::getInstance()->error.emit("User enforced a disconnect");
	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Exit")) {
        exit(EXIT_SUCCESS);
//		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}