#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <SFML/Graphics.hpp>

#include "../../OGL/OGL.hpp"

namespace RT
{
	class RayTracer
	{
		private:
			OGL::Shader* Compute_Shader;
			OGL::Camera camera;

			GLuint texture = 0;
			sf::Vector2u Resolution;

			std::vector<OGL::SSBO> ssbo_Vector;

		public:

			struct UniformData
			{
				std::string Image;
				std::string MVP_Matrix;
				std::string Camera_Position;
			};

			RayTracer(std::string Directory, std::string MainFile, sf::Vector2u res);

			void AddSSBO(OGL::SSBO& ssbo, unsigned int Base)
			{
				ssbo_Vector.push_back(ssbo);
				Compute_Shader->Bind();
				ssbo.SetBase(Base);
			}

			void Update(sf::RenderWindow& win, UniformData ud, float DeltaTime, unsigned int TextureSlot = 0);

			void Wait(OGL::Shader::Barrier_Type bt = OGL::Shader::ALL_ACCESS_BARRIERS) { Compute_Shader->SetBarrier(bt); }

			~RayTracer();
	};
}

#endif // !RAY_TRACER_H
