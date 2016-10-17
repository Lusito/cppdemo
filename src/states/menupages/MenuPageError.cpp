#include <memory>

#include "MenuPageError.hpp"
#include "../../state/StateManager.hpp"
#include "../PlayState.hpp"
#include <string.h>

MenuPageError::MenuPageError(StateManager& manager, nk_context* nk)
	: MenuPage(manager, nk, "error") {
}

MenuPageError::~MenuPageError() { }

void MenuPageError::updateContent() {
	nk_layout_row_dynamic(nk, 30, 1);
	nk_label_colored(nk, "Error", NK_TEXT_ALIGN_CENTERED|NK_TEXT_ALIGN_BOTTOM, nk_rgb(255, 0,0));
	nk_layout_row_dynamic(nk, 30, 1);
	nk_label_colored(nk, message.c_str(), NK_TEXT_ALIGN_CENTERED|NK_TEXT_ALIGN_BOTTOM, nk_rgb(255, 0,0));
	nk_layout_row_dynamic(nk, 30, 1);
	if (nk_button_label(nk, "Back")) {
		manager.pop();
	}
}