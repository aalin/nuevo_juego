#include "game.hpp"
#include "map.hpp"
#include "player.hpp"

#include "opengl.hpp"

#include <SDL/SDL.h>
#include <cmath>

Game::Game() {
	_map = new Map();
	_player = new Player(p::vec2(150.0, 150.0));

	_movement.x = 0.0;
	_movement.y = 0.0;
	_last_update = SDL_GetTicks();
}

Game::~Game()
{
	delete _map;
	delete _player;
}

void Game::keyUp(SDLKey& key)
{
	switch(key)
	{
		case SDLK_w:
			_movement.x -= 1.0;
			break;
		case SDLK_s:
			_movement.x += 1.0;
			break;
		case SDLK_a:
			_movement.y -= 1.0;
			break;
		case SDLK_d:
			_movement.y += 1.0;
			break;
		default:
			break;
	}
}

void Game::keyDown(SDLKey& key)
{
	switch(key)
	{
		case SDLK_w:
			_movement.x += 1.0;
			break;
		case SDLK_s:
			_movement.x -= 1.0;
			break;
		case SDLK_a:
			_movement.y += 1.0;
			break;
		case SDLK_d:
			_movement.y -= 1.0;
			break;
		default:
			break;
	}
}

void Game::update()
{
	float speed = (SDL_GetTicks() - _last_update) / 10.0;
	_player->move(_movement.x * speed);
	_player->rotate(_movement.y * speed);
	_player->update(*_map);
	_last_update = SDL_GetTicks();
}

void Game::draw()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 800.0 / 600.0, 1.0, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float ticks = SDL_GetTicks();

	const float center = _map->size() / 2.0;

	p::vec3 look_at = _player->position();
	p::vec3 camera = look_at + _player->direction() * -25.0;
	camera.z = _map->heightAt(camera.x, camera.y) + 5.0;

	GLfloat light_pos[] = { camera.x, camera.y, camera.z };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	gluLookAt(
		camera.x, camera.y, camera.z,
		look_at.x, look_at.y, look_at.z,
		0.0, 0.0, 1.0
	);

	_map->draw();
	_player->draw();
}
