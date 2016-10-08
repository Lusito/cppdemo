#pragma once

struct vertex_data {
    float x, y;
    float r, g, b;
};

class AbstractDemo {
public:
	AbstractDemo();
	AbstractDemo(const AbstractDemo& orig) = delete;
	~AbstractDemo() = default;
	
	void run(const char *title);
	virtual void update(float deltaTime) = 0;
	
protected:
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
	int numPlayers = 1;
};
