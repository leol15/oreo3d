



#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "../resource/GLMesh.h"
#include "../resource/Mesh.h"
#include "../resource/ShaderProgram.h"

#include "../geometry/Cube.h"
#include "../geometry/Sphere.h"
#include "../geometry/Geometry.h"

#include "../scene/SceneNode.h"
#include "../scene/Drawable.h"

#include "../editor/Control.h"

#include "grid_world.h"

#include <iomanip>

static bool init_window(GLFWwindow ** window);

static void gl_clear();

static const float WINDOW_WIDTH = 1000;
static const float WINDOW_HEIGHT = 1000;

// callbacks to interact
static int CLICK_SIZE = 5;
static int BUTTON_ID = 0;
static int ACTION_ID = 0;
static double MOUSE_X, MOUSE_Y;
static void onMouseClicked(GLFWwindow * window, int button, int action, int mods);
static void onMouseMoved(GLFWwindow * window, double xpos, double ypos);
static void onKeyboardEvent(GLFWwindow * window, int key, int scancode, int action, int mods);

static const int WORLD_WIDTH = 300;
static const int WORLD_HEIGHT = 300;

static GridWorld * WORLD;

int main(int argc, char const *argv[]) {
	
	GLFWwindow * window;
	if (!init_window(&window)) {
		return -1;
	}

	// set up mouse input
	WORLD = new GridWorld(WORLD_WIDTH, WORLD_HEIGHT);
	glfwSetMouseButtonCallback(window, &onMouseClicked);
	glfwSetCursorPosCallback(window, &onMouseMoved);
	glfwSetKeyCallback(window, &onKeyboardEvent);


	// WORLD->setCellType(CellType::WATER);
	// WORLD->addCell(0, 0);
	// WORLD->setCellType(CellType::STONE);
	// WORLD->addCell(0, 1);
	// WORLD->setCellType(CellType::SAND);
	// WORLD->addCell(4, 4);

	// load some shader programs and textures
	// ShaderProgram * default_shader = new ShaderProgram("asset/shaders/normals.vert", "asset/shaders/normals.frag");
	ShaderProgram default_shader("./grid.vert", "./grid.frag");
	GLuint programID = default_shader.getProgram();

	double t0, t1, t2;
	// double t = glfwGetTime();
	// main loop
	while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && 
			glfwWindowShouldClose(window) == 0) {
		t0 = glfwGetTime();
		// std::cerr << 1000 * (glfwGetTime() - t) << std::endl;
		// t = glfwGetTime();

		// one whole process
		gl_clear();
		// draw grid
		t1 = glfwGetTime();

		// #define BUG(X, t1, t2) std::cerr << (X) << ": " << std::setw(5) << (int)(10000 * (t2 - t1)) / 10.0f << "|";
		#define BUG(X, t1, t2)


		// dont update when pressed
		// if (ACTION_ID == 0)
		WORLD->update();
		t2 = glfwGetTime();
		BUG("u", t1, t2);

		t1 = glfwGetTime();
		WORLD->draw(programID);
		t2 = glfwGetTime();
		BUG("d", t1, t2);


		// end draw
		t1 = glfwGetTime();
	    glfwSwapBuffers(window);
		t2 = glfwGetTime();
		BUG(" swap", t1, t2);

		t1 = glfwGetTime();
	    glfwPollEvents();
		t2 = glfwGetTime();
		BUG("poll", t1, t2);
		BUG("total", t0, t2);
		// std::cerr << std::endl;

		// constantly pressed
		if (BUTTON_ID == 0 && ACTION_ID == 1)
			onMouseMoved(window, MOUSE_X, MOUSE_Y);
	}

	// clean up
	std::cerr << "cleaning up" << std::endl;
	// delete cube_drawable;
	delete WORLD;

	return 0;
}


static void gl_clear() {
    // Draw the scene:
    // glEnable(GL_MULTISAMPLE); // MSAA does not seem to be working
    // glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glDepthFunc (GL_LEQUAL);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    glClearColor(0.6f, 0.6f, 0.6f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


static bool init_window(GLFWwindow ** window) {
	// Initialise GLFW
	glewExperimental = true; // Needed for core profile
	if( !glfwInit() )
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	*window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello", nullptr, nullptr);

	if (*window == nullptr) {
		std::cerr << "GLFW window cannot open" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(*window); // Initialize GLEW
	glewExperimental=true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
    	return false;
	}
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(*window, GLFW_STICKY_KEYS, GL_TRUE);
	return true;
}


static void onMouseClicked(GLFWwindow * window, int button, int action, int mods) {
	BUTTON_ID = button;
	ACTION_ID = action;
	glfwGetCursorPos(window, &MOUSE_X, &MOUSE_Y);
}

static void onMouseMoved(GLFWwindow * window, double xpos, double ypos) {
	if (BUTTON_ID == 0 && ACTION_ID == 1) {
		// pressed dragging
		if (WORLD != nullptr)
			WORLD->addCell(
				xpos / WINDOW_WIDTH * WORLD_WIDTH, 
				ypos / WINDOW_HEIGHT * WORLD_HEIGHT,
				CLICK_SIZE);
		MOUSE_X = xpos;
		MOUSE_Y = ypos;
	}
}


static void onKeyboardEvent(GLFWwindow * window, int key, int scancode, int action, int mods) {
	if (action == 1 && WORLD != nullptr) {
		switch (key) {
			case 321:
				WORLD->setCellType(CellType::SAND);
				break;
			case 322:
				WORLD->setCellType(CellType::WATER);
				break;
			case 323:
				WORLD->setCellType(CellType::STONE);
				break;
			case 32:
				WORLD->reset();
				break;
			default:
				if (48 < key && key < 59) {
					CLICK_SIZE = key - 48; 
				}
				break;
		}
		// if (key == )
	}
	// std::cerr << key << ":" << action << ":" << scancode << std::endl;
}
