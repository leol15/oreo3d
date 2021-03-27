#ifndef DRAWABLE_
#define DRAWABLE_

#include "../resource/GLMesh.h"
#include "../resource/ShaderProgram.h"
#include "../geometry/Geometry.h"
#include "../scene/Transformable.h"

// contains everything you need to draw some triangles (draws one mesh only!)
class Drawable : public Transformable {
public:
	Drawable() : Transformable(),
		glmesh_(), shaderprogram_(nullptr) { };
	virtual ~Drawable() { };
	
	// setters
	void setShaderProgram(ShaderProgram * sp) { shaderprogram_ = sp; }

	void setGeometry(const Geometry & geo) { setMesh(geo.getMesh()); }

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

