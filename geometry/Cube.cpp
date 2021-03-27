
#include <glm/glm.hpp>

#include <vector>

#include "Cube.h"
#include "Geometry.h"

// generate data for one face of cube
static void addFace(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d,
		std::vector<glm::vec3> &vertices,
		std::vector<glm::vec3> &normals,
		std::vector<glm::vec2> &UVs,
		std::vector<unsigned int> &triangles);

Cube::Cube () : Geometry() {
	// 6 faces, 24 vertices, since corners of cube have
	// different normals 
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> UVs;
	std::vector<unsigned int> triangles;

	// top bottom
	addFace({0.5, 0.5, -0.5},
			{-0.5, 0.5, -0.5},
			{-0.5, 0.5, 0.5},
			{0.5, 0.5, 0.5},
			vertices, normals, UVs, triangles);

	addFace({0.5, -0.5, 0.5},
			{-0.5, -0.5, 0.5},
			{-0.5, -0.5, -0.5},
			{0.5, -0.5, -0.5},
			vertices, normals, UVs, triangles);

	// left right
	addFace({-0.5, 0.5, -0.5},
			{-0.5, -0.5, -0.5},
			{-0.5, -0.5, 0.5},
			{-0.5, 0.5, 0.5},
			vertices, normals, UVs, triangles);

	addFace({0.5, 0.5, 0.5},
			{0.5, -0.5, 0.5},
			{0.5, -0.5, -0.5},
			{0.5, 0.5, -0.5},
			vertices, normals, UVs, triangles);

	// front back
	addFace({-0.5, 0.5, 0.5},
			{-0.5, -0.5, 0.5},
			{0.5, -0.5, 0.5},
			{0.5, 0.5, 0.5},
			vertices, normals, UVs, triangles);

	addFace({0.5, 0.5, -0.5},
			{0.5, -0.5, -0.5},
			{-0.5, -0.5, -0.5},
			{-0.5, 0.5, -0.5},
			vertices, normals, UVs, triangles);
	// mesh
	mesh_ = new Mesh();
	mesh_->setPositions(vertices);
	mesh_->setNormals(normals);
	mesh_->setUVs(UVs);
	mesh_->setTriangles(triangles);
}

Cube::~Cube() {
	delete mesh_;
}


static void addFace(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d,
		std::vector<glm::vec3> &vertices,
		std::vector<glm::vec3> &normals,
		std::vector<glm::vec2> &UVs,
		std::vector<unsigned int> &triangles) {
	// top face, y > 0
	vertices.push_back(a);
	vertices.push_back(b);
	vertices.push_back(c);
	vertices.push_back(d);

	glm::vec3 normal = glm::normalize(glm::cross(c - a, b - a));
	normals.push_back(normal);
	normals.push_back(normal);
	normals.push_back(normal);
	normals.push_back(normal);

	UVs.push_back({0, 0});
	UVs.push_back({0, 1});
	UVs.push_back({1, 0});
	UVs.push_back({1, 1});

	triangles.push_back(vertices.size() - 4);
	triangles.push_back(vertices.size() - 3);
	triangles.push_back(vertices.size() - 2);

	triangles.push_back(vertices.size() - 4);
	triangles.push_back(vertices.size() - 2);
	triangles.push_back(vertices.size() - 1);
}


