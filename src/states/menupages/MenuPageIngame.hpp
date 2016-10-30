#pragma once
#include "MenuPage.hpp"

class MenuPageIngame : public MenuPage {
public:
	MenuPageIngame(StateManager& manager, nk_context* nk);
	MenuPageIngame(const MenuPageIngame& orig) = delete;
	virtual ~MenuPageIngame();

	virtual void updateContent();
};
