

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


	// load some shader programs and textures
	// ShaderProgram * default_shader = new ShaderProgram("asset/shaders/normals.vert", "asset/shaders/normals.frag");
	ShaderProgram * default_shader = new ShaderProgram("asset/shaders/blinn.vert", "asset/shaders/blinn.frag");
	// GLuint programID = default_shader->getProgram();
	// build the sceen tree

	Drawable * cube_drawable = new Drawable();
	cube_drawable->setShaderProgram(default_shader);
	cube_drawable->setGeometry(Cube());

	// create an artificial scene
	SceneNode root;
	root.setDrawable(cube_drawable);

	// main loop
	while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && 
			glfwWindowShouldClose(window) == 0) {
		// one whole process
		gl_clear();
		// draw with hand
		// glUseProgram(default_shader->getProgram());

		// GLuint Mid = glGetUniformLocation(default_shader->getProgram(), "M");
		// GLuint Vid = glGetUniformLocation(default_shader->getProgram(), "V");
		// GLuint Pid = glGetUniformLocation(default_shader->getProgram(), "P");
		// GLuint MVPid = glGetUniformLocation(default_shader->getProgram(), "MVP");
		// GLuint Mid = glGetUniformLocation(default_shader->getProgram(), "M");
		// GLuint DTid = glGetUniformLocation(default_shader->getProgram(), "DT");

		// view and projection matrix
		glm::mat4 P = ctrl.getProjectionMatrix();
		glm::mat4 V = ctrl.getViewMatrix();
		// glUniformMatrix4fv(Pid, 1, GL_FALSE, &P[0][0]);
		// glUniformMatrix4fv(Mid, 1, GL_FALSE, &M[0][0]);
		// glUniformMatrix4fv(Vid, 1, GL_FALSE, &V[0][0]);

		// lights
		// glUniform3fv(LightPositionID, 1, &LightPosition[0]);
		// glUniform3fv(LightAmbientID, 1, &LightAmbient[0]);
		// glm::vec3 CameraPosition = ctrl.getCameraPosition();
		// glUniform3fv(CameraPositionID, 1, &CameraPosition[0]);
		// glUniformMatrix4fv(Mid, 1, GL_FALSE, &M[0][0]);
		// glUniformMatrix4fv(Vid, 1, GL_FALSE, &V[0][0]);
		// glUniformMatrix4fv(Pid, 1, GL_FALSE, &P[0][0]);

		// cube_drawable->draw(P, V, glm::mat4(1));

		// glBindVertexArray(VertexArrayID);
		// glDrawElements(GL_TRIANGLES, faces.size(), GL_UNSIGNED_INT, 0);

		// glmesh.render();

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
