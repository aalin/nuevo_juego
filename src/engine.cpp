#include "engine.hpp"
#include "game.hpp"
#include "opengl.hpp"

#define SET_LIGHT(LIGHT, PNAME, X, Y, Z, A) \
{ GLfloat param[] = { X, Y, Z, A }; glLightfv(LIGHT, PNAME, param); }

#define SET_MATERIAL(FACE, PNAME, ...) \
{ GLfloat param[] = { __VA_ARGS__ } ; glMaterialfv(FACE, PNAME, param); }


Engine::Engine(unsigned int width, unsigned int height, bool fullscreen)
	: _running(true)
{
	unsigned int flags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER;

	if(fullscreen)
		flags |= SDL_FULLSCREEN;

	_surface = SDL_SetVideoMode(width, height, 32, flags);
	if(_surface == 0)
		throw "Surface could not be created";

	_game = new Game();

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	// glShadeModel(GL_SMOOTH);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_FOG);
	GLfloat fog_color[] = {0.0, 0.0, 0.0, 0.5};
	glFogfv(GL_FOG_COLOR, fog_color);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_DENSITY, 0.05);
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogf(GL_FOG_START, 50.0);
	glFogf(GL_FOG_END, 512.0);

	SET_LIGHT(GL_LIGHT0, GL_POSITION, -2.0, 2.0, 2.0, 1.0);
	SET_LIGHT(GL_LIGHT0, GL_AMBIENT,   0.0, 0.0, 0.0, 0.0);
	SET_LIGHT(GL_LIGHT0, GL_DIFFUSE,   0.1, 0.1, 0.1, 0.0);
	SET_LIGHT(GL_LIGHT0, GL_SPECULAR,  0.0, 0.0, 0.0, 0.0);

	SET_MATERIAL(GL_FRONT, GL_AMBIENT,  0.0, 0.0, 0.0, 0.0);
	SET_MATERIAL(GL_FRONT, GL_DIFFUSE,  1.0, 1.0, 1.0, 1.0);
	SET_MATERIAL(GL_FRONT, GL_SPECULAR, 0.0, 0.0, 0.0, 0.0);
	SET_MATERIAL(GL_FRONT, GL_EMISSION, 0.3, 0.3, 0.3, 0.2);
	SET_MATERIAL(GL_FRONT, GL_SHININESS, 0);

	glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

Engine::~Engine()
{
	std::cout << "~Engine()" << std::endl;
}

void Engine::handleInput()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
			quit();
		else
		{
			if(event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						quit();
						break;
					default:
						_game->keyDown(event.key.keysym.sym);
						break;
				}
			}
			else if(event.type == SDL_KEYUP)
			{
				_game->keyUp(event.key.keysym.sym);
			}
		}
	}
}

void Engine::update()
{
	_game->update();
}

void Engine::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_game->draw();
	_frame_counter.update();
	SDL_GL_SwapBuffers();
}
