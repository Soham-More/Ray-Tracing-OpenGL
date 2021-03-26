#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../Call.h"

namespace OGL
{
    class Camera
    {
        private:
            glm::vec3 pos;//Position

            glm::vec3 Viewdirection;
            glm::vec3 Up;
            glm::vec3 Right;
            glm::vec2 oldMousePos;

        public:

            Camera();

            ///Updates Mouse Position
            glm::vec2 Update_Mouse(sf::RenderWindow& win);
            ///Updates position
            void Update_Keyboard(float DeltaTime);
            ///Gives View Matrix
            glm::mat4 Get_View_Matrix();
            ///Gives View Direction
            glm::vec3 GetViewDirection(){return Viewdirection;}
            ///Gives Camera's Position
            const glm::vec3 GetPlayerPos(){return pos;}

            ~Camera();
    };
}

#endif // CAMERA_H
