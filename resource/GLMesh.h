#ifndef GLMESH_H
#define GLMESH_H

#include "Mesh.h"

// maintain a VAO for ogl
class GLMesh {
public:
	GLMesh();
	~GLMesh();

	void SetMesh(const Mesh& mesh);
	void render();

	static const std::map<std::string, GLint> SHADER_LOCATIONS;
	
protected:
	GLuint vertex_array_id_;
	GLuint positions_vbo_;
	GLuint normals_vbo_;
	GLuint UVs_vbo_;
	GLuint colors_vbo_;
	GLuint triangles_vbo_;
	
    unsigned int num_indices_;

};



#endif	// GLMESH_H

