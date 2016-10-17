#include <memory>

#include "MenuPageFindServers.hpp"
#include "MenuPageJoinServer.hpp"
#include "../../state/StateManager.hpp"
#include <string.h>
#include "../../Constants.hpp"
#include "../../Signals.hpp"

MenuPageFindServers::MenuPageFindServers(StateManager& manager, nk_context* nk)
	: MenuPage(manager, nk, "find servers"), discoveryClient(Constants::GAME_NAME) {
	joinServerMenu = std::make_shared<MenuPageJoinServer>(manager, nk);
}

MenuPageFindServers::~MenuPageFindServers() { }

void MenuPageFindServers::updateContent() {
	nk_layout_row_dynamic(nk, 30, 1);
	nk_label(nk, "Find Servers in LAN (checking every 4 seconds)", NK_TEXT_ALIGN_CENTERED|NK_TEXT_ALIGN_BOTTOM);

	discoveryClient.update();
	if(discoveryClient.getServersChanged())
		onServersChanged();

	nk_layout_row_dynamic(nk, 30, 1);
	nk_layout_row_dynamic(nk, 30, 2);
	if (nk_button_label(nk, "Back")) {
		manager.pop();
	}
	nk_label(nk, countLabel.c_str(), NK_TEXT_ALIGN_RIGHT|NK_TEXT_ALIGN_MIDDLE);
	nk_layout_row_dynamic(nk, 30, 1);

	for (auto& server : servers) {
		nk_layout_row_dynamic(nk, 30, 2);
		nk_label(nk, server.label.c_str(), NK_TEXT_ALIGN_LEFT|NK_TEXT_ALIGN_MIDDLE);
		if (nk_button_label(nk, "connect")) {
			//fixme: server.getPort()
			joinServerMenu->setHostname(server.getHostname());
			manager.push(joinServerMenu);
		}
	}
}

void MenuPageFindServers::onServersChanged() {
	servers = discoveryClient.getServers();
	countLabel = "Found " + std::to_string(servers.size()) + " server(s)";
	for (auto& server : servers) {
		uint8_t maxSlots = server.getMaxSlots();
		uint8_t usedSlots = maxSlots - server.getAvailableSlots();
		server.label = server.getServername() + " ("
			+ std::to_string(usedSlots) + "/" + std::to_string(maxSlots) + ")";
	}
}

void MenuPageFindServers::show(bool visible) {
	MenuPage::show(visible);
	if(visible) {
		if(!discoveryClient.start(Constants::DISCOVERY_PORT))
			Signals::getInstance()->error.emit("Could not start discovery client");
		else
			onServersChanged();
	} else {
		discoveryClient.stop();
	}
}
