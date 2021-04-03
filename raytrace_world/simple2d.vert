#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;

out vec3 color_frag;

void main() {
	// gl_Position = vec4((position.x - 0.5) * 2, -(position.y - 0.5) * 2, 0, 1);
	gl_Position = vec4(position.x, position.y, 0, 1);
	color_frag = color;
}