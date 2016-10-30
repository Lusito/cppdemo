#pragma once
#include "MenuPage.hpp"

class MenuPageJoinServer : public MenuPage {
private:
	char hostname[256];
	int hostnameLength = 0;
	char username[256];
	int usernameLength = 0;

public:
	MenuPageJoinServer(StateManager& manager, nk_context* nk);
	MenuPageJoinServer(const MenuPageJoinServer& orig) = delete;
	virtual ~MenuPageJoinServer();

	virtual void updateContent();
	void setHostname(const std::string &hostname);
};
