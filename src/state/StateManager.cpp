#include "StateManager.hpp"
#include "AbstractState.hpp"

StateManager::StateManager() { }

StateManager::~StateManager() { }

void StateManager::push(std::shared_ptr<AbstractState> state) {
	if(!states.empty()) {
		auto back = states.back();
		back->obscuring();
	}

	states.push_back(state);
	state->entered();
	state->resize(width, height);
}

bool StateManager::pop() {
	if(states.empty())
		return false;

	{
		auto back = states.back();
		back->leaving();
	}
	states.pop_back();
	if(!states.empty()) {
		auto back = states.back();
		back->resize(width, height);
		back->reveiling();
	}
	return true;
}

void StateManager::update(float deltaTime) {
	if(!states.empty()) {
		auto back = states.back();
		back->update(deltaTime);
	}
}

bool StateManager::handleKey(int key, int scancode, int action, int mods) {
	if(!states.empty()) {
		auto back = states.back();
		return back->handleKey(key, scancode, action, mods);
	}
	return false;
}

void StateManager::resize(int width, int height) {
	this->width = width;
	this->height = height;

	if(!states.empty()) {
		auto back = states.back();
		back->resize(width, height);
	}
}