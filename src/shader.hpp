#ifndef SHADER_HPP
#define SHADER_HPP

#include "opengl.hpp"
#include <string>

class Shader {
	public:
		Shader(std::string basename);

		void use() { glUseProgram(_program); }

	private:
		GLuint _vertex_shader;
		GLuint _fragment_shader;
		GLuint _program;

		std::map<std::string, GLint>
};

#endif
