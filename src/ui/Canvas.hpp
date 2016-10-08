#pragma once 

#include "nuklear_setup.h"

class Canvas {
private:
	nk_context* nk;
    struct nk_panel layout;
    struct nk_command_buffer *painter;
    struct nk_vec2 backupSpacing;
    struct nk_vec2 backupPadding;
    struct nk_style_item backupBackground;

public:
	Canvas(nk_context* nk);
	Canvas(const Canvas& orig) = delete;
	~Canvas();
	
	void update(struct nk_rect &area);
	
private:
	void draw();
};
