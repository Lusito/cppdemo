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
	nk_label(nk, "Find Servers in LAN", NK_TEXT_ALIGN_CENTERED|NK_TEXT_ALIGN_BOTTOM);

	discoveryClient.update();
	if(discoveryClient.getServersChanged())
		servers = discoveryClient.getServers();
	for (auto& server : servers) {
		nk_layout_row_dynamic(nk, 30, 1);
		//fixme: generate label when servers changed?
		uint8_t maxSlots = server.getMaxSlots();
		uint8_t usedSlots = maxSlots - server.getAvailableSlots();
		std::string name = server.getServername() + " ("
			+ std::to_string(usedSlots) + "/" + std::to_string(maxSlots) + ")";
		if (nk_button_label(nk, name.c_str())) {
			//fixme: server.getPort()
			joinServerMenu->setHostname(server.getHostname());
			manager.push(joinServerMenu);
		}
	}

	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Back")) {
		manager.pop();
	}
}

void MenuPageFindServers::show(bool visible) {
	MenuPage::show(visible);
	if(visible) {
		if(!discoveryClient.start(Constants::DISCOVERY_PORT))
			Signals::getInstance()->error.emit("Could not start discovery client");
		else
			servers = discoveryClient.getServers();
	} else {
		discoveryClient.stop();
	}
}
