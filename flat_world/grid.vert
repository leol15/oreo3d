#version 330 core

layout(location = 0) in vec2 position;
// layout(location = 1) in vec3 normal_model;
// layout(location = 2) in vec2 uv;
// layout(location = 3) in vec3 color;

// Values that stay constant for the whole mesh.
// uniform mat4 M;  // to world space
// uniform mat4 V;
// uniform mat4 P;

uniform int CELL_TYPE;

// out vec3 position_frag;
// out vec3 normal_world;
out vec4 color_frag;

void main() {
	// gl_Position = P * V * M * vec4(position , 1);
	// 0~1 -> -1~1
	gl_Position = vec4((position.x - 0.5) * 2, -(position.y - 0.5) * 2, 0, 1);
	// gl_Position = vec4(rand() % 10 / 10.0f, rand() % 10 / 10.0f, 0, 1);
	// normal mapping
	// vec3 mapped_normal = normalize(vec3(sin(normal_model.x * 100), normal_model.y, normal_model.z));

	// position_world = position;
	// normal_world = (M * vec4(normal_model, 0)).xyz;
	switch (CELL_TYPE) {
		case 0:  // sand
			color_frag = vec4(0.9, 0.7, 0.2, 1);
			break;
		case 1:  // water
			color_frag = vec4(0.1, 0.4, 1, 1);
			break;
		case 2:  // stone
			color_frag = vec4(0.4, 0.4, 0.4, 1);
			break;
		default:
			color_frag = vec4(1, 1, 1, 0.5);
	}
}