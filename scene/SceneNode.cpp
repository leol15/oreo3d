

#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "SceneNode.h"

// render self and recursively render the childrens
void SceneNode::render(const glm::mat4& proj_matrix,
		const glm::mat4& view_matrix,
		glm::mat4 model_matrix) {
	// apply local transform
	model_matrix *= model_matrix_;

	// childrens
	for (auto & child : children_) {
		child.render(proj_matrix, view_matrix, model_matrix);
	}
}

