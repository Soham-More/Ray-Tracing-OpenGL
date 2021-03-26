#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <SFML/Graphics.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../Call.h"
#include "../Shaders/Shader.h"
#include "../Model/Model.h"

namespace OGL
{
	class CubeMap
	{
		private:
			unsigned int TextureID = 0;

			;

		public:
			CubeMap();

			void SourceFiles(std::vector<std::string>& FileNames);

			void Bind(unsigned int slot);

			void UnBind();

			~CubeMap();
	};
}

#endif // CUBEMAP_H