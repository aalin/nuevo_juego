#include "game.hpp"
#include "map.hpp"
#include "shader.hpp"

#include "opengl.hpp"

#include <SDL/SDL.h>
#include <cmath>

Game::Game() {
	_map = new Map();
	_shader = new Shader("test");
}

Game::~Game()
{
	delete _map;
	delete _shader;
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

	float ticks = SDL_GetTicks();
	float x = std::cos(ticks / 800.0);
	float y = std::sin(ticks / 800.0);

	const float center = _map->size() / 2.0;

	gluLookAt(
		x * 100.0 + center, y * 100.0 + center, 30.0,
		x * 20.0 + center, y * 20.0 + center, 0.0,
		0.0, 0.0, 1.0
	);

	_shader->use();
	_map->draw();
}
