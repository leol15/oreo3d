#version 330 core

// in vec3 position_world;
// in vec3 normal_world;


// in vec3 position_frag;
// in vec3 normal_world;
in vec4 color_frag;

out vec4 color;

void main() {

	color = color_frag;
	// color = vec4(1, 0.5, 1, 1);

}