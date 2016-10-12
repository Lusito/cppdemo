#pragma once
#include "MenuPage.hpp"

class MenuPageCreateServer;
class MenuPageMain : public MenuPage {
private:
	std::shared_ptr<MenuPageCreateServer> createServerMenu;

public:
	MenuPageMain(StateManager& manager, nk_context* nk);
	MenuPageMain(const MenuPageMain& orig) = delete;
	virtual ~MenuPageMain();
	
	virtual void updateContent();
};
