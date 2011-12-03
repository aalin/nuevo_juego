#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include "opengl.hpp"

class Map {
	public:
		Map();
		~Map();

		void draw();

		unsigned int size() const { return _size; };

		float heightAt(unsigned int x, unsigned int y) const {
			if(x >= _size - 1 || y >= _size - 1)
				return 0.0;

			return _height_data[y * _size + x];
		}

		float interpolatedHeightAt(float x, float y) const {
			int int_x = static_cast<int>(x);
			int int_y = static_cast<int>(y);

			float height = heightAt(int_x, int_y);

			float dx = heightAt(x + 1, y) - height;
			float dy = heightAt(x, y + 1) - height;

			float into_x = x - int_x;
			float into_y = y - int_y;

			return height + dx * into_x + dy * into_y;
		}

	private:
		unsigned int _size;
		std::vector<float> _height_data;

		GLuint _buffers[2];
		GLuint vertexBuffer() { return _buffers[0]; }
		GLuint indexBuffer() { return _buffers[1]; }
};

#endif
