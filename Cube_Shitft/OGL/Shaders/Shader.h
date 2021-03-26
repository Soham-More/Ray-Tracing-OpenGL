#ifndef SHADER_H
#define SHADER_H

#include "../Call.h"

#include <fstream>
#include <string>
#include <sstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_map>

namespace OGL
{
    class Shader
    {
        private:
			sf::Shader shader;
			unsigned int rid;

            unsigned int GetUniformLocation(const std::string& name);
            std::string fp;

			unsigned int ShaderID;
        public:
			enum Shader_Type{ DEFAULT = 0, COMPUTE_SHADER };
			enum Barrier_Type
			{
				ALL_ACCESS_BARRIERS = GL_ALL_BARRIER_BITS,
				IMAGE_ACCESS_BARRIER = GL_SHADER_IMAGE_ACCESS_BARRIER_BIT,
				SSBO_ACCESS_BARRIER = GL_SHADER_STORAGE_BARRIER_BIT
			};

            Shader(){}
            Shader(const std::string& Shader_Root_Folder, const std::string& Main_Shader, Shader_Type st = DEFAULT);

            void Bind();
			void Bind_Compute(int x, int y, int z);
            void Unbind();

            void SetUniform1i(const std::string& name, float f1);
            void SetUniform(const std::string& name, float r, float g, float b, float al);
            void SetUniformMat4f(const std::string& name, const glm::mat4& mat);

			void SetBarrier(Barrier_Type BarrierType);

            bool isValidShader(){ return (rid != 0); }

			sf::Shader& Get_Shader() { return shader; }

			~Shader();

		public: // Static Variables
			static unsigned int ShaderCount;
			static int currentShader;
    };
}

#endif // SHADER_H
