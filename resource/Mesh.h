#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <vector>
#include <map>
// a real mesh with values
class Mesh {
public:
	Mesh() { };

	// construct from a surface of revolution
	Mesh(const std::vector<glm::vec2> pts2d, int num_bands);

	// setter
	void setPositions(std::vector<glm::vec3>& positions) { positions_ = positions; };
	void setNormals(std::vector<glm::vec3>& normals) { normals_ = normals; };
	void setUVs(std::vector<glm::vec2>& UVs) { UVs_ = UVs; };
	void setColors(std::vector<glm::vec3>& colors) { colors_ = colors; };
	void setTriangles(std::vector<unsigned int>& triangles) { triangles_ = triangles; };

	// getter
	const std::vector<glm::vec3>& getPositions() const { return positions_; };
	const std::vector<glm::vec3>& getNormals() const { return normals_; };
	const std::vector<glm::vec2>& getUVs() const { return UVs_; };
	const std::vector<glm::vec3>& getColors() const { return colors_; };
	const std::vector<unsigned int>& getTriangles() const { return triangles_; };

	// const std::vector<glm::vec3>& getTangents() const;
	// const std::vector<glm::vec3>& getBinormals() const;

private:
	// all properties you ever wanted for a vertex
	std::vector<glm::vec3> positions_;
	std::vector<glm::vec3> normals_;
	std::vector<glm::vec2> UVs_;
	std::vector<glm::vec3> colors_;
	// std::vector<glm::vec3> tangents_;
	// std::vector<glm::vec3> binormals_;
	std::vector<unsigned int> triangles_;

};


#endif 	// MESH_H