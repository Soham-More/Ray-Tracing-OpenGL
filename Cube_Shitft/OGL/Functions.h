#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Model/Model.h"

#include <algorithm>

namespace OGL
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
	};

	struct Vertex_Index_Array
	{
		std::vector<float> Vertex_Array;
		std::vector<unsigned int> Index_Array;
	};
}

typedef std::vector<OGL::Vertex>::iterator Vertex_Iterator;

namespace OGL
{
	Vertex_Iterator Find(Vertex_Iterator Begin, Vertex_Iterator End, Vertex& Key);

	std::vector<float> ToArray(std::vector<Vertex> Array);

	std::vector<Vertex> ToVector(std::vector<float> Array);

	Vertex_Index_Array GetIndexedArray(std::vector<Vertex>& Array);
}

#endif //FUNCTIONS_H