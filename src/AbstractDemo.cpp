#include "AbstractDemo.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#define NK_IMPLEMENTATION
#include "ui/nuklear_setup.h"
#include "ui/MenuPageMain.hpp"
#include "ui/Canvas.hpp"

#define NK_GLFW_GL2_IMPLEMENTATION
#include <nuklear_glfw_gl2.h>

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

AbstractDemo::AbstractDemo() {}

void AbstractDemo::run(const char *title) {
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640, 480, title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

	glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, [] (GLFWwindow* window, int key, int scancode, int action, int mods) {
		AbstractDemo* self = static_cast<AbstractDemo *>(glfwGetWindowUserPointer(window));
		bool down = action != GLFW_RELEASE;
		switch(key) {
		case GLFW_KEY_ESCAPE:
			if(down)
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		case GLFW_KEY_UP:
			self->moveUp = down;
			break;
		case GLFW_KEY_DOWN:
			self->moveDown = down;
			break;
		case GLFW_KEY_LEFT:
			self->moveLeft = down;
			break;
		case GLFW_KEY_RIGHT:
			self->moveRight = down;
			break;
		}
	});

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

    struct nk_context* nk;
    struct nk_font_atlas* atlas;

    nk = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);
    nk_glfw3_font_stash_begin(&atlas);
    nk_glfw3_font_stash_end();

	MenuPageMain mainmenu(nk);
	Canvas canvas(nk);

	struct nk_rect area {0,0,0,0};
	int width, height;
	
	double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
		double now = glfwGetTime();
		double deltaTime = now - lastTime;
		lastTime = now;
		

        glfwGetWindowSize(window, &width, &height);
        area.w = (float) width;
		area.h = (float) height;

        glClear(GL_COLOR_BUFFER_BIT);
        nk_glfw3_new_frame();
		nk->style.window.fixed_background.data.color.a = 0;
		
		update((float)deltaTime);
		canvas.update(area);
		mainmenu.update(area);

        nk_glfw3_render(NK_ANTI_ALIASING_ON, 10000, 1000);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
