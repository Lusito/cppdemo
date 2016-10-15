#include "../generated/MessageAdapters.hpp"
#include "Game.hpp"
#include <eznet/Utils.hpp>

int main(void) {
	eznet::init();
	Game game;
	game.run();
	return 0;
}
