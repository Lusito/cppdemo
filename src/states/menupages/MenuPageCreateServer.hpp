#pragma once
#include "MenuPage.hpp"

class MenuPageCreateServer : public MenuPage {
private:
	char servername[256];
	int servernameLength = 0;
	char username[256];
	int usernameLength = 0;

public:
	MenuPageCreateServer(StateManager& manager, nk_context* nk);
	MenuPageCreateServer(const MenuPageCreateServer& orig) = delete;
	virtual ~MenuPageCreateServer();
	
	virtual void updateContent();
};
