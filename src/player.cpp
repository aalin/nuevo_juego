#include "player.hpp"
#include "map.hpp"

Player::Player(p::vec2 pos) : _position(pos.x, pos.y, 0.0), _rotation(0.0)
{
	const float vertices[] = {
		-0.25, -0.25,  0.00,
		 0.00,  0.00,  0.00,
		 0.00,  0.50,  0.00,
		 0.25, -0.25,  0.00,
	};

	glGenBuffers(1, &_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

Player::~Player()
{
	glDeleteBuffers(1, &_vbo);
}

void Player::update(const Map& map)
{
	_position.z = map.interpolatedHeightAt(_position.x, _position.y) + 0.1;
}

void Player::draw()
{
	glPushMatrix();

	glDisable(GL_LIGHTING);
	glColor3f(1.0, 0.0, 0.0);

	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(_rotation, 0.0, 0.0, 1.0);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);

	glEnable(GL_LIGHTING);
	glPopMatrix();
}
