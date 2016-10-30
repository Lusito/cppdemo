#pragma once
#include "MenuPage.hpp"

class MenuPageError : public MenuPage {
private:
	std::string message;

public:
	MenuPageError(StateManager& manager, nk_context* nk);
	MenuPageError(const MenuPageError& orig) = delete;
	virtual ~MenuPageError();

	virtual void updateContent();
	void setMessage(const std::string &message_) {
		message = message_;
	}
};
