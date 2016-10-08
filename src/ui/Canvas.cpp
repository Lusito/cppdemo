#include "Canvas.hpp"

Canvas::Canvas(nk_context* nk) : nk(nk) { }

Canvas::~Canvas() { }

void Canvas::update(struct nk_rect &area) {
    backupPadding = nk->style.window.padding;
    backupSpacing = nk->style.window.spacing;
    backupBackground = nk->style.window.fixed_background;

    nk->style.window.spacing = nk_vec2(0,0);
    nk->style.window.padding = nk_vec2(0,0);
    nk->style.window.fixed_background = nk_style_item_color(nk_rgb(0,0,0));

    if(nk_begin(nk, &layout, "Canvas", area, NK_WINDOW_NO_SCROLLBAR)) {
		nk_window_set_bounds(nk, area);
		nk_layout_row_dynamic(nk, area.h, 1);
		nk_widget(&area, nk);
		painter = nk_window_get_canvas(nk);
	
		draw();
	}
    nk_end(nk);
	nk->style.window.spacing = backupPadding;
	nk->style.window.padding = backupSpacing;
	nk->style.window.fixed_background = backupBackground;
}

void Canvas::draw() {
	struct nk_rect circle{50,200,50,50};
	nk_color red{255,0,0,255};
	nk_fill_circle(painter, circle, red);
}
