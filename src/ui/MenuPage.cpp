#include "MenuPage.hpp"

MenuPage::MenuPage(nk_context* nk, const std::string &name) : nk(nk), name(name) {
	show(false);
}

MenuPage::~MenuPage() {
	nk_window_close(nk, name.c_str());
}

void MenuPage::update(struct nk_rect &area) {
	if (nk_begin(nk, &layout, name.c_str(), area, 0)) {
		nk_window_set_bounds(nk, area);
		updateContent(area);
	}
	nk_end(nk);
}

void MenuPage::show(bool visible) {
	nk_window_show(nk, name.c_str(), visible ? NK_SHOWN : NK_HIDDEN);
}
