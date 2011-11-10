#include "map.hpp"
#include "opengl.hpp"
#include "vector3.hpp"
#include <cmath>
#include <iostream>

const float PI = 3.14159;

Map::Map() : _size(128)
{
	std::cout << "Map::Map()" << std::endl;
	glGenBuffers(2, _buffers);

	_height_data.reserve(_size * _size);

	for(unsigned int y = 0; y < _size; ++y)
		for(unsigned int x = 0; x < _size; ++x)
			_height_data.push_back(std::cos(x / PI) + std::sin(y / PI) + std::cos(x * y / 200.0));

	std::vector<float> data;
	data.reserve(_size * _size * 6);

	for(unsigned int y = 0; y < _size; ++y)
	{
		for(unsigned int x = 0; x < _size; ++x)
		{
			// Vertex
			data.push_back(x);
			data.push_back(y);
			data.push_back(_height_data[y * _size + x]);

			// Normal
			if(x < 1 || y < 1 || x >= _size || y >= _size)
			{
				data.push_back(0.0);
				data.push_back(0.0);
				data.push_back(0.0);
			}
			else
			{
				float dx = _height_data[y * _size + x + 1] - _height_data[y * _size + x - 1];
				float dy = _height_data[(y + 1) * _size + x] - _height_data[(y - 1) * _size + x];
				Vector3 v(-dx, -dy, 1.0);
				v.normalize();
				data.push_back(v.x);
				data.push_back(v.y);
				data.push_back(v.z);
			}
		}
	}

	std::cout << data.size() << std::endl;

	std::vector<unsigned short> indexes;
	indexes.reserve(_size * _size * 6);

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
	glEnableClientState(GL_NORMAL_ARRAY);
	const int vertex_size = sizeof(float) * 6; // 3 floats for vertex, 3 floats for normal
	glVertexPointer(3, GL_FLOAT, vertex_size, (void*)0);
	glNormalPointer(GL_FLOAT, vertex_size, (void*)(sizeof(float) * 3));

	glDrawElements(GL_TRIANGLES, _size * _size * 6, GL_UNSIGNED_SHORT, (void*)0);

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
