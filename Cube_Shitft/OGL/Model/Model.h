#ifndef MODEL_H
#define MODEL_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../Call.h"
#include "../Shaders/Shader.h"

namespace OGL
{
    class glBuffers
    {
        public:

            unsigned int VertexBuffer;// Opengl Variable
            unsigned int IndexBuffer;// Opengl Variable

            unsigned int VertexArrayId;// Opengl Variable
    };

    class Model
    {
        private:

            std::vector<float> VertexArray;
            std::vector<float> NormalArray;
            std::vector<unsigned int> IndexArray;

            glBuffers Buffer;

            glm::mat4 ScaleM;
            glm::mat4 Transform;
            glm::mat4 Rotation;

            glm::vec4 Color;

            glm::vec3 Pos;

        public:
            OGL::Shader* msh;

            Model();

            void GenerateModel(std::vector<float>& va, std::vector<unsigned int>& ia);

            void Rotate(float Angle, glm::vec3 axis);
            void Scale(glm::vec3 Scale);
            void SetPosition(glm::vec3 Pos);

            void Bind();

            void UnBind();

            void Draw();

            void SetShader(OGL::Shader& sh){ msh = &sh; }

            void SetColor(glm::vec4 Col){ Color = Col; }

            ~Model();
    };
}

#endif // MODEL_H
