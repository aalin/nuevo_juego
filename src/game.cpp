#include "game.hpp"
#include "map.hpp"
#include "player.hpp"

#include "opengl.hpp"

#include <SDL/SDL.h>
#include <cmath>

Game::Game() {
	_map = new Map();
	_player = new Player(p::vec2(150.0, 150.0));
}

Game::~Game()
{
	delete _map;
	delete _player;
}

void Game::update()
{
	_player->update(*_map);
}

void Game::draw()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 800.0 / 600.0, 1.0, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float ticks = SDL_GetTicks();
	float x = std::cos(ticks / 800.0);
	float y = std::sin(ticks / 800.0);

	const float center = _map->size() / 2.0;

	GLfloat light_pos[] = {x * 20.0 + center, y * 20.0 + center, 30.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	p::vec3 look_at = _player->position();

	gluLookAt(
		x * 200 + center, y * 200 + center, 50.0,
		look_at.x, look_at.y, look_at.z,
		0.0, 0.0, 1.0
	);

	_map->draw();
	_player->draw();
}
