#include "map.hpp"
#include "opengl.hpp"
#include <cmath>
#include <iostream>
#include <fstream>

#include "p-math/vector.h"

const float PI = 3.14159;

std::vector<float> loadMap(std::string filename) {
	std::ifstream is(filename.c_str());

	if(is.fail())
		throw "error loading file";

	is.seekg(0, std::ios::end);
	unsigned int length = is.tellg();
	is.seekg(0, std::ios::beg);

	std::vector<float> result;
	result.reserve(length);

	while(is.good())
	{
		unsigned char c = is.get();
		if(is.good())
			result.push_back(c / 256.0 * 50.0 - 30.0);
	}

	is.close();
	return result;
};

template <typename T>
T square(T value) { return value * value; }

Map::Map()
{
	std::cout << "Map::Map()" << std::endl;
	glGenBuffers(2, _buffers);

	_height_data = loadMap("map.a");
	_size = std::sqrt(_height_data.size());

	std::vector<p::vec3> data;
	data.reserve(square(_size) * 2);

	for(unsigned int y = 0; y < _size; ++y)
	{
		for(unsigned int x = 0; x < _size; ++x)
		{
			// Vertex
			data.push_back(p::vec3(x, y, _height_data[y * _size + x]));

			// Normal
			if(x < 1 || y < 1 || x >= _size || y >= _size)
				data.push_back(p::vec3(0.0, 0.0, 0.0));
			else
			{
				float dx = _height_data[y * _size + x + 1] - _height_data[y * _size + x - 1];
				float dy = _height_data[(y + 1) * _size + x] - _height_data[(y - 1) * _size + x];
				p::vec3 v(-dx, -dy, 1.0);
				data.push_back(p::normalize(v));
			}
		}
	}

	typedef p::vec<unsigned short, 3> index;
	std::vector<index> indexes;
	indexes.reserve(square(_size - 1) * 2);

	for(unsigned int y = 0; y < _size - 1; ++y)
	{
		for(unsigned int x = 0; x < _size - 1; ++x)
		{
			indexes.push_back(index(y * _size + x, (y * 1) * _size + x + 1, (y + 1) * _size + x + 1));
			indexes.push_back(index(y * _size + x, (y + 1) * _size + x * 1, (y + 1) * _size + x + 1));
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer());
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * data.size(), &data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index) * indexes.size(), &indexes[0], GL_STATIC_DRAW);
}

Map::~Map()
{
	glDeleteBuffers(2, _buffers);
}

void Map::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer());

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	const int vertex_size = sizeof(float) * 6; // 3 floats for vertex, 3 floats for normal
	glVertexPointer(3, GL_FLOAT, vertex_size, (void*)0);
	glNormalPointer(GL_FLOAT, vertex_size, (void*)(sizeof(float) * 3));

	glDrawElements(GL_TRIANGLES, square(_size - 1) * 6, GL_UNSIGNED_SHORT, (void*)0);

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
