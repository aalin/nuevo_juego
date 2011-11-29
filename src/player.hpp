#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "opengl.hpp"
#include "p-math/vector.h"

class Map;

class Player {
	static const float PI = 3.14159265;

	public:
		Player(p::vec2 pos);
		~Player();

		const p::vec3& position() const { return _position; }
		const p::vec3 direction() const {
			return p::normalize(
				p::vec3(
					std::cos((_rotation + 90.0) / 180.0 * PI),
					std::sin((_rotation + 90.0) / 180.0 * PI),
					0.0
				)
			);
		}

		void update(const Map& map);
		void draw();

		void rotate(float degrees) {
			_rotation += degrees;
		}

		void move(float amount) {
			_position += direction() * amount;
		}

	private:
		p::vec3 _position;
		float _rotation;

		GLuint _vbo;
};

#endif
