#ifndef FRAME_COUNTER_HPP
#define FRAME_COUNTER_HPP

#include <SDL/SDL.h>
#include <iostream>

class FrameCounter
{
	public:
		FrameCounter()
		{
			_start_time = 0;
			_frames = 0;
		}

		void update()
		{
			_frames++;
			unsigned int end_time = SDL_GetTicks();
			if(end_time - _start_time >= 5000)
			{
				float seconds = (end_time - _start_time) / 1000.0;
				float fps = _frames / seconds;
				std::cout << _frames << " frames in " << seconds << " seconds: " << fps << " fps" << std::endl;
				_start_time = end_time;
				_frames = 0;
			}
		}

	protected:
		unsigned int _start_time;
		unsigned int _frames;
};

#endif

