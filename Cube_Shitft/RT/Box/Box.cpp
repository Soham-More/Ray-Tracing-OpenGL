#include "Box.h"

glm::vec4 vec4(glm::vec3 v)
{
	return glm::vec4(v.x, v.y, v.z, 1.0f);
}

RT::Shapes::Box::Box(glm::vec3 Center, glm::vec3 Size, sf::Color col)
{
	this->min = vec4(Center - (Size / 2.0f));
	this->max = vec4(Center + (Size / 2.0f));

	this->Color = glm::vec4(col.r / 255.0f, col.g / 255.0f, col.b / 255.0f, col.a / 255.0f);
}

RT::Shapes::Box::Box(glm::vec3 Min, glm::vec3 Max, glm::vec4 col)
{
	this->min = vec4(Min);
	this->max = vec4(Max);
	this->Color = glm::vec4(col.r / 255.0f, col.g / 255.0f, col.b / 255.0f, col.a / 255.0f);
}


RT::Shapes::Box::~Box()
{
	;
}
