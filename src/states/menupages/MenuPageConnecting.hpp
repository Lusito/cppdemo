#pragma once
#include "MenuPage.hpp"
#include <signal11/Signal.hpp>

class MenuPageConnecting : public MenuPage {
private:
	std::string message;
	ConnectionScope connectionScope;

public:
	MenuPageConnecting(StateManager& manager, nk_context* nk);
	MenuPageConnecting(const MenuPageConnecting& orig) = delete;
	virtual ~MenuPageConnecting();

	virtual void updateContent();
	void setMessage(const std::string &message_) {
		message = message_;
	}

private:
	void onServerConnected();
};
