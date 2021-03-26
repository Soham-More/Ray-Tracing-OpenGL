#pragma once

#include "../../Call.h"
#include "../Shader.h"

#include <fstream>
#include <string>
#include <sstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <SFML/Graphics.hpp>

namespace OGL
{
	class SSBO
	{
		private:
			unsigned int ssboID;

		public:
			SSBO();

			void Bind();
			void UnBind();

			void SetBase(unsigned int Base);

			template<class T>
			inline void SetData(std::vector<T> Data)
			{
				Bind();
				Call(glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(T) * Data.size(), &Data[0], GL_STATIC_COPY));
			}

			~SSBO();
	};
}

