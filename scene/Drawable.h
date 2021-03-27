#ifndef DRAWABLE_
#define DRAWABLE_

#include "../resource/GLMesh.h"
#include "../resource/ShaderProgram.h"

// contains everything you need to draw some triangles
class Drawable {
public:
	Drawable() : glmesh_(), shaderprogram_(nullptr) { };
	virtual ~Drawable() { };
	
	// setters
	void setShaderProgram(ShaderProgram * sp) { shaderprogram_ = sp; }

	void setMesh(const Mesh & mesh);

	void draw(const glm::mat4& proj_matrix,
		const glm::mat4& view_matrix,
		const glm::mat4& model_matrix) const;

	const GLMesh& getGLMesh() const { return glmesh_; }
protected:
	GLMesh glmesh_;
	ShaderProgram * shaderprogram_;

};


#endif	// DRAWABLE_

