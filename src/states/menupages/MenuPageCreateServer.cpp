#include <memory>

#include "MenuPageCreateServer.hpp"
#include "../../state/StateManager.hpp"
#include "../PlayState.hpp"
#include <string.h>

MenuPageCreateServer::MenuPageCreateServer(StateManager& manager, nk_context* nk)
	: MenuPage(manager, nk, "create server") {
	strcpy(servername, "My Server Name");
	strcpy(username, "My User Name");
	servernameLength = strlen(servername);
	usernameLength = strlen(username);
}

MenuPageCreateServer::~MenuPageCreateServer() { }

void MenuPageCreateServer::updateContent() {
	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Start")) {
		while(manager.pop())
			continue;
		manager.push(std::make_shared<ServerPlayState>(manager, nk, 1234, username, servername));
	}
	nk_layout_row_dynamic(nk, 30, 1);
	nk_edit_string(nk, NK_EDIT_SIMPLE, username, &usernameLength, 256, nk_filter_default);
	
	nk_layout_row_dynamic(nk, 30, 1);
	nk_edit_string(nk, NK_EDIT_SIMPLE, servername, &servernameLength, 256, nk_filter_default);
	
	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Back")) {
		manager.pop();
	}
}