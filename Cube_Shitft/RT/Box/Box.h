#ifndef BOX_H
#define BOX_H

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <SFML/Graphics.hpp>

#include "../../OGL/OGL.hpp"

namespace RT
{
	namespace Shapes
	{
		struct Box
		{
			glm::vec4 min;
			glm::vec4 max;
			glm::vec4 Color;

			Box(glm::vec3 Center, glm::vec3 Size, sf::Color col);
			Box(glm::vec3 Min, glm::vec3 Max, glm::vec4 col);
			~Box();
		};
	}
}

#endif // !BOX_H

