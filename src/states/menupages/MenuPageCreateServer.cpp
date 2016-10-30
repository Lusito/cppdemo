#include <memory>

#include "MenuPageCreateServer.hpp"
#include "../../state/StateManager.hpp"
#include "../PlayState.hpp"
#include <string.h>

MenuPageCreateServer::MenuPageCreateServer(StateManager& manager, nk_context* nk)
	: MenuPage(manager, nk, "create server") {
	strcpy(servername, "My Server Name");
	strcpy(username, "I am Root");
	servernameLength = strlen(servername);
	usernameLength = strlen(username);
}

MenuPageCreateServer::~MenuPageCreateServer() { }

void MenuPageCreateServer::updateContent() {
	nk_layout_row_dynamic(nk, 30, 1);
	nk_label(nk, "Create Server", NK_TEXT_ALIGN_CENTERED|NK_TEXT_ALIGN_BOTTOM);

	nk_layout_row_dynamic(nk, 30, 1);
	nk_label(nk, "Username:", NK_TEXT_ALIGN_LEFT|NK_TEXT_ALIGN_BOTTOM);

	nk_layout_row_dynamic(nk, 30, 1);
	nk_edit_string(nk, NK_EDIT_SIMPLE, username, &usernameLength, 256, nk_filter_default);

	nk_layout_row_dynamic(nk, 30, 1);
	nk_label(nk, "Servername:", NK_TEXT_ALIGN_LEFT|NK_TEXT_ALIGN_BOTTOM);

	nk_layout_row_dynamic(nk, 30, 1);
	nk_edit_string(nk, NK_EDIT_SIMPLE, servername, &servernameLength, 256, nk_filter_default);

	nk_layout_row_dynamic(nk, 30, 0);
	nk_layout_row_dynamic(nk, 30, 2);
	if (nk_button_label(nk, "Back")) {
		manager.pop();
	}
	if (nk_button_label(nk, "Start")) {
		manager.pop();
		manager.push(std::make_shared<ServerPlayState>(manager, nk, 1234, username, servername));
	}
}