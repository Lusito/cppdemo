#pragma once

class AbstractState {
private:

public:
	AbstractState();
	AbstractState(const AbstractState& orig) = delete;
	virtual ~AbstractState();

	virtual void entered() {}
	virtual void leaving() {}
	virtual void obscuring() {}
	virtual void reveiling() {}
	virtual void update(float deltaTime) = 0;
	virtual bool handleKey(int key, int scancode, int action, int mods) { return false; }
	virtual void resize(int width, int height) {}
};
