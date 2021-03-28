
#include "ShaderProgram.h"

#include <GL/glew.h>
// #include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

// debug
static void queryUniforms(GLuint prog_id) {
	GLint num_uniforms = 0;
    glGetProgramiv(prog_id, GL_ACTIVE_UNIFORMS, &num_uniforms);
    std::vector<GLchar> name_data(256);
    std::cerr << "num_uniforms: " << num_uniforms << std::endl;
    for (int uniform = 0; uniform < num_uniforms; uniform++) {
        // It's possible that the program is not valid if the user is not done assembling it.
        // In this case, we will just not detect any uniforms.

        // Fetch uniform information
        GLint array_size;
        GLenum gl_type;
        GLsizei name_length;
        glGetActiveUniform(prog_id, uniform, name_data.size(), &name_length, &array_size, &gl_type, &name_data[0]);
        std::string name((char*)&name_data[0], name_length);
        GLint location = glGetUniformLocation(prog_id, &name_data[0]);
        // GLCheckError();

        // If it's an array, remove the suffixed [0]
        if (array_size > 1) name = name.substr(0, name.size() - 3);

        // Store uniform information
        // DataType type = ConvertType(name, gl_type);
        // uniform_locations_[name] = std::make_pair(location, type);
        // uniforms_list_.push_back(std::make_pair(name, type));
        std::cerr << "uniform: " << name << " | " << gl_type << " | " << location << std::endl;
    }
}


// compile a shader file
static GLuint compile_shader(const std::string shader_path, GLenum shader_type);

ShaderProgram::ShaderProgram(
		const std::string & vertex_shader_path,
		const std::string & fragment_shader_path,
		const std::string & geometry_shader_path) : program_id_(0) {

	// Create & Compile the shaders
	GLuint VertexShaderID = compile_shader(vertex_shader_path, GL_VERTEX_SHADER);
	GLuint FragmentShaderID = compile_shader(fragment_shader_path, GL_FRAGMENT_SHADER);
	GLuint GeometryShaderID = geometry_shader_path == "" ? 0 :
		compile_shader(geometry_shader_path, GL_GEOMETRY_SHADER);


	// Link the program
	program_id_ = glCreateProgram();

	glAttachShader(program_id_, VertexShaderID);
	glAttachShader(program_id_, FragmentShaderID);
	if (GeometryShaderID != 0) glAttachShader(program_id_, GeometryShaderID);

	glLinkProgram(program_id_);

	// Check the program
	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetProgramiv(program_id_, GL_LINK_STATUS, &Result);
	glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 || Result != GL_TRUE){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(program_id_, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cerr << "error linking shaders: " << &ProgramErrorMessage[0] << std::endl;
		// so what?
	}

	
	glDetachShader(program_id_, VertexShaderID);
	glDetachShader(program_id_, FragmentShaderID);
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	if (GeometryShaderID != 0) {
		glDetachShader(program_id_, GeometryShaderID);
		glDeleteShader(GeometryShaderID);
	}
	// queryUniforms(program_id_);
}

ShaderProgram::~ShaderProgram() {
	if (program_id_ != 0) glDeleteProgram(program_id_);
}


////////////////// helpers

static GLuint compile_shader(const std::string shader_path, GLenum shader_type) {
	// Create the shader
	GLuint shader_id = glCreateShader(shader_type);

	// Read the Vertex Shader code from the file
	std::string shader_str;
	std::ifstream shader_fs(shader_path, std::ios::in);
	if(shader_fs.is_open()) {
		std::stringstream sstr;
		sstr << shader_fs.rdbuf();
		shader_str = sstr.str();
		shader_fs.close();
	}else{
		std::cerr << "Cannot open file " << shader_path << std::endl;
		glDeleteShader(shader_id);
		return 0;
	}

	GLint Result = GL_FALSE;
	int InfoLogLength = -1;

	// Compile Shader
	const char * shader_c_str = shader_str.c_str();
	glShaderSource(shader_id, 1, &shader_c_str , NULL);
	glCompileShader(shader_id);

	// Check Shader
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( Result != GL_TRUE ){
		std::vector<char> ShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(shader_id, InfoLogLength, NULL, &ShaderErrorMessage[0]);
		std::cerr << "shader compile error ["<< shader_path << "]:\n" << &ShaderErrorMessage[0] << std::endl;
		glDeleteShader(shader_id);
		return 0;
	}

	return shader_id;		
}



