#include "game.hpp"
#include "map.hpp"

#include "opengl.hpp"

Game::Game() {
	_map = new Map();
}

Game::~Game()
{
	delete _map;
}

void Game::update()
{
}

void Game::draw()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 800.0 / 600.0, 1.0, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		-20.0, -20.0, 10.0,
		50.0, 50.0, 0.0,
		0.0, 0.0, 1.0
	);
	_map->draw();
}
