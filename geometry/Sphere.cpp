
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <cmath>

#include "Geometry.h"
#include "Sphere.h"
#include "../resource/Mesh.h"


Sphere::Sphere() : Geometry() {
	// pupulate a sphere mesh_

	std::vector<glm::vec2> sphere_curve;
	for (int degree = 0; degree <= 180; degree += 10) {
		sphere_curve.push_back(glm::vec2(
			static_cast<float>(sin(degree / 180.0f * M_PI) / 2.0f),
			static_cast<float>(cos(degree / 180.0f * M_PI) / 2.0f)));
	}

	mesh_ = new Mesh(sphere_curve, 25);
}

Sphere::~Sphere() {
	delete mesh_;
}

