#pragma once
#include "MenuPage.hpp"
#include <eznet/DiscoveryClient.hpp>

class MenuPageJoinServer;
class MenuPageFindServers : public MenuPage {
private:
	eznet::DiscoveryClient discoveryClient;
	std::vector<eznet::ServerDescription> servers;
	std::shared_ptr<MenuPageJoinServer> joinServerMenu;

public:
	MenuPageFindServers(StateManager& manager, nk_context* nk);
	MenuPageFindServers(const MenuPageFindServers& orig) = delete;
	virtual ~MenuPageFindServers();
	
	void updateContent() override;
	
	void show(bool visible) override;
};
