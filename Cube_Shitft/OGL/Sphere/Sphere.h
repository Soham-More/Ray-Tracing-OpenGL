#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../Call.h"
#include "../Shaders/Shader.h"
#include "../Model/Model.h"

namespace OGL
{
    class Sphere
    {
        private:
            OGL::Model s_Model;

            glm::vec3 Pos;
            float radius;

            void Generate_Fragments(float radius, float sectorCount, float stackCount);

        public:

            Sphere(){ ; }
            Sphere(glm::vec3 Pos, float radius);

            void SetShader(OGL::Shader& sh){ s_Model.SetShader(sh); }

            void SetPosition(glm::vec3 Pos){ s_Model.SetPosition(Pos); this->Pos = Pos; }
            void SetRadius(float r){ s_Model.Scale(glm::vec3(r, r, r)); radius = r; }

            void move(glm::vec3 m);

            glm::vec3 GetPosition(){ return Pos; }

            void SetColor(sf::Color Col){ s_Model.SetColor(glm::vec4(Col.r/255.0f, Col.g/255.0f, Col.b/255.0f, Col.a/255.0f));}

            void Draw();

            ~Sphere();
    };
}

#endif // SPHERE_H
