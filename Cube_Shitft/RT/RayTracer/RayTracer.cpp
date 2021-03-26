#include "RayTracer.h"

RT::RayTracer::RayTracer(std::string Directory, std::string MainFile, sf::Vector2u res) : Resolution(res)
{
	this->Compute_Shader = new OGL::Shader(Directory, MainFile, OGL::Shader::COMPUTE_SHADER);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// set basic parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//GL_CLAMP_TO_EDGE GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Create texture data (4-component unsigned byte)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, Resolution.x, Resolution.y, 0, GL_RGBA, GL_FLOAT, NULL);
	glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RT::RayTracer::Update(sf::RenderWindow& win, UniformData ud, float DeltaTime, unsigned int TextureSlot)
{
	camera.Update_Mouse(win);
	camera.Update_Keyboard(DeltaTime);

	// Draw
	Call(glBindTexture(GL_TEXTURE_2D, texture));
	Call(glActiveTexture(GL_TEXTURE0 + TextureSlot));

	Compute_Shader->Bind();
	Compute_Shader->SetUniform1i(ud.Image, 0);
	Compute_Shader->SetUniformMat4f(ud.MVP_Matrix, camera.Get_View_Matrix());
	Compute_Shader->SetUniform(ud.Camera_Position, camera.GetPlayerPos().x, camera.GetPlayerPos().y, camera.GetPlayerPos().z, 0.0f);

	Compute_Shader->Bind_Compute(Resolution.x, Resolution.y, 1);
}

RT::RayTracer::~RayTracer()
{
	;
}
