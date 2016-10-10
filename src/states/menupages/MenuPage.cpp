#include "MenuPage.hpp"

MenuPage::MenuPage(StateManager& manager, nk_context* nk, const std::string &name)
	: manager(manager), nk(nk), name(name), area{0,0,0,0} {
	show(false);
}

MenuPage::~MenuPage() {
	nk_window_close(nk, name.c_str());
}

void MenuPage::update(float deltaTime) {
	if (nk_begin(nk, &layout, name.c_str(), area, 0)) {
		nk_window_set_bounds(nk, area);
		updateContent();
	}
	nk_end(nk);
}

void MenuPage::show(bool visible) {
	nk_window_show(nk, name.c_str(), visible ? NK_SHOWN : NK_HIDDEN);
}
