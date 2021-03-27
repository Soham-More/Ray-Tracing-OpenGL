#include <iostream>
#include <cstdio>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <SFML/Graphics.hpp>

#include "OGL/OGL.hpp"
#include "RT/RT.hpp"

// Change to false for compiling for a release
#define DEBUG false

//unsigned int OGL::Shader::ShaderCount = 0;
//int OGL::Shader::currentShader = -1;

void main()
{
	sf::ContextSettings settings;
	settings.majorVersion = 4;
	settings.minorVersion = 3;

	sf::RenderWindow win(sf::VideoMode(800, 600), "Ray Tracer", sf::Style::Default, settings);
	win.setVerticalSyncEnabled(true);

	OGL::Init();

	std::string Root_Dir;

	if (DEBUG)
	{
		Root_Dir = "C:/Users/deathstroke/Desktop/Soham's Directory/Visual C++ Projects/C++ Projects/Cube_Shitft/Cube_Shitft/";
	}
	else
	{
		Root_Dir = "";
	}

	OGL::Shader sh(Root_Dir + "Shaders/Compute_Shaders/", "Shader.sh");

	sf::RenderStates rs;
	rs.shader = &sh.Get_Shader();

	int work_grp_cnt[3];

	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &work_grp_cnt[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &work_grp_cnt[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &work_grp_cnt[2]);

	printf("max global (total) work group counts x:%i y:%i z:%i\n",
		work_grp_cnt[0], work_grp_cnt[1], work_grp_cnt[2]);

	int work_grp_size[3];

	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &work_grp_size[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &work_grp_size[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &work_grp_size[2]);

	printf("max local (in one shader) work group sizes x:%i y:%i z:%i\n",
		work_grp_size[0], work_grp_size[1], work_grp_size[2]);

	int work_grp_inv = 0;

	glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &work_grp_inv);
	printf("max local work group invocations %i\n", work_grp_inv);

	float data[] = {
		-1.0f, 1.0f, 0.0f, 1.0f,
		 1.0f, 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f, 0.0f,

		-1.0f, 1.0f, 0.0f, 1.0f,
		-1.0f,-1.0f, 0.0f, 0.0f,
		 1.0f,-1.0f, 1.0f, 0.0f,
	};

	GLuint VBO = 0;
	GLuint buffer = 0;

	Call(glGenVertexArrays(1, &VBO));
	Call(glBindVertexArray(VBO));

	Call(glGenBuffers(1, &buffer));
	Call(glBindBuffer(GL_ARRAY_BUFFER, buffer));

	Call(glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW));

	Call(glBindVertexArray(0));

	std::vector<RT::Shapes::Box> Scene =
	{
		// The ground
		RT::Shapes::Box(glm::vec3(0.0f,-0.05f, 0.0f), glm::vec3(10.0f, 0.1f, 10.0f), sf::Color::Red),
		//Box in the middle
		RT::Shapes::Box(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), sf::Color::Green),

		RT::Shapes::Box(glm::vec3(2.0f, 1.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f), sf::Color::Blue),
		// Light Source
		RT::Shapes::Box(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), sf::Color::White),

		RT::Shapes::Box(glm::vec3(10.05f, 0.0f, 0.0f), glm::vec3(1.0f, 10.0f, 10.0f), sf::Color::Red),
	};

	OGL::SSBO Box_Scene;

	RT::RayTracer rt(Root_Dir + "Shaders/Compute_Shaders/", "Tutorial.vert", sf::Vector2u(1600, 1200));
	rt.AddSSBO(Box_Scene, 1);
	Box_Scene.SetData<RT::Shapes::Box>(Scene);

	sf::Clock clk;
	float DeltaTime = 0.0f;

	while (true)
	{
		sf::Event Win_Event;

		while (win.pollEvent(Win_Event))
		{
			switch (Win_Event.type)
			{
				case sf::Event::Closed:
					win.close();
					break;

				case sf::Event::Resized:
					win.setSize(sf::Vector2u(Win_Event.size.width, Win_Event.size.height));
					break;

				default:
					break;
			}
		}

		if (!win.isOpen())
		{
			break;
		}
		
		// Clear Window
		win.clear();

		glClear(GL_COLOR_BUFFER_BIT);

		// Draw
		rt.Update(win, { "img_output", "ViewTransform", "CameraPos" }, DeltaTime);

		Call(glBindVertexArray(VBO));
		Call(glBindBuffer(GL_ARRAY_BUFFER, buffer));

		Call(glEnableVertexAttribArray(0));
		Call(glVertexAttribPointer(
			0,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			16,                               // stride
			(void*)0                          // array buffer offset
		));

		Call(glEnableVertexAttribArray(1));
		Call(glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			16,                               // stride
			(void*)8                          // array buffer offset
		));

		float aspect = float(win.getSize().x) / float(win.getSize().y);

		glm::mat4 proj = glm::ortho(0.0f, aspect, 0.0f, 1.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(aspect/2, 0.5f, -1.0f));
		glm::mat4 Model = glm::mat4(1.0f);

		rt.Wait(OGL::Shader::IMAGE_ACCESS_BARRIER);

		sh.Bind();

		sh.SetUniform1i("texture", 0);

		sh.SetUniformMat4f("Projection", proj);
		sh.SetUniformMat4f("View", view);
		sh.SetUniformMat4f("Model", Model);
		
		Call(glDrawArrays(GL_TRIANGLES, 0, 6));

		std::cout << "FPS: " << 1 / DeltaTime << "\n";

		// Display all Content
		win.display();

		DeltaTime = clk.getElapsedTime().asSeconds();
		clk.restart();
	}

	system("Pause");

	glfwTerminate();
}