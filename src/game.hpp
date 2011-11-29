#ifndef GAME_HPP
#define GAME_HPP

#include <SDL/SDL.h>
#include "p-math/vector.h"

class Map;
class Player;

class Game {
	public:
		Game();
		~Game();

		void update();
		void draw();
		void keyUp(SDLKey&);
		void keyDown(SDLKey&);

	private:
		Map* _map;
		Player* _player;

		p::vec2 _movement;
		unsigned int _last_update;
};

#endif
