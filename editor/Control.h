#ifndef CONTROLS_H_
#define CONTROLS_H_

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Control
{
public:
	Control(GLFWwindow * window, int width, int height);
	~Control() { };

	glm::mat4 getProjectionMatrix() const { return Projection_; };
	glm::mat4 getViewMatrix() const { return View_; };

	static void onMouseClicked(GLFWwindow * window, int button, int action, int mods);
	static void onMouseMoved(GLFWwindow * window, double xpos, double ypos);
	static void onMouseScrolled(GLFWwindow * window, double xpos, double ypos);

	glm::vec3 getCameraPosition() { return camera_position_; }

private:
	GLFWwindow * window_;
	int width_, height_;

	// position
	glm::vec3 position_;
	float camera_dist_;
	glm::vec3 camera_position_;
	// horizontal angle : toward -Z
	float horizontalAngle_;
	// vertical angle : 0, look at the horizon
	float verticalAngle_;
	// Initial Field of View
	float initialFoV_;

	float speed_; // 3 units / second
	float mouse_rot_speed_;

	glm::mat4 Projection_, View_;

	int active_mouse_button_;
	double mousex_, mousey_;

	void computeMatricesFromInputs();


	static Control * MEEEE; // make it a singleton
};




#endif
