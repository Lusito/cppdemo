#include "ChatRenderSystem.hpp"
#include "../components/PositionComponent.hpp"
#include "../components/RenderComponent.hpp"
#include "../ui/Canvas.hpp"
#include "../Signals.hpp"

const float LINE_BLEND_TIME = 2; // seconds

ChatRenderSystem::ChatRenderSystem(nk_context* nk) : nk(nk), area{0,0,0,0} {
	connectionScope += Signals::getInstance()->chat.connect(this, &ChatRenderSystem::onChat);
}

void ChatRenderSystem::update(float deltaTime) {
	if(!messages.empty()) {
		lineTime+= deltaTime;
		if(lineTime > LINE_BLEND_TIME) {
			lineTime -= LINE_BLEND_TIME;
			messages.pop_front();
		}
	}

	if (nk_begin(nk, &layout, "chat log", area, NK_WINDOW_NO_SCROLLBAR)) {
		nk_window_set_bounds(nk, area);
		for (auto &msg : messages) {
			nk_layout_row_dynamic(nk, 40, 1);
			nk_label_wrap(nk, msg.c_str());
		}
	}
	nk_end(nk);
}

void ChatRenderSystem::onChat(const std::string &message, const std::string &username) {
	messages.emplace_back(username + ": " + message);
}
