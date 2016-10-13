#pragma once
#include "MenuPage.hpp"

class MenuPageCreateServer;
class MenuPageFindServers;
class MenuPageJoinServer;
class MenuPageMain : public MenuPage {
private:
	std::shared_ptr<MenuPageCreateServer> createServerMenu;
	std::shared_ptr<MenuPageFindServers> findServersMenu;
	std::shared_ptr<MenuPageJoinServer> joinServerMenu;

public:
	MenuPageMain(StateManager& manager, nk_context* nk);
	MenuPageMain(const MenuPageMain& orig) = delete;
	virtual ~MenuPageMain();
	
	virtual void updateContent();
};
