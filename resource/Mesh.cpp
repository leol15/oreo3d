
#include <cmath>

#include "Mesh.h"



// surface of revolution
Mesh::Mesh(const std::vector<glm::vec2> pts2d, int num_bands) {
	// spin it in the y direction, x z changes
	if (pts2d.size() < 2) return;

	auto rotVec = [](const glm::vec2 v, const float angle_rad) {
		return glm::vec3(v.x * cos(angle_rad), v.y, v.x * sin(angle_rad));
	};

	float max_y, min_y;
	max_y = min_y = pts2d[0].y;

	for (auto & p : pts2d) {
		max_y = std::max(max_y, p.y);
		min_y = std::min(min_y, p.y);
	}

	// pts
	for (size_t i = 0; i < pts2d.size(); i++) {
		// one circle
		for (int slice = 0; slice <= num_bands; slice++) {
			// vertex
			float angle_radian = 2.0f * M_PI * slice / num_bands;
			glm::vec3 point3d = rotVec(pts2d[i], angle_radian);
			positions_.push_back(point3d);
			// normal
			glm::vec3 tangent_vertical(0);
			if (i == 0) {
				// with next
				glm::vec3 next_point = rotVec(pts2d[i + 1], angle_radian);
				tangent_vertical = glm::normalize(point3d - next_point);
			} else {
				glm::vec3 prev_point = rotVec(pts2d[i - 1], angle_radian);
				tangent_vertical = glm::normalize(prev_point - point3d);
			}
			glm::vec3 tangent_horizontal = rotVec(glm::vec2(1, 0), M_PI / 2.0f + angle_radian);
			normals_.push_back(glm::normalize(glm::cross(tangent_vertical, tangent_horizontal)));
			// normals.push_back(glm::normalize(tangent_vertical));
			// uv
			UVs_.push_back(glm::vec2(static_cast<float>(slice) / num_bands,
				pts2d[i].y - min_y / (max_y - min_y)));
		}
	}

	size_t vert_per_layer = num_bands + 1;

	// faces
	for (size_t layer = 1; layer < pts2d.size(); layer++) {
		// connect with prev layer
		for (size_t band = 1; band < vert_per_layer; band++) {
			// prev band
			// DC
			// BA
			unsigned int A = vert_per_layer * layer + band; 
			unsigned int B = A - 1;
			unsigned int C = A - vert_per_layer;
			unsigned int D = B - vert_per_layer;
			triangles_.push_back(D);
			triangles_.push_back(C);
			triangles_.push_back(B);

			triangles_.push_back(B);
			triangles_.push_back(C);
			triangles_.push_back(A);
		}
	}
}




