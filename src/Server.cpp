#include "../generated/MessageAdapters.hpp"
#include "AbstractDemo.hpp"

const float PLAYER_SPEED = 0.4f;
class Server: public AbstractDemo {
public:
	void update(float deltaTime) {
		float x = 0, y = 0;
		if(moveUp)
			y += 1;
		if(moveDown)
			y -= 1;
		if(moveLeft)
			x -= 1;
		if(moveRight)
			x += 1;
		vertices[2].x += x * deltaTime * PLAYER_SPEED;
		vertices[2].y += y * deltaTime * PLAYER_SPEED;
	}
};

int main(void) {
	Server server;
	server.run("Server");
	return 0;
}
