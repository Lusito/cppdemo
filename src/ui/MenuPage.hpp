#pragma once
#include <string>
#include "nuklear_setup.h"

struct nk_context;

class MenuPage {
protected:
	nk_context* nk;
	std::string name;
	nk_panel layout;

public:
	MenuPage(nk_context* nk, const std::string &name);
	MenuPage(const MenuPage& orig) = delete;
	virtual ~MenuPage();
	
	void update(struct nk_rect &area);
	virtual void show(bool visible);

protected:
	virtual void updateContent(struct nk_rect &area) = 0;

};
