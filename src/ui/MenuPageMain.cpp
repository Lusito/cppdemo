#include "MenuPageMain.hpp"

MenuPageMain::MenuPageMain(nk_context* nk) : MenuPage(nk, "mainmenu") {
	hostname[0] = '\0';
}

MenuPageMain::~MenuPageMain() { }

void MenuPageMain::updateContent(struct nk_rect &area) {
	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Create Server")) {
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