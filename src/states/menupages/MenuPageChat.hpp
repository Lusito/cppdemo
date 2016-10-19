#pragma once
#include "MenuPage.hpp"

class MenuPageChat : public MenuPage {
private:
	char message[256];
	int messageLength = 0;

public:
	MenuPageChat(StateManager& manager, nk_context* nk);
	MenuPageChat(const MenuPageChat& orig) = delete;
	virtual ~MenuPageChat();
	
	void updateContent() override;

	void resize(int width, int height) override {
		MenuPage::resize(width, height-50);
		area.y = area.h;
	}
	bool handleKey(int key, int scancode, int action, int mods) override;
};
