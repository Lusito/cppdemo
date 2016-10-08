#pragma once
#include "MenuPage.hpp"

class MenuPageMain : public MenuPage {
private:
	char hostname[256];
	int hostnameLength = 0;

public:
	MenuPageMain(nk_context* nk);
	MenuPageMain(const MenuPageMain& orig) = delete;
	virtual ~MenuPageMain();
	
	virtual void updateContent(struct nk_rect &area);
};
