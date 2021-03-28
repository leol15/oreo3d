

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
#include "geometry/Sphere.h"
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


	// load some shader programs and textures
	// ShaderProgram * default_shader = new ShaderProgram("asset/shaders/normals.vert", "asset/shaders/normals.frag");
	ShaderProgram * default_shader = new ShaderProgram("asset/shaders/blinn.vert", "asset/shaders/blinn.frag");
	// GLuint programID = default_shader->getProgram();
	// build the sceen tree

	Drawable * cube_drawable = new Drawable();
	cube_drawable->setShaderProgram(default_shader);
	cube_drawable->setGeometry(Cube());

	Drawable * sphere_drawable = new Drawable();
	sphere_drawable->setShaderProgram(default_shader);
	sphere_drawable->setGeometry(Sphere());

	// create an artificial scene
	SceneNode * root = new SceneNode();
	root->setDrawable(cube_drawable);

	SceneNode * n2 = new SceneNode();
	n2->setDrawable(sphere_drawable);
	n2->setTranslate({0, -1, 0});

	root->addSceneNode(n2);

	double dx = 1;
	double dv = 0;
	double t = glfwGetTime();
	// main loop
	while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && 
			glfwWindowShouldClose(window) == 0) {
		if (rand() % 30 == 0)
			std::cerr << ((glfwGetTime() - t) * 1000) << std::endl;
		t = glfwGetTime();
		// one whole process
		gl_clear();
		// view and projection matrix
		glm::mat4 P = ctrl.getProjectionMatrix();
		glm::mat4 V = ctrl.getViewMatrix();

		root->render(P, V);
		// end draw
	    glfwSwapBuffers(window);
	    glfwPollEvents();

	    // simulate
		n2->setTranslate({0, dx, 0});
		dv -= 0.005;
		dx += dv;
		if (dx < -1.0) {
			// dv += 0.005;
			dv = -dv;
			dx = -0.99;
		}
	}

	// clean up
	std::cerr << "cleaning up" << std::endl;
	delete default_shader;
	// delete cube_drawable;

	return 0;
}


static void gl_clear() {
    // Draw the scene:
    glEnable(GL_MULTISAMPLE); // MSAA does not seem to be working
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glDepthFunc (GL_LEQUAL);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
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

	return true;
}
