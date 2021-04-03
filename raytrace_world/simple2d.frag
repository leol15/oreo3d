#version 330 core


in vec3 color_frag;
out vec3 color;

void main() {
	color = color_frag;
}