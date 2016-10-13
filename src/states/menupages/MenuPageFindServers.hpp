#pragma once
#include "MenuPage.hpp"

class MenuPageFindServers : public MenuPage {
private:

public:
	MenuPageFindServers(StateManager& manager, nk_context* nk);
	MenuPageFindServers(const MenuPageFindServers& orig) = delete;
	virtual ~MenuPageFindServers();
	
	virtual void updateContent();
};
