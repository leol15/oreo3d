#ifndef TRANSFORMABLE_H_
#define TRANSFORMABLE_H_

#include <glm/glm.hpp>

class Transformable {
public:
	Transformable() : model_matrix_(1.0f),
		translate_(0), rotate_(0), scale_(0) { };

	// can set matrix directly
	void setModelMatrix(const glm::mat4 & M) {
		model_matrix_ = M;
	}

	// transformations
	void setTranslate(const glm::vec3 & translate) {
		translate_ = translate;
		computeModelMatrix();
	}
	void setRotate(const glm::vec3 & euler_angles) {
		rotate_ = euler_angles;
		computeModelMatrix();
	}
	void setScale(const glm::vec3 & scale) {
		scale_ = scale;
		computeModelMatrix();
	}

protected:
	// transformations
	glm::mat4 model_matrix_;
	glm::vec3 translate_;
	glm::vec3 rotate_;
	glm::vec3 scale_;

	void computeModelMatrix() {
		glm::mat4 translate = glm::translate(glm::mat4(), translate_);
		glm::mat4 rotate = glm::eulerAngleXYZ(
			glm::radians(rotate_.x),
			glm::radians(rotate_.y),
			glm::radians(rotate_.z));
		// rotation_ = glm::quat_cast(rotate);
		glm::mat4 scale = glm::scale(glm::mat4(), scale_);
		model_matrix_ = translate * rotate * scale;
	}
};


#endif