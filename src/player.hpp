#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "opengl.hpp"
#include "p-math/vector.h"

class Map;

class Player {
	public:
		Player(p::vec2 pos);

		const p::vec3& position() const { return _position; }

		void update(const Map& map);
		void draw();

	private:
		p::vec3 _position;
		float _rotation;

		GLuint _vbo;
};

#endif
