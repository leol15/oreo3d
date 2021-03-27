

#include "Drawable.h"
#include "../resource/Mesh.h"

#include <iostream>

void Drawable::draw(const glm::mat4& proj_matrix,
		const glm::mat4& view_matrix,
		const glm::mat4& model_matrix) const {
	// set up for glmesh's render
	// check shaderprogram
	if (shaderprogram_ == nullptr) return;
	// set up shader program, somehow know what uniform to pass in
	glUseProgram(shaderprogram_->getProgram());
	// bind uniforms

	GLuint M_ID = glGetUniformLocation(shaderprogram_->getProgram(), "M");
	GLuint V_ID = glGetUniformLocation(shaderprogram_->getProgram(), "V");
	GLuint P_ID = glGetUniformLocation(shaderprogram_->getProgram(), "P");

	// apply local transformations
	glm::mat4 model_matrix_new = model_matrix * model_matrix_;

	glUniformMatrix4fv(M_ID, 1, GL_FALSE, &model_matrix_new[0][0]);
	glUniformMatrix4fv(V_ID, 1, GL_FALSE, &view_matrix[0][0]);
	glUniformMatrix4fv(P_ID, 1, GL_FALSE, &proj_matrix[0][0]);

	glmesh_.render();
	glUseProgram(0);
}

void Drawable::setMesh(const Mesh & mesh) {
	glmesh_.setMesh(mesh);
}

