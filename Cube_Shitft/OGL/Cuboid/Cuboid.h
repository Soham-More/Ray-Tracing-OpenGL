#ifndef CUBOID_H
#define CUBOID_H

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
	class Cuboid
	{
		private:
			OGL::Model Basic_Model;

			glm::vec3 Pos;
			glm::vec3 Size;

		public:
			Cuboid();
			Cuboid(glm::vec3 Pos, glm::vec3 Size);

			void SetShader(OGL::Shader& sh) { Basic_Model.SetShader(sh); }

			void SetPosition(glm::vec3 Pos) { Basic_Model.SetPosition(Pos); this->Pos = Pos; }
			void SetSize(glm::vec3 Size) { Basic_Model.Scale(Size); this->Size = Size; }

			void move(glm::vec3 m);

			glm::vec3 GetPosition() { return Pos; }

			void SetColor(sf::Color Col) { Basic_Model.SetColor(glm::vec4(Col.r / 255.0f, Col.g / 255.0f, Col.b / 255.0f, Col.a / 255.0f)); }

			void Draw();

			~Cuboid();
	};
}

#endif // !CUBOID_H

