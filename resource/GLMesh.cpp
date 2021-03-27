#include <GL/glew.h>
#include <string>
#include <map>

#include <iostream>

#include "GLMesh.h"

const std::map<std::string, GLint> GLMesh::SHADER_LOCATIONS = {
	{"positions", 0},
	{"normals", 1},
	{"UVs", 2},
	{"colors", 3},
	{"binormals", 4},
	{"tangents", 5}
};

GLMesh::GLMesh() : num_indices_(0) {

	glGenVertexArrays(1, &vertex_array_id_);
	glBindVertexArray(vertex_array_id_);

	// the default arrays
	glGenBuffers(1, &positions_vbo_);
	glGenBuffers(1, &normals_vbo_);
	glGenBuffers(1, &UVs_vbo_);
	glGenBuffers(1, &colors_vbo_);
	glGenBuffers(1, &triangles_vbo_);
}

void GLMesh::setMesh(const Mesh& mesh) {

	// check the mesh for data
	glBindVertexArray(vertex_array_id_);

	//
	auto positions = mesh.getPositions();
	GLint positions_loc = SHADER_LOCATIONS.at("positions");
	if (positions.size() > 0) {
		glBindBuffer(GL_ARRAY_BUFFER, positions_vbo_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * positions.size(), positions.data(), GL_STATIC_DRAW); // Static, Dynamic, or Stream
		glEnableVertexAttribArray(positions_loc);
		// size changed from 3*sizeof(float) to 0
		glVertexAttribPointer(positions_loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	} else {
		glDisableVertexAttribArray(positions_loc);
	}

	auto normals = mesh.getNormals();
	GLint normals_loc = SHADER_LOCATIONS.at("normals");
	if (normals.size() > 0) {
		glBindBuffer(GL_ARRAY_BUFFER, normals_vbo_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(normals_loc);
		glVertexAttribPointer(normals_loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	} else {
		glDisableVertexAttribArray(normals_loc);
	}

	auto UVs = mesh.getUVs();
	GLint UVs_loc = SHADER_LOCATIONS.at("UVs");
	if (UVs.size() > 0) {
		glBindBuffer(GL_ARRAY_BUFFER, UVs_vbo_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * UVs.size(), UVs.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(UVs_loc);
		glVertexAttribPointer(UVs_loc, 2, GL_FLOAT, GL_FALSE, 0, 0);
	} else {
		glDisableVertexAttribArray(UVs_loc);
	}

	auto colors = mesh.getColors();
	GLint colors_loc = SHADER_LOCATIONS.at("colors");
	if (colors.size() > 0) {
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * colors.size(), colors.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(colors_loc);
		glVertexAttribPointer(colors_loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	} else {
		glDisableVertexAttribArray(colors_loc);
	}
	
	// Triangles
	auto triangles = mesh.getTriangles();
    if (triangles.size() > 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangles_vbo_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * triangles.size(), triangles.data(), GL_STATIC_DRAW);
    }
    glBindVertexArray(0);
	num_indices_ = triangles.size();
}


void GLMesh::render() const {
	// assume mesh was set correctly
	if (num_indices_ > 0) {
		glBindVertexArray(vertex_array_id_);
		// Last parameter is a byte offset.
		glDrawElements(GL_TRIANGLES, num_indices_, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}


GLMesh::~GLMesh() {
	glDeleteVertexArrays(1, &vertex_array_id_);
	glDeleteBuffers(1, &positions_vbo_);
	glDeleteBuffers(1, &normals_vbo_);
	glDeleteBuffers(1, &UVs_vbo_);
	glDeleteBuffers(1, &colors_vbo_);
	glDeleteBuffers(1, &triangles_vbo_);
}

