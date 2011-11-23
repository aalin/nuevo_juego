#include "player.hpp"
#include "map.hpp"

Player::Player(p::vec2 pos) : _position(pos.x, pos.y, 0.0), _rotation(0.0)
{
	const float vertices[] = {
	  -0.25, -0.25, 0.00,
	   0.00,  0.00, 0.00,
	   0.00,  0.50, 0.00,
	   0.25, -0.25, 0.00
	};

	glGenBuffers(1, &_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Player::update(const Map& map)
{
	_position.z = map.heightAt(_position.x, _position.y) + 1.0;
}

void Player::draw()
{
	glPushMatrix();

	glDisable(GL_LIGHTING);
	glPointSize(10.0);
	glBegin(GL_POINTS);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(_position.x, _position.y, _position.z);
	glEnd();
	glEnable(GL_LIGHTING);

	/*
	glTranslatef(_position.x, _position.y, map.heightAt(_position.x, _position.y) + 1.0);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(float) * 3, (void*)0);
	glDrawElements(GL_TRIANGLE_STRIP, 3 * 4, GL_UNSIGNED_SHORT, (void*)0);

	glDisableClientState(GL_VERTEX_ARRAY);
	*/

	glPopMatrix();
}
