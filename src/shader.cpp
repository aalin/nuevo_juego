#include <iostream>
#include <fstream>
#include "shader.hpp"

std::string readSource(std::string filename)
{
	std::ifstream is(filename.c_str());

	if(is.fail())
		throw "error loading file";

	is.seekg (0, std::ios::end);
	unsigned int length = is.tellg();
	is.seekg (0, std::ios::beg);

	std::string source(length, '\0');
	is.read(&source[0], length);
	is.close();

	return source;
}

GLuint createShader(GLenum shader_type, std::string filename)
{
	GLuint shader = glCreateShader(shader_type);
	std::cout << "--- " << filename << ":" << std::endl;
	std::string source = readSource(filename);
	std::cout << source << std::endl;
	std::cout << "/// " << filename << std::endl;

	const char* data = source.c_str();
	glShaderSource(shader, 1, &data, 0);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint log_length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

		GLchar *info = new GLchar[log_length + 1];
		glGetShaderInfoLog(shader, log_length, NULL, info);

		std::cout << "Errors compiling " << filename << std::endl;
		std::cout << info << std::endl;

		delete[] info;

		throw;
	}

}

Shader::Shader(std::string basename) {
	_vertex_shader = createShader(GL_VERTEX_SHADER, basename + ".vert");
	_fragment_shader = createShader(GL_FRAGMENT_SHADER, basename + ".frag");

	_program = glCreateProgram();

	glAttachShader(_program, _vertex_shader);
	glAttachShader(_program, _fragment_shader);

	glLinkProgram(_program);

	GLint status;
	glGetProgramiv(_program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint log_length;
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &log_length);

		GLchar *info_log = new GLchar[log_length + 1];
		glGetProgramInfoLog(_program, log_length, NULL, info_log);
		std::cout << "Linker failure: " << info_log << std::endl;
		delete[] info_log;
	}

	GLint num_uniforms;
	glGetProgramiv(_program, GL_ACTIVE_UNIFORMS, &num_uniforms);
	std::cout << "Num uniforms: " << num_uniforms << std::endl;
}
