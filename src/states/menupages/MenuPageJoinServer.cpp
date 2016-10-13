#include <memory>

#include "MenuPageJoinServer.hpp"
#include "../../state/StateManager.hpp"
#include "../PlayState.hpp"
#include <string.h>

MenuPageJoinServer::MenuPageJoinServer(StateManager& manager, nk_context* nk)
	: MenuPage(manager, nk, "join server") {
	strcpy(hostname, "localhost");
	strcpy(username, "I are Client");
	hostnameLength = strlen(hostname);
	usernameLength = strlen(username);
}

MenuPageJoinServer::~MenuPageJoinServer() { }

void MenuPageJoinServer::updateContent() {
	nk_layout_row_dynamic(nk, 30, 1);
	nk_label(nk, "Join Server", NK_TEXT_ALIGN_CENTERED|NK_TEXT_ALIGN_BOTTOM);
	
	nk_layout_row_dynamic(nk, 30, 1);
	nk_label(nk, "Hostname or IP:", NK_TEXT_ALIGN_LEFT|NK_TEXT_ALIGN_BOTTOM);
	
	nk_layout_row_dynamic(nk, 30, 1);
	nk_edit_string(nk, NK_EDIT_SIMPLE, hostname, &hostnameLength, 256, nk_filter_default);
	
	nk_layout_row_dynamic(nk, 30, 1);
	nk_label(nk, "Username:", NK_TEXT_ALIGN_LEFT|NK_TEXT_ALIGN_BOTTOM);
	
	nk_layout_row_dynamic(nk, 30, 1);
	nk_edit_string(nk, NK_EDIT_SIMPLE, username, &usernameLength, 256, nk_filter_default);
	
	nk_layout_row_dynamic(nk, 30, 0);
	nk_layout_row_dynamic(nk, 30, 2);
	if (nk_button_label(nk, "Back")) {
		manager.pop();
	}
	if (nk_button_label(nk, "Connect")) {
		while(manager.pop())
			continue;
		manager.push(std::make_shared<ClientPlayState>(manager, nk, hostname, 1234, username));
	}
}