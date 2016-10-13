#include <memory>

#include "MenuPageFindServers.hpp"
#include "../../state/StateManager.hpp"
#include <string.h>

MenuPageFindServers::MenuPageFindServers(StateManager& manager, nk_context* nk)
	: MenuPage(manager, nk, "find servers") {
}

MenuPageFindServers::~MenuPageFindServers() { }

void MenuPageFindServers::updateContent() {
	nk_layout_row_dynamic(nk, 30, 1);
	nk_label(nk, "Find Servers in LAN", NK_TEXT_ALIGN_CENTERED|NK_TEXT_ALIGN_BOTTOM);
	
	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Back")) {
		manager.pop();
	}
}