

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "resource/GLMesh.h"
#include "resource/Mesh.h"
#include "resource/ShaderProgram.h"

#include "geometry/Cube.h"
#include "geometry/Geometry.h"

#include "scene/SceneNode.h"
#include "scene/Drawable.h"

#include "editor/Control.h"

static bool init_window(GLFWwindow ** window);

static void gl_clear();

static const float WIDTH = 1000;
static const float HEIGHT = 1000;

int main(int argc, char const *argv[]) {
	
	GLFWwindow * window;
	if (!init_window(&window)) {
		return -1;
	}

	Control ctrl(window, WIDTH, HEIGHT);

	// create an artificial scene
	SceneNode root;

	// load some shader programs and textures
	ShaderProgram default_shader("asset/shaders/default.vert", "asset/shaders/default.frag");

	// build the sceen tree

	Drawable * cube = new Drawable();

	root.setDrawable(cube);

	// main loop
	while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && 
			glfwWindowShouldClose(window) == 0) {
		// one whole process
		gl_clear();
		// view and projection matrix
		glm::mat4 P = ctrl.getProjectionMatrix();
		glm::mat4 V = ctrl.getViewMatrix();
		// the triangle drawing pipeline
		// .
		// load some shader programing into memory
		// .
		// set all uniforms in shader
		// .
		// activate & draw mesh buffers
		//
		root.render(P, V);
		// end draw
	    glfwSwapBuffers(window);
	    glfwPollEvents();
	}

	return 0;
}


static void gl_clear() {
    // Draw the scene:
    glEnable(GL_MULTISAMPLE); // MSAA does not seem to be working
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glDepthFunc (GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClearColor(0.1f, 0.1f, 0.15f, 0.0f);
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

	*window = glfwCreateWindow(WIDTH, HEIGHT, "Hello", nullptr, nullptr);

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


	// I won’t dig into details now, but you need to create a Vertex Array Object and set it as the current one :	
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


	return true;
}
