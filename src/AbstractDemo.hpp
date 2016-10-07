#pragma once

struct vertex_data {
    float x, y;
    float r, g, b;
};

const int MAX_PLAYERS = 4;
class AbstractDemo {
public:
	AbstractDemo();
	AbstractDemo(const AbstractDemo& orig) = delete;
	~AbstractDemo() = default;
	
	void run(const char *title);
	virtual void update(float deltaTime) = 0;
	
protected:
	vertex_data vertices[MAX_PLAYERS];
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
};
