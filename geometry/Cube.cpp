
#include <vector>

#include "Cube.h"
#include <glm/glm.hpp>

Cube::Cube () {
	// 6 faces, 24 vertices, since corners of cube have
	// different normals 
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> UVs;
	std::vector<unsigned int> triangles;

	// top face, y > 0
	vertices.push_back({0.5, 0.5, 0.5});
	normals.push_back({0, 1, 0});
	UVs.push_back({0, 0});

	vertices.push_back({0.5, 0.5, -0.5});
	normals.push_back({0, 1, 0});
	UVs.push_back({0, 1});

	vertices.push_back({-0.5, 0.5, 0.5});
	normals.push_back({0, 1, 0});
	UVs.push_back({1, 0});

	vertices.push_back({-0.5, 0.5, -0.5});
	normals.push_back({0, 1, 0});
	UVs.push_back({1, 1});

	triangles.push_back(0);
	triangles.push_back(1);
	triangles.push_back(2);
	triangles.push_back(1);
	triangles.push_back(3);
	triangles.push_back(2);

	// mesh
	mesh_ = new Mesh();
	mesh_->setPositions(vertices);
	mesh_->setNormals(normals);
	mesh_->setUVs(UVs);
	mesh_->setTriangles(triangles);
}


