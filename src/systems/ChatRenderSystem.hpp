#pragma once
#include "../ui/nuklear_setup.h"
#include <ecstasy/core/EntitySystem.hpp>
#include <deque>
#include <signal11/Signal.hpp>

class Canvas;
class ChatRenderSystem : public EntitySystem<ChatRenderSystem> {
private:
	nk_context* nk;
	nk_panel layout;
	struct nk_rect area;
	std::deque<std::string> messages;
	float lineTime = 0;
	ConnectionScope connectionScope;

public:
	ChatRenderSystem(nk_context* nk);
	
	void update(float deltaTime) override;
	
	void resize(int width, int height) {
		area.w = width;
		area.h = height - 50;
	}

private:
	void onChat(const std::string &message, const std::string &username);
};
