#include "map.hpp"
#include "opengl.hpp"
#include <cmath>
#include <iostream>

const float PI = 3.14159;

Map::Map() : _size(128)
{
	std::cout << "Map::Map()" << std::endl;
	glGenBuffers(2, _buffers);

	_height_data.reserve(_size * _size);

	std::vector<float> data;
	data.reserve(_size * _size * 3);

	for(unsigned int y = 0; y < _size; ++y)
	{
		for(unsigned int x = 0; x < _size; ++x)
		{
			float z = std::cos(x / PI) + std::sin(y / PI);
			data.push_back(x);
			data.push_back(y);
			data.push_back(z);
			_height_data.push_back(z);
		}
	}

	std::vector<unsigned short> indexes;
	indexes.reserve(_size * _size * 3);

	for(unsigned int y = 0; y < _size - 1; ++y)
	{
		for(unsigned int x = 0; x < _size - 1; ++x)
		{
			indexes.push_back(y * _size + x);
			indexes.push_back(y * _size + x + 1);
			indexes.push_back((y + 1) * _size + x + 1);

			indexes.push_back(y * _size + x);
			indexes.push_back((y + 1) * _size + x);
			indexes.push_back((y + 1) * _size + x + 1);
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer());
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), &data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indexes.size(), &indexes[0], GL_STATIC_DRAW);
}

Map::~Map()
{
	glDeleteBuffers(2, _buffers);
}

void Map::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer());

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, (void*)0);

	glDrawElements(GL_TRIANGLES, _size * _size * 6, GL_UNSIGNED_SHORT, (void*)0);

	glDisableClientState(GL_VERTEX_ARRAY);
}
