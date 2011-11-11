#ifndef GAME_HPP
#define GAME_HPP

#include <SDL/SDL.h>

class Map;
class Shader;

class Game {
	public:
		Game();
		~Game();

		void update();
		void draw();
		void keyUp(SDLKey&) {}
		void keyDown(SDLKey&) {}

	private:
		Map* _map;
		Shader* _shader;
};

#endif
