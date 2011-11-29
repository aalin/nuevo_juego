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
			return _height_data[y * _size + x];
		}

	private:
		unsigned int _size;
		std::vector<float> _height_data;

		GLuint _buffers[2];
		GLuint vertexBuffer() { return _buffers[0]; }
		GLuint indexBuffer() { return _buffers[1]; }
};

#endif
