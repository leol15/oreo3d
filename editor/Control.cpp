
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Control.h"


Control * Control::MEEEE = nullptr; // make it a singleton

// goal:
// interactivly change the ViewMatrix
Control::Control(GLFWwindow * window, int width, int height)
		: window_(window), width_(width), height_(height),
		position_(glm::vec3(0, 0, 0)),
		camera_dist_(5),
		camera_position_(glm::vec3(0)),
		horizontalAngle_(3.14f),
		verticalAngle_(0.0f),
		initialFoV_(45.0f),
		speed_(0.0009f),
		mouse_rot_speed_(0.002f),
		Projection_(glm::mat4(1)),
		View_(glm::mat4(1)),
		active_mouse_button_(-1), 
		mousex_(0), mousey_(0) {

	// register some callbacks
	MEEEE = this; // make it a singleton
	glfwSetScrollCallback(window, &Control::onMouseScrolled);
	glfwSetMouseButtonCallback(window_, &Control::onMouseClicked);
	glfwSetCursorPosCallback(window, &Control::onMouseMoved);

	// Projection matrix : 45&deg; Field of View, ratio as screen size, display range : 0.1 unit <-> 100 units
	Projection_ = glm::perspective(glm::radians(45.0f), (float) width_ / height_, 0.1f, 100.0f);
	
	computeMatricesFromInputs();
}


void Control::onMouseScrolled(GLFWwindow * window, double xoff, double yoff) {
	// -1 or 1
	// flip to make sense
	MEEEE->camera_dist_ -= yoff / 2.0;
	MEEEE->camera_dist_ = abs(MEEEE->camera_dist_);
	MEEEE->computeMatricesFromInputs();
}

static bool WIRE_FRAME = false;
// state machine
void Control::onMouseClicked(GLFWwindow * window, int button, int action, int mods) {
	// left 0
	// right 1
	// mid 2
	// down 1 
	// up 0
	if (action == 0) {
		MEEEE->active_mouse_button_ = -1;
		return;
	}
	// some button is pressed
	MEEEE->active_mouse_button_ = button;
	glfwGetCursorPos(window, &(MEEEE->mousex_), &(MEEEE->mousey_));

	// special actions
	if (action == 1 && button == 3) {
		MEEEE->position_ = glm::vec3(0);
	} else if (action == 1 && button == 4) {
		WIRE_FRAME = !WIRE_FRAME;
		if (WIRE_FRAME) {
			glDisable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		} else {
			glEnable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	MEEEE->computeMatricesFromInputs();

}

void Control::onMouseMoved(GLFWwindow * window, double xpos, double ypos) {
	// some button is moving
	switch (MEEEE->active_mouse_button_) {
		case 0:
			// std::cerr << "but 0" << std::endl;
			break;
		case 1:
			// rotate it
			// Compute new orientation
			MEEEE->horizontalAngle_ += MEEEE->mouse_rot_speed_ * float(MEEEE->mousex_ - xpos);
			// flip to make angling more intuitive
			MEEEE->verticalAngle_   -= MEEEE->mouse_rot_speed_ * float(MEEEE->mousey_ - ypos);
			MEEEE->verticalAngle_ = std::max(-3.1415f / 2.0f, std::min(3.1415f / 2.0f, MEEEE->verticalAngle_));
			MEEEE->computeMatricesFromInputs();
			break;
		case 2:
			// translate
			{
				// Direction : Spherical coordinates to Cartesian coordinates conversion
				glm::vec3 direction(
				    cos(MEEEE->verticalAngle_) * sin(MEEEE->horizontalAngle_),
				    sin(MEEEE->verticalAngle_),
				    cos(MEEEE->verticalAngle_) * cos(MEEEE->horizontalAngle_)
				);

				direction = glm::normalize(direction);

				// Right vector
				glm::vec3 right = glm::vec3(
				    sin(MEEEE->horizontalAngle_ - 3.14f/2.0f),
				    0,
				    cos(MEEEE->horizontalAngle_ - 3.14f/2.0f)
				);

				right = glm::normalize(right);
				glm::vec3 up = glm::cross(right, direction);
				// flip for intuitive control
				MEEEE->position_ -= MEEEE->speed_ * right * (MEEEE->mousex_ - xpos) * MEEEE->camera_dist_;
				MEEEE->position_ -= MEEEE->speed_ * up * (MEEEE->mousey_ - ypos) * MEEEE->camera_dist_;
				MEEEE->computeMatricesFromInputs();
			}
			break;
		default:
		// noone is active
			break;
	}
	MEEEE->mousex_ = xpos;
	MEEEE->mousey_ = ypos;
}


void Control::computeMatricesFromInputs() {

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
	    cos(verticalAngle_) * sin(horizontalAngle_),
	    sin(verticalAngle_),
	    cos(verticalAngle_) * cos(horizontalAngle_)
	);

	direction = glm::normalize(direction);

	// Right vector
	glm::vec3 right = glm::vec3(
	    sin(horizontalAngle_ - 3.14f / 2.0f),
	    0,
	    cos(horizontalAngle_ - 3.14f / 2.0f)
	);

	// Up vector : perpendicular to both direction and right
	glm::vec3 up = glm::cross(right, direction);

	// Camera matrix
	camera_position_ = position_ + direction * camera_dist_;
	View_ = glm::lookAt(camera_position_, position_, up);

}
