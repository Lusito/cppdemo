#include "Game.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#define NK_IMPLEMENTATION
#include "ui/nuklear_setup.h"
#include "ui/Canvas.hpp"

#define NK_GLFW_GL2_IMPLEMENTATION
#include <nuklear_glfw_gl2.h>

#include "state/StateManager.hpp"
#include "states/menupages/MenuPageMain.hpp"
#include <ecstasy/utils/EntityFactory.hpp>
#include "components/ComponentFactories.hpp"
#include "components/PlayerComponent.hpp"
#include "components/LocalPlayerComponent.hpp"
#include "components/InputComponent.hpp"
#include "components/PositionComponent.hpp"
#include "components/VelocityComponent.hpp"
#include "components/RenderComponent.hpp"

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

auto createEntityFactory() {
	auto factory = std::make_shared<EntityFactory>();
	
	// Setup component factories
	factory->addComponentFactory<RenderComponentFactory>("Render");
	factory->addComponentFactory<SimpleComponentFactory<InputComponent>>("Input");
	factory->addComponentFactory<SimpleComponentFactory<LocalPlayerComponent>>("LocalPlayer");
	factory->addComponentFactory<SimpleComponentFactory<PlayerComponent>>("Player");
	factory->addComponentFactory<SimpleComponentFactory<PositionComponent>>("Position");
	factory->addComponentFactory<SimpleComponentFactory<VelocityComponent>>("Velocity");

	// Fixme: read blueprints from .def files instead.
	auto playerBlueprint = std::make_shared<EntityBlueprint>();
	auto renderBlueprint = std::make_shared<ComponentBlueprint>("Render");
	renderBlueprint->set("size", "25");
	renderBlueprint->set("color", "FF0000");
	playerBlueprint->add(renderBlueprint);
	playerBlueprint->add(std::make_shared<ComponentBlueprint>("Input"));
	playerBlueprint->add(std::make_shared<ComponentBlueprint>("Player"));
	playerBlueprint->add(std::make_shared<ComponentBlueprint>("Position"));
	playerBlueprint->add(std::make_shared<ComponentBlueprint>("Velocity"));
	factory->addEntityBlueprint("player", playerBlueprint);

	return factory;
}

Game::Game() {}

void Game::run() {
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640, 480, "Demo", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

    struct nk_context* nk;
    struct nk_font_atlas* atlas;

    nk = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);
    nk_glfw3_font_stash_begin(&atlas);
    nk_glfw3_font_stash_end();

	{
		int width, height;
        glfwGetWindowSize(window, &width, &height);
		stateManager.resize(width, height);
	}
	glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, [] (GLFWwindow* window, int key, int scancode, int action, int mods) {
		Game* self = static_cast<Game *>(glfwGetWindowUserPointer(window));
		self->getStateManager().handleKey(key, scancode, action, mods);
	});
    glfwSetWindowSizeCallback(window, [] (GLFWwindow* window, int width, int height) {
		Game* self = static_cast<Game *>(glfwGetWindowUserPointer(window));
		self->getStateManager().resize(width, height);
	});
	
	stateManager.setEntityFactory(createEntityFactory());
	auto mainmenu = std::make_shared<MenuPageMain>(stateManager, nk);
	stateManager.push(mainmenu);

	double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
		double now = glfwGetTime();
		double deltaTime = now - lastTime;
		lastTime = now;

        glClear(GL_COLOR_BUFFER_BIT);
        nk_glfw3_new_frame();
		nk->style.window.fixed_background.data.color.a = 0;
		
		stateManager.update(deltaTime);

        nk_glfw3_render(NK_ANTI_ALIASING_ON, 10000, 1000);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
