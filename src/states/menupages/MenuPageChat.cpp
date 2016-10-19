#include <memory>

#include "MenuPageChat.hpp"
#include "../../state/StateManager.hpp"
#include "../PlayState.hpp"
#include "../../Signals.hpp"
#include <string.h>
#include <GLFW/glfw3.h>

MenuPageChat::MenuPageChat(StateManager& manager, nk_context* nk)
	: MenuPage(manager, nk, "chat") {
	message[0] = '\0';
}

MenuPageChat::~MenuPageChat() { }

void MenuPageChat::updateContent() {
	nk_layout_row_dynamic(nk, 30, 1);
	nk_edit_focus(nk, NK_EDIT_SIMPLE);
	nk_edit_string(nk, NK_EDIT_SIMPLE, message, &messageLength, 256, nk_filter_default);
}

bool MenuPageChat::handleKey(int key, int scancode, int action, int mods) {
	if(key == GLFW_KEY_ENTER && action == GLFW_RELEASE) {
		message[messageLength] = '\0';
		Signals::getInstance()->submitChat.emit(message);
		message[0] = '\0';
		messageLength = 0;
		manager.pop();
		return true;
	}
	return false;
}
