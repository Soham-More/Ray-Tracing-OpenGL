#include "Square.h"

#include "../Functions.h"


OGL::Square::Square()
{
}

OGL::Square::Square(glm::vec3 Pos, glm::vec2 Size)
{
	std::vector<float> Cuboid_Triangle =
	{
		-0.5f,  0.5f, 0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f, 0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,  0.0f,  0.0f, 1.0f
	};

	std::vector<OGL::Vertex> Init_List = OGL::ToVector(Cuboid_Triangle);

	OGL::Vertex_Index_Array VIA = OGL::GetIndexedArray(Init_List);

	Basic_Model.GenerateModel(VIA.Vertex_Array, VIA.Index_Array);

	Basic_Model.SetPosition(Pos);
	Basic_Model.Scale(glm::vec3(Size.x * 2.0f, Size.y * 2.0f, 1.0f));

	this->Pos = Pos;
	this->Size = Size;
}


void OGL::Square::Draw()
{
	Basic_Model.Draw();
}

OGL::Square::~Square()
{
}
