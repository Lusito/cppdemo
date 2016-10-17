#include <memory>

#include "MenuPageConnecting.hpp"
#include "../../state/StateManager.hpp"
#include "../PlayState.hpp"
#include "../../Signals.hpp"
#include <string.h>

MenuPageConnecting::MenuPageConnecting(StateManager& manager, nk_context* nk)
	: MenuPage(manager, nk, "error") {
	connectionScope += Signals::getInstance()->serverConnected.connect(this, &MenuPageConnecting::onServerConnected);
}

MenuPageConnecting::~MenuPageConnecting() { }

void MenuPageConnecting::updateContent() {
	nk_layout_row_dynamic(nk, 30, 1);
	nk_label(nk, "Connecting to server", NK_TEXT_ALIGN_CENTERED|NK_TEXT_ALIGN_BOTTOM);
	nk_layout_row_dynamic(nk, 30, 1);
	nk_label(nk, message.c_str(), NK_TEXT_ALIGN_CENTERED|NK_TEXT_ALIGN_BOTTOM);
	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Disconnect")) {
		Signals::getInstance()->error.emit("User stopped connection process");
	}
}

void MenuPageConnecting::onServerConnected() {
	manager.pop();
}
