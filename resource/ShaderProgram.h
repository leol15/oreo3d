#ifndef SHADER_PROGRAM_H_
#define SHADER_PROGRAM_H_

// #include <GL/glew.h>
// #include <GLFW/glfw3.h>

#include <string>

// manage a shader, vert + frag +? geom

class ShaderProgram {
public:
	ShaderProgram(const std::string & vertex_shader_path,
		const std::string & fragment_shader_path,
		const std::string & geometry_shader_path = "");
	~ShaderProgram();

	GLuint getProgram() const { return program_id_; }

protected:
	GLuint program_id_;
};


#endif	// SHADER_PROGRAM_H_