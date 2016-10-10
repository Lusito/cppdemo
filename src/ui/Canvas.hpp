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
	struct nk_rect area{0,0,0,0};

public:
	Canvas(nk_context* nk);
	Canvas(const Canvas& orig) = delete;
	~Canvas();
	
	void begin();
	void end();
	
	float setSize(float width, float height) {
		area.w = width;
		area.h = height;
	}
	
	void drawCircle(float x, float y, float radius, nk_color &color);
};
